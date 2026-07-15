#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <filesystem>
#include <deque>

#include "attacks.h"
#include "bitboard.h"
#include "evaluate.h"
#include "misc.h"
#include "nnue/network.h"
#include "nnue/nnue_accumulator.h"
#include "nnue/nnue_misc.h"
#include "position.h"
#include "types.h"
#include "uci.h"

using namespace Stockfish;

static bool sf_initialized = false;
static std::unique_ptr<Eval::NNUE::Network> global_network;
static Eval::NNUE::EvalFile global_eval_file;

struct SFBridgeAccumulator {
    Position pos;
    StateListPtr states;
    std::vector<Move> move_history;
    std::unique_ptr<Eval::NNUE::AccumulatorStack> accumulators;
    std::unique_ptr<Eval::NNUE::AccumulatorCaches> caches;

    SFBridgeAccumulator(const std::string& fen) {
        states = std::make_unique<std::deque<StateInfo>>(1);
        pos.set(fen, false, &states->back());
        accumulators = std::make_unique<Eval::NNUE::AccumulatorStack>();
        caches = std::make_unique<Eval::NNUE::AccumulatorCaches>(*global_network);
    }
};

extern "C" {

void sf_nnue_init(const char* net_path) {
    if (!sf_initialized) {
        Bitboards::init();
        Attacks::init();
        Position::init();

        global_network = std::make_unique<Eval::NNUE::Network>();
    }

    std::filesystem::path path_to_net;
    if (net_path) {
        path_to_net = net_path;
    } else {
        path_to_net = EvalFileDefaultName; 
    }

    global_network->load(std::filesystem::path{}, path_to_net, global_eval_file);
    
    sf_initialized = true;
}

void* sf_nnue_create_accumulator(const char* fen) {
    if (!sf_initialized) {
        sf_nnue_init(nullptr);
    }
    auto* acc = new SFBridgeAccumulator(fen);
    return acc;
}

void sf_nnue_update_accumulator(void* acc_ptr, uint16_t move_bits) {
    auto* acc = static_cast<SFBridgeAccumulator*>(acc_ptr);
    Move m = Move(move_bits);
    if (m != Move::none()) {
        acc->move_history.push_back(m);
        acc->states->emplace_back();
        auto [dirtyPiece, dirtyThreats] = acc->accumulators->push();
        acc->pos.do_move(m, acc->states->back(), acc->pos.gives_check(m), dirtyPiece, dirtyThreats, nullptr, nullptr);
    }
}

int sf_nnue_evaluate(void* acc_ptr) {
    auto* acc = static_cast<SFBridgeAccumulator*>(acc_ptr);
    int score = Eval::evaluate(*global_network, acc->pos, *(acc->accumulators), *(acc->caches), 0);
    // std::cout << "DEBUG SF SCORE: " << score << std::endl;
    return score;
}

void sf_nnue_undo_accumulator(void* acc_ptr) {
    auto* acc = static_cast<SFBridgeAccumulator*>(acc_ptr);
    if (!acc->move_history.empty()) {
        Move m = acc->move_history.back();
        acc->move_history.pop_back();
        if (m == Move::none()) {
            acc->pos.undo_null_move();
        } else {
            acc->pos.undo_move(m);
            acc->accumulators->pop();
        }
        acc->states->pop_back();
    }
}

void sf_nnue_make_null_move(void* acc_ptr) {
    auto* acc = static_cast<SFBridgeAccumulator*>(acc_ptr);
    acc->move_history.push_back(Move::none());
    acc->states->emplace_back();
    acc->pos.do_null_move(acc->states->back());
}

void sf_nnue_undo_null_move(void* acc_ptr) {
    auto* acc = static_cast<SFBridgeAccumulator*>(acc_ptr);
    if (!acc->move_history.empty()) {
        acc->move_history.pop_back();
        acc->pos.undo_null_move();
        acc->states->pop_back();
    }
}

void sf_nnue_free_accumulator(void* acc_ptr) {
    auto* acc = static_cast<SFBridgeAccumulator*>(acc_ptr);
    delete acc;
}

void sf_nnue_print_fen(void* acc_ptr) {
    auto* acc = static_cast<SFBridgeAccumulator*>(acc_ptr);
    std::cout << "Stockfish FEN: " << acc->pos.fen() << std::endl;
}
}

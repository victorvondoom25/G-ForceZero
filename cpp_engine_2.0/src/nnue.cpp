#include "nnue.hpp"
#include <stdexcept>
#include <iostream>

namespace nnue {

void load_weights(const std::string& filepath) {
    sf_nnue_init(filepath.c_str());
}

void init_accumulator(const chess::Board& board, Accumulator& acc) {
    if (acc.acc_ptr) {
        sf_nnue_free_accumulator(acc.acc_ptr);
    }
    acc.acc_ptr = sf_nnue_create_accumulator(board.getFen().c_str());
}

void update_accumulator(const chess::Board& board, const chess::Move& move, Accumulator& acc) {
    if (!acc.acc_ptr) return;
    std::string uci_move = chess::uci::moveToUci(move);
    sf_nnue_update_accumulator(acc.acc_ptr, uci_move.c_str());
}

void undo_accumulator(const chess::Board& board, const chess::Move& move, Accumulator& acc) {
    if (!acc.acc_ptr) return;
    std::string uci_move = chess::uci::moveToUci(move);
    sf_nnue_undo_accumulator(acc.acc_ptr, uci_move.c_str());
}

void make_null_move_accumulator(Accumulator& acc) {
    if (!acc.acc_ptr) return;
    sf_nnue_make_null_move(acc.acc_ptr);
}

void undo_null_move_accumulator(Accumulator& acc) {
    if (!acc.acc_ptr) return;
    sf_nnue_undo_null_move(acc.acc_ptr);
}

int evaluate(const Accumulator& acc, chess::Color side_to_move) {
    if (!acc.acc_ptr) return 0;
    int score = sf_nnue_evaluate(acc.acc_ptr);
    // Stockfish 16.1 evaluate() returns score from White's perspective!
    // We need to return score from side_to_move's perspective.
    return (side_to_move == chess::Color::WHITE) ? score : -score;
}

} // namespace nnue

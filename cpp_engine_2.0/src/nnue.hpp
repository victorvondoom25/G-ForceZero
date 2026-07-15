#ifndef NNUE_HPP
#define NNUE_HPP

#include <string>
#include "chess.hpp"

namespace nnue {

extern "C" {
    void sf_nnue_init(const char* net_path);
    void* sf_nnue_create_accumulator(const char* fen);
    void sf_nnue_update_accumulator(void* acc, const char* uci_move);
    void sf_nnue_undo_accumulator(void* acc, const char* uci_move);
    void sf_nnue_make_null_move(void* acc);
    void sf_nnue_undo_null_move(void* acc);
    int sf_nnue_evaluate(void* acc);
    void sf_nnue_free_accumulator(void* acc);
}

class Accumulator {
public:
    void* acc_ptr;

    Accumulator() : acc_ptr(nullptr) {}

    ~Accumulator() {
        if (acc_ptr) {
            sf_nnue_free_accumulator(acc_ptr);
        }
    }

    // Disable copying because state is complex
    Accumulator(const Accumulator&) = delete;
    Accumulator& operator=(const Accumulator&) = delete;

    // Allow moving
    Accumulator(Accumulator&& other) noexcept {
        acc_ptr = other.acc_ptr;
        other.acc_ptr = nullptr;
    }
    Accumulator& operator=(Accumulator&& other) noexcept {
        if (this != &other) {
            if (acc_ptr) sf_nnue_free_accumulator(acc_ptr);
            acc_ptr = other.acc_ptr;
            other.acc_ptr = nullptr;
        }
        return *this;
    }
};

void load_weights(const std::string& filepath);
void init_accumulator(const chess::Board& board, Accumulator& acc);

// We change update to mutate in place
void update_accumulator(const chess::Board& board, const chess::Move& move, Accumulator& acc);
void undo_accumulator(const chess::Board& board, const chess::Move& move, Accumulator& acc);
void make_null_move_accumulator(Accumulator& acc);
void undo_null_move_accumulator(Accumulator& acc);

int evaluate(const Accumulator& acc, chess::Color side_to_move);

} // namespace nnue

#endif

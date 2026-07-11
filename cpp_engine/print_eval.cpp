#include "nnue.hpp"
#include "chess.hpp"
#include <iostream>
int main() {
    nnue::load_weights("nnue_weights.bin");
    chess::Board board("rnb2rk1/ppp1p1b1/3p2pp/3n1pN1/2qP1B2/6P1/PP2PPBP/R2QR1K1 w - - 0 12");
    nnue::Accumulator acc;
    nnue::refresh_accumulator(board, chess::Color::WHITE, acc);
    nnue::refresh_accumulator(board, chess::Color::BLACK, acc);
    std::cout << "NNUE Eval: " << nnue::evaluate(acc, board.sideToMove()) << std::endl;
    return 0;
}

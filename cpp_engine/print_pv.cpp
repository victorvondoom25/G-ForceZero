#include <iostream>
#include "chess.hpp"

using namespace chess;

int main() {
    Board board("r1b1kb1r/pp1ppppp/2n2n2/q7/3NP3/2N5/PPP2PPP/R1BQKB1R b KQkq - 0 4");
    Move m1 = uci::uciToMove(board, "c6d4"); // just an example to check FEN
    // Let's use FEN at move 7 (White just played 7. f4)
    // 1. e4 c5 2. Nf3 Nc6 3. d4 cxd4 4. Nxd4 Qa5+ 5. Nc3 Nf6 6. Nb3 Qe5 7. f4
    Board b("r1b1kb1r/pp1ppppp/2n2n2/4q3/5P2/1NN5/PPP1P1PP/R1BQKB1R b KQkq - 0 7");
    std::cout << b.getFen() << "\n";
    return 0;
}

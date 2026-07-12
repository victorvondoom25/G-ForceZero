#include <iostream>
#include "chess.hpp"
using namespace chess;

int main() {
    Board b;
    b.setFen("N2r1bnr/1p1k1ppp/p1b1p3/8/4p3/P7/1PP2PPP/1RB1KB1R w K - 3 12");
    
    Movelist moves;
    movegen::legalmoves(moves, b);
    std::cout << "White moves from FEN:\n";
    for(auto m : moves) {
        std::cout << "Move: " << uci::moveToUci(m) << "\n";
    }
    return 0;
}

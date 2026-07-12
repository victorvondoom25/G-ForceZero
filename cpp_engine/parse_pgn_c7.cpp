#include <iostream>
#include "chess.hpp"
using namespace chess;

int main() {
    Board b;
    b.setFen("3r1bnr/1pNk1ppp/p1b1p3/8/4p3/P7/1PP2PPP/1RB1KB1R w K - 2 12");
    Movelist moves;
    movegen::legalmoves(moves, b);
    for(auto m : moves) {
        if (m.from() == Square::underlying::SQ_C7)
            std::cout << "Move: " << uci::moveToUci(m) << "\n";
    }
    return 0;
}

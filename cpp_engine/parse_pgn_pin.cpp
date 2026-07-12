#include <iostream>
#include "chess.hpp"
using namespace chess;

int main() {
    Board b;
    b.setFen("N2r1bnr/1p1k1ppp/p1b1p3/8/4p3/P7/1PP2PPP/1RB1KB1R b K - 3 12");
    
    std::cout << "Pinned pieces: " << b.pinners(~b.sideToMove()) << "\n";
    std::cout << "Blockers: " << b.blockersForKing(b.sideToMove()) << "\n";

    return 0;
}

#include <iostream>
#include "chess.hpp"
using namespace chess;

int main() {
    Board b;
    b.setFen("3rkbnr/1pN2ppp/p1b1p3/8/4p3/P7/1PP2PPP/1RB1KB1R b Kk - 1 11"); // after Nc7+
    
    std::string token;
    b.makeMove(uci::uciToMove(b, "e8d7"));
    b.makeMove(uci::uciToMove(b, "c1f4")); // Bf4
    
    std::cout << "FEN after Bf4: " << b.getFen() << "\n";
    
    Movelist moves;
    movegen::legalmoves(moves, b);
    for(auto m : moves) {
        std::cout << "Move: " << uci::moveToUci(m) << "\n";
    }
    return 0;
}

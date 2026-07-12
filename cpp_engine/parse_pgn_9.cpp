#include <iostream>
#include "chess.hpp"
using namespace chess;

int main() {
    Board b;
    std::string moves_str = "b1c3 c7c5 g1f3 b8c6 a1b1 d7d5 d2d4 e7e6 a2a3 c5d4 f3d4 c8d7 e2e4 d5e4 d4c6 d7c6 d1d8";
    b.setFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    
    std::string token;
    size_t pos = 0;
    while ((pos = moves_str.find(" ")) != std::string::npos) {
        token = moves_str.substr(0, pos);
        b.makeMove(uci::uciToMove(b, token));
        moves_str.erase(0, pos + 1);
    }
    b.makeMove(uci::uciToMove(b, moves_str));
    
    Movelist moves;
    movegen::legalmoves(moves, b);
    for(auto m : moves) {
        std::cout << "Move: " << uci::moveToUci(m) << "\n";
    }
    return 0;
}

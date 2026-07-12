#include <iostream>
#include "chess.hpp"
using namespace chess;

int main() {
    Board b;
    b.setFen("N2r1bnr/1p1k1ppp/p1b1p3/8/4p3/P7/1PP2PPP/1RB1KB1R b K - 3 12");
    
    std::cout << "White Rooks: " << b.pieces(PieceType::ROOK, Color::WHITE) << "\n";
    std::cout << "Black Rooks: " << b.pieces(PieceType::ROOK, Color::BLACK) << "\n";
    std::cout << "White Bishops: " << b.pieces(PieceType::BISHOP, Color::WHITE) << "\n";
    std::cout << "Black Bishops: " << b.pieces(PieceType::BISHOP, Color::BLACK) << "\n";

    return 0;
}

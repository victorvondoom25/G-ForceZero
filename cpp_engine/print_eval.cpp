#include <iostream>
#include "chess.hpp"

// Forward declare the evaluate function
int classical_evaluate(const chess::Board& board);

// We need to compile this against nnue_engine.cpp but let's just copy the evaluate logic

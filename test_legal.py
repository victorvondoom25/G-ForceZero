import chess
board = chess.Board("8/1b3pk1/4rn2/2rpq2p/pNpR2p1/P3P1P1/1PR1BPP1/3Q2K1 w - - 2 48")
print([board.san(m) for m in board.legal_moves])

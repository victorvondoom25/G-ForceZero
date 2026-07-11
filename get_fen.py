import chess

board = chess.Board("8/1b3pk1/4rn2/1r1pq2p/pNpR2p1/P2BP1P1/1PR2PP1/3Q2K1 w - - 4 49")
board.push_san("Rd2")
board.push_san("cxd3")
board.push_san("Nxd3")
print("After Nxd3:", board.fen())

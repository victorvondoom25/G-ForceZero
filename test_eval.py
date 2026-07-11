import chess
import chess.engine
import os

os.chdir("cpp_engine")
engine = chess.engine.SimpleEngine.popen_uci("./nnue_engine")
board = chess.Board("8/1b3pk1/4rn2/2rpq2p/pNpR2p1/P3P1P1/1PR1BPP1/3Q2K1 w - - 2 48")
board.push_san("Bd3")
board.push_san("cxd3")
board.push_san("Nxd3")
info = engine.analyse(board, chess.engine.Limit(depth=1))
print("Engine Score for White after Nxd3:", info["score"])
engine.quit()

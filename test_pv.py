import chess
import chess.engine
import os

os.chdir("cpp_engine")
engine = chess.engine.SimpleEngine.popen_uci("./nnue_engine")
board = chess.Board("8/1b3pk1/4rn2/1r1pq2p/pNpR2p1/P2BP1P1/1P1R1PP1/3Q2K1 b - - 5 49")
board.push_san("cxd3")
board.push_san("Nxd3")
print("Board after Nxd3:")
print(board)
print("Is it White to move?", board.turn)
print("Black to move!")
info = engine.analyse(board, chess.engine.Limit(depth=5))
print("Best move for Black:", info["pv"][0] if "pv" in info else "none")
print("Score:", info["score"])
board.push(info["pv"][0])
info = engine.analyse(board, chess.engine.Limit(depth=5))
print("Best move for White:", info["pv"][0] if "pv" in info else "none")
print("Score:", info["score"])
engine.quit()

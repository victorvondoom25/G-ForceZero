import chess
import chess.engine
import os

os.chdir("cpp_engine")
engine = chess.engine.SimpleEngine.popen_uci("./nnue_engine")
board = chess.Board("r4rk1/P4pp1/2P1p3/8/1P1P2nP/2Q1P2q/5P2/R4RK1 w - - 1 33")
info = engine.analyse(board, chess.engine.Limit(depth=12))
print("Engine Score:", info["score"])
print("Engine PV:", [board.san(m) for m in info.get("pv", [])])

sf = chess.engine.SimpleEngine.popen_uci("stockfish")
info_sf = sf.analyse(board, chess.engine.Limit(depth=15))
print("Stockfish Score:", info_sf["score"])
print("Stockfish PV:", [board.san(m) for m in info_sf.get("pv", [])])
engine.quit()
sf.quit()

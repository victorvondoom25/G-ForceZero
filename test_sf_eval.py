import chess
import chess.engine

engine = chess.engine.SimpleEngine.popen_uci("stockfish")
board = chess.Board("r1b1kb1r/pp1ppppp/5n2/4q3/8/1NN5/PPP1Q1PP/R1B1KB1R b KQkq - 1 10")
info = engine.analyse(board, chess.engine.Limit(depth=15))
print("Stockfish eval:", info["score"])
engine.quit()

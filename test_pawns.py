import chess

board = chess.Board("8/1b3pk1/4rn2/2rpq2p/p2R2p1/P2NP1P1/1PR2PP1/3Q2K1 b - - 0 49")
w_pawns = board.pieces(chess.PAWN, chess.WHITE)
b_pawns = board.pieces(chess.PAWN, chess.BLACK)

score = -207
for f in range(8):
    fm = 0x0101010101010101 << f
    adj = 0
    if f > 0: adj |= 0x0101010101010101 << (f - 1)
    if f < 7: adj |= 0x0101010101010101 << (f + 1)
    
    w_here = bool(int(w_pawns) & fm)
    b_here = bool(int(b_pawns) & fm)
    
    isolated = 0
    if w_here and not (int(w_pawns) & adj):
        score -= 15
        isolated -= 15
        print(f"White isolated on file {f}")
    if b_here and not (int(b_pawns) & adj):
        score += 15
        isolated += 15
        print(f"Black isolated on file {f}")
        
    wc = bin(int(w_pawns) & fm).count('1')
    bc = bin(int(b_pawns) & fm).count('1')
    doubled = 0
    if wc > 1:
        score -= 10 * (wc - 1)
        doubled -= 10 * (wc - 1)
        print(f"White doubled on file {f}, wc={wc}")
    if bc > 1:
        score += 10 * (bc - 1)
        doubled += 10 * (bc - 1)
        print(f"Black doubled on file {f}, bc={bc}")

print("Score after pawns:", score)

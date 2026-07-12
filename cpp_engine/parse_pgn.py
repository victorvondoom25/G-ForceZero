import chess.pgn
import io

pgn = io.StringIO("""[Event "rated bullet game"]
[Site "https://lichess.org/iX2AC2IN"]
[Date "2026.07.12"]
[Round "-"]
[White "cutecassia"]
[Black "G-ForceZero"]
[Result "1-0"]
[GameId "iX2AC2IN"]
[UTCDate "2026.07.12"]
[UTCTime "06:28:52"]
[WhiteElo "2401"]
[BlackElo "2103"]
[WhiteRatingDiff "+1"]
[BlackRatingDiff "-5"]
[WhiteTitle "BOT"]
[BlackTitle "BOT"]
[Variant "Standard"]
[TimeControl "60+2"]
[ECO "A28"]
[Opening "English Opening: King's English Variation, Four Knights Variation, Flexible Line"]
[Termination "Normal"]

1. c4 e5 2. Nc3 Nf6 3. Nf3 Nc6 4. d3 Bc5 5. Nxe5 Bxf2+ 6. Kxf2 Nxe5 7. d4 Nxc4 8. e4 d5 9. exd5 Nb6 10. Bb5+ Kf8 11. Re1 Nbxd5 12. Kg1 c6 13. Nxd5 Nxd5 14. Bc4 Be6 15. Qd2 Qh4 16. Re5 Rd8 17. a3 Kg8 18. Qd3 h6 19. Bd2 b5 20. Ba2 Qg4 21. h3 Qh4 22. Rae1 Rd6 23. Bb3 Qd8 24. Qg3 Qb6 25. Qf2 Rd8 26. Bc2 Qc7 27. b3 a6 28. Kh1 Qd7 29. a4 b4 30. a5 Nc3 31. Rc5 Nd5 32. Bd1 Qb7 33. Kh2 Nf6 34. Kg1 Bd5 35. Bc2 Rc8 36. Qg3 Nh5 37. Qd6 Qa8 38. Bxb4 Rd8 39. Qc7 Rc8 40. Qe5 g6 41. Bd2 Ng7 42. Qf6 Ne8 43. Qf2 Qb7 44. Qh4 Ng7 45. Re7 Rc7 46. Re5 g5 47. Qf2 Ne6 48. Qf6 Rc8 49. Rc3 Re8 50. Rg3 Qb8 51. h4 Qd8 52. Bxg5 hxg5 53. Rexg5+ Kf8 54. Qxh8+ Ke7 55. Qe5 Qxa5 56. Kh2 Qd2 57. Be4 Rd8 58. R3g4 Bxe4 59. Rxe4 Rxd4 60. Rxd4 Qxd4 61. Qxd4 Nxd4 62. h5 f6 63. h6 fxg5 64. h7 Kd6 65. h8=Q Ne6 66. Qa8 c5 67. Qxa6+ Kd5 68. Kg1 Ke5 69. Qc6 Kf5 70. Qd5+ Kf6 71. Kh2 Ke7 72. Kg3 Kf7 73. Kg4 Kf6 74. Qd6 Kf7 75. Qd7+ Kf6 76. Qd5 Ke7 77. Kf5 Nd4+ 78. Kxg5 Nxb3 79. Qxb3 Kd6 80. g4 Ke5 81. Qc4 Kd6 82. Kf6 Kc6 83. g5 Kc7 84. Qxc5+ Kd7 85. g6 Kd8 86. Ke6 Ke8 87. Qe7# 1-0""")

game = chess.pgn.read_game(pgn)
board = game.board()
for move in game.mainline_moves():
    board.push(move)
    if board.fullmove_number == 62 and board.turn == chess.BLACK:
        print(board.fen())
        break

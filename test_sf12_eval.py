import subprocess
import urllib.request
import os

if not os.path.exists("stockfish12"):
    urllib.request.urlretrieve("https://github.com/official-stockfish/Stockfish/releases/download/sf_12/stockfish_12_linux_x64.zip", "sf12.zip")
    os.system("unzip sf12.zip && mv stockfish_12_linux_x64/stockfish_20090216_x64 stockfish12 && chmod +x stockfish12")

p = subprocess.Popen(["./stockfish12"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
p.stdin.write("position fen r1b1kb1r/pp1ppppp/5n2/4q3/8/1NN5/PPP1Q1PP/R1B1KB1R b KQkq - 1 10\n")
p.stdin.write("eval\n")
p.stdin.write("quit\n")
p.stdin.flush()
print(p.stdout.read())

import os

with open('CMakeLists.txt', 'r') as f:
    content = f.read()

content = content.replace('nnue_engine', 'gforce_engine')

with open('CMakeLists.txt', 'w') as f:
    f.write(content)

with open('../render/config.yml', 'r') as f:
    content2 = f.read()

content2 = content2.replace('nnue_engine', 'gforce_engine')

with open('../render/config.yml', 'w') as f:
    f.write(content2)

with open('../Dockerfile', 'r') as f:
    content3 = f.read()
content3 = content3.replace('nnue_engine', 'gforce_engine')
if 'brain.nnue' not in content3:
    content3 = content3.replace('RUN cp /app/G-ForceZero/cpp_engine_2.0/book.bin', 'RUN cp /app/G-ForceZero/cpp_engine_2.0/brain.nnue /app/lichess-bot/brain.nnue || true\nRUN cp /app/G-ForceZero/cpp_engine_2.0/book.bin')

with open('../Dockerfile', 'w') as f:
    f.write(content3)


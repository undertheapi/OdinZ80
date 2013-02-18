g++ -c disassembler/bytefile.cpp disassembler/z80.cpp disassembler/main.cpp
g++ bytefile.o z80.o main.o -o zdis
rm bytefile.o
rm z80.o
rm main.o

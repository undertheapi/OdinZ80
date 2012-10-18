md bin
g++ disassembler/bytefile.cpp -c
g++ disassembler/z80.cpp -c
g++ disassembler/main.cpp -c
g++ bytefile.o z80.o main.o -o bin/zdis.exe
del bytefile.o
del z80.o
del main.o

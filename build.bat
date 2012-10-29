md bin
g++ -c disassembler/bytefile.cpp disassembler/z80.cpp disassembler/main.cpp
g++ bytefile.o z80.o main.o -o bin/zdis.exe
del bytefile.o
del z80.o
del main.o

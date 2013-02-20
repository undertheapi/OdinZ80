g++ -c disassembler/bytefile.cpp disassembler/z80.cpp disassembler/main.cpp
g++ bytefile.o z80.o main.o -o zdis
rm bytefile.o
rm z80.o
rm main.o

g++ assembler/character/characterlist.cpp -c
g++ assembler/lex/tokenlist.cpp -c
g++ assembler/lex/lex.cpp -c
g++ assembler/parser/bytecode.cpp -c
g++ assembler/parser/parser.cpp -c
g++ assembler/parser/addresslist.cpp -c
g++ assembler/parser/foundlist.cpp -c
g++ assembler/parser/instructions/LDinstr.cpp -c
g++ assembler/parser/instructions/PUSHinstr.cpp -c
g++ assembler/parser/instructions/POPinstr.cpp -c
g++ assembler/parser/instructions/EXinstr.cpp -c
g++ assembler/parser/instructions/ADDinstr.cpp -c
g++ assembler/parser/instructions/ADCinstr.cpp -c
g++ assembler/parser/instructions/SUBinstr.cpp -c
g++ assembler/parser/instructions/SUBCinstr.cpp -c
g++ assembler/parser/instructions/ANDinstr.cpp -c
g++ assembler/parser/instructions/ORinstr.cpp -c
g++ assembler/parser/instructions/XORinstr.cpp -c
g++ assembler/parser/instructions/CPinstr.cpp -c
g++ assembler/parser/instructions/INCinstr.cpp -c
g++ assembler/parser/instructions/DECinstr.cpp -c
g++ assembler/main.cpp -c
g++ main.o DECinstr.o INCinstr.o XORinstr.o CPinstr.o characterlist.o tokenlist.o lex.o bytecode.o parser.o addresslist.o foundlist.o LDinstr.o PUSHinstr.o POPinstr.o EXinstr.o ADDinstr.o ADCinstr.o SUBinstr.o SUBCinstr.o ANDinstr.o ORinstr.o -o odin
rm characterlist.o 
rm tokenlist.o 
rm lex.o 
rm bytecode.o 
rm parser.o 
rm foundlist.o
rm addresslist.o
rm LDinstr.o
rm PUSHinstr.o
rm POPinstr.o
rm EXinstr.o
rm ADDinstr.o
rm ADCinstr.o
rm SUBinstr.o
rm SUBCinstr.o
rm ANDinstr.o
rm ORinstr.o
rm XORinstr.o
rm CPinstr.o
rm INCinstr.o
rm DECinstr.o
rm main.o
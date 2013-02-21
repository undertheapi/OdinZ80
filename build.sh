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
g++ assembler/parser/instructions/RLCinstr.cpp -c
g++ assembler/parser/instructions/RLinstr.cpp -c
g++ assembler/parser/instructions/RRCinstr.cpp -c
g++ assembler/parser/instructions/RRinstr.cpp -c
g++ assembler/parser/instructions/SLAinstr.cpp -c
g++ assembler/parser/instructions/SRAinstr.cpp -c
g++ assembler/parser/instructions/SRLinstr.cpp -c
g++ assembler/parser/instructions/BITinstr.cpp -c
g++ assembler/parser/instructions/SETinstr.cpp -c
g++ assembler/parser/instructions/RESinstr.cpp -c
g++ assembler/parser/instructions/JPinstr.cpp -c
g++ assembler/parser/instructions/JRinstr.cpp -c
g++ assembler/parser/instructions/CALLinstr.cpp -c
g++ assembler/parser/instructions/RETinstr.cpp -c
g++ assembler/parser/instructions/RSTinstr.cpp -c
g++ assembler/parser/instructions/INinstr.cpp -c
g++ assembler/parser/instructions/OUTinstr.cpp -c
g++ assembler/main.cpp -c
g++ main.o INinstr.o OUTinstr.o RSTinstr.o RETinstr.o CALLinstr.o JRinstr.o JPinstr.o SETinstr.o RESinstr.o BITinstr.o SRLinstr.o SLAinstr.o SRAinstr.o RRinstr.o RRCinstr.o RLinstr.o RLCinstr.o DECinstr.o INCinstr.o XORinstr.o CPinstr.o characterlist.o tokenlist.o lex.o bytecode.o parser.o addresslist.o foundlist.o LDinstr.o PUSHinstr.o POPinstr.o EXinstr.o ADDinstr.o ADCinstr.o SUBinstr.o SUBCinstr.o ANDinstr.o ORinstr.o -o odin
rm INinstr.o
rm OUTinstr.o
rm RSTinstr.o
rm RETinstr.o
rm CALLinstr.o
rm JRinstr.o
rm JPinstr.o
rm SETinstr.o
rm RESinstr.o
rm BITinstr.o
rm SRLinstr.o
rm SLAinstr.o
rm SRAinstr.o
rm RRinstr.o
rm RRCinstr.o
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
rm RLCinstr.o
rm RLinstr.o
rm main.o

g++ -c disassembler/bytefile.cpp disassembler/z80.cpp disassembler/main.cpp
g++ bytefile.o z80.o main.o -o zdis.exe
del bytefile.o
del z80.o
del main.o

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
g++ assembler/general/ctype.cpp -c
g++ assembler/general/meta.cpp -c
g++ assembler/main.cpp -c
g++ main.o meta.o ctype.o INinstr.o OUTinstr.o RSTinstr.o RETinstr.o CALLinstr.o JRinstr.o JPinstr.o SETinstr.o RESinstr.o BITinstr.o SRLinstr.o SLAinstr.o SRAinstr.o RRinstr.o RRCinstr.o RLinstr.o RLCinstr.o DECinstr.o INCinstr.o XORinstr.o CPinstr.o characterlist.o tokenlist.o lex.o bytecode.o parser.o addresslist.o foundlist.o LDinstr.o PUSHinstr.o POPinstr.o EXinstr.o ADDinstr.o ADCinstr.o SUBinstr.o SUBCinstr.o ANDinstr.o ORinstr.o -o odin.exe
del INinstr.o
del OUTinstr.o
del RSTinstr.o
del RETinstr.o
del CALLinstr.o
del JRinstr.o
del JPinstr.o
del SETinstr.o
del RESinstr.o
del BITinstr.o
del SRLinstr.o
del SLAinstr.o
del SRAinstr.o
del RRinstr.o
del RRCinstr.o
del characterlist.o 
del tokenlist.o 
del lex.o 
del bytecode.o 
del parser.o 
del foundlist.o
del addresslist.o
del LDinstr.o
del PUSHinstr.o
del POPinstr.o
del EXinstr.o
del ADDinstr.o
del ADCinstr.o
del SUBinstr.o
del SUBCinstr.o
del ANDinstr.o
del ORinstr.o
del XORinstr.o
del CPinstr.o
del INCinstr.o
del DECinstr.o
del RLCinstr.o
del RLinstr.o
del ctype.o
del meta.o
del main.o

g++ debugger/ram/ram.cpp -c
g++ debugger/registers/registers.cpp -c
g++ debugger/registers/specialregisters.cpp -c
g++ debugger/general/convert.cpp -c
g++ debugger/cpu/z80cpu.cpp -c
g++ debugger/main.cpp -c
g++ ram.o registers.o specialregisters.o z80cpu.o main.o convert.o -o zdebug.exe
del ram.o
del registers.o
del specialregisters.o
del z80cpu.o
del convert.o
del main.o

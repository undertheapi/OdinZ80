g++ ../character/characterlist.cpp -c
g++ ../lex/tokenlist.cpp -c
g++ ../lex/lex.cpp -c
g++ ../parser/bytecode.cpp -c
g++ ../parser/parser.cpp -c
g++ ../parser/addresslist.cpp -c
g++ ../parser/foundlist.cpp -c
g++ testparser.cpp -c
g++ ../parser/instructions/LDinstr.cpp -c
g++ ../parser/instructions/PUSHinstr.cpp -c
g++ ../parser/instructions/POPinstr.cpp -c
g++ ../parser/instructions/EXinstr.cpp -c
g++ ../parser/instructions/ADDinstr.cpp -c
g++ ../parser/instructions/ADCinstr.cpp -c
g++ ../parser/instructions/SUBinstr.cpp -c
g++ ../parser/instructions/SUBCinstr.cpp -c
g++ ../parser/instructions/ANDinstr.cpp -c
g++ ../parser/instructions/ORinstr.cpp -c
g++ ../parser/instructions/XORinstr.cpp -c
g++ ../parser/instructions/CPinstr.cpp -c
g++ ../parser/instructions/INCinstr.cpp -c
g++ ../parser/instructions/DECinstr.cpp -c
g++ DECinstr.o INCinstr.o XORinstr.o CPinstr.o characterlist.o tokenlist.o lex.o bytecode.o parser.o addresslist.o foundlist.o testparser.o LDinstr.o PUSHinstr.o POPinstr.o EXinstr.o ADDinstr.o ADCinstr.o SUBinstr.o SUBCinstr.o ANDinstr.o ORinstr.o -o unittest
./unittest
rm characterlist.o 
rm tokenlist.o 
rm lex.o 
rm bytecode.o 
rm parser.o 
rm testparser.o
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
rm unittest


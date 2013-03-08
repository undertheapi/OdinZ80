g++ ../lex/tokenlist.cpp -c
g++ ../lex/lex.cpp -c
g++ ../character/characterlist.cpp -c
g++ ../general/ctype.cpp -c
g++ testlex.cpp -c
g++ tokenlist.o lex.o characterlist.o ctype.o testlex.o -o unittest.exe
unittest
del tokenlist.o
del lex.o
del characterlist.o
del ctype.o
del testlex.o
del unittest.exe

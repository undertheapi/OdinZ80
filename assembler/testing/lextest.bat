g++ ../lex/tokenlist.cpp -c
g++ ../lex/lex.cpp -c
g++ ../character/characterlist.cpp -c
g++ testlex.cpp -c
g++ tokenlist.o lex.o characterlist.o testlex.o -o unittest.exe
unittest
del tokenlist.o
del lex.o
del characterlist.o
del testlex.o
del unittest.exe

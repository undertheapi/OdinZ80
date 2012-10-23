g++ ../lex/tokenlist.cpp -c
g++ ../lex/lex.cpp -c
g++ ../character/characterlist.cpp -c
g++ testlex.cpp -c
g++ tokenlist.o lex.o characterlist.o testlex.o -o unittest
./unittest
rm tokenlist.o
rm lex.o
rm characterlist.o
rm testlex.o
rm unittest

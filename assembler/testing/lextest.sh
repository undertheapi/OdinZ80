g++ ../lex/tokenlist.cpp -c
g++ ../lex/lex.cpp -c
g++ ../character/characterlist.cpp -c
g++ ../general/ctype.cpp -c
g++ testlex.cpp -c
g++ tokenlist.o lex.o characterlist.o ctype.o testlex.o -o unittest
./unittest
rm tokenlist.o
rm lex.o
rm characterlist.o
rm ctype.o
rm testlex.o
rm unittest

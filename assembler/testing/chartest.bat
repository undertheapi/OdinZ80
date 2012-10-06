g++ testcharacterlist.cpp -c
g++ ../character/characterlist.cpp -c
g++ testcharacterlist.o characterlist.o -o unittest.exe
unittest
del testcharacterlist.o
del characterlist.o
del unittest.exe

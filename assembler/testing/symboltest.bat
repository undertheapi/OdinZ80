g++ ../symbol_table/symbol_table.cpp -c
g++ testsymbol.cpp -c
g++ symbol_table.o testsymbol.o -o unittest.exe
unittest
del symbol_table.o
del testsymbol.o
del unittest.exe

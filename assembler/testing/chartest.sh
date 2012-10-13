#!/bin/bash
#This is the chartest.sh bash file for compiling and running
#the unit test testcharacerlist.
g++ ../character/characterlist.cpp -c
g++ testcharacterlist.cpp -c
g++ characterlist.o testcharacterlist.o -o unittest
./unittest
rm characterlist.o
rm testcharacterlist.o
rm unittest


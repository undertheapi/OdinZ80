/*
	Copyright (c) 2014, Gareth Richardson
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this
	   list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright notice,
	   this list of conditions and the following disclaimer in the documentation
	   and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
	ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	The views and conclusions contained in the software and documentation are those
	of the authors and should not be interpreted as representing official policies,
	either expressed or implied, of the FreeBSD Project.
*/

/*
	file name: assembler.cpp
	date created: 11/11/2014
	date updated: 21/11/2014
	author: Gareth Richardson
	description: The class header for Assembler. Used as the container for the components
	of the rest of the Z80 Assembler.
*/

#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>

using namespace std;

#include "assembler.hpp"

void Assembler::init() {
	Assembler::cList = new CharacterList;
	Assembler::tList = new TokenList;
	Assembler::bCodeObj = new ByteCode;
}

void Assembler::execute() {
	Assembler::populateCharacterList();
	Assembler::populateTokens();
	Assembler::runParser();
}

void Assembler::populateCharacterList() {
	ifstream file(Assembler::fileName.c_str(), ios::binary);
	
	char val;
	
	while (file.read(static_cast<char*>(&val), sizeof(unsigned char)))
		Assembler::cList->push(val);
	
	file.close();
	
	if (Assembler::cList->errorState) {
		if (cList->errorState & INVALID_CHAR == INVALID_CHAR) {
			Assembler::errorString = "Invalid character in the file.\n";
		} else if (cList->errorState & LIST_FULL == LIST_FULL) {
			Assembler::errorString = "The source file is too big.\n";
		} else if (cList->errorState & LIST_EMPTY == LIST_EMPTY) {
			Assembler::errorString = "An unexpected error has happen.\n";
		}
		Assembler::errorState = true;
	}
	
	Assembler::cList->finishedFile();
}

void Assembler::populateTokens() {
	if (!Assembler::errorState) {
		Lex lexObj(Assembler::cList, Assembler::tList);
		lexObj.run();
		
		if (lexObj.checkForError()) {
			Assembler::errorString = lexObj.getError();
			Assembler::errorState = true;
		}
	}
}

void Assembler::runParser() {
	if (!Assembler::errorState) {
		Z80Parser parserObj(Assembler::tList, Assembler::bCodeObj);
		parserObj.run();
		
		if (parserObj.checkState()) {
			Assembler::errorString = parserObj.getError();
			Assembler::errorState = true;
		}
	}
}

Assembler::Assembler(string fileLocation) {
	Assembler::fileName = fileLocation;
	Assembler::init();
	Assembler::execute();
}

ByteCode* Assembler::getCode() {
	return Assembler::bCodeObj;
}

bool Assembler::error() {
	return Assembler::errorState;
}

string Assembler::getError() {
	return Assembler::errorString;
}

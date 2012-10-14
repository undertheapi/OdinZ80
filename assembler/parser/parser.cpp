/*
	Copyright (c) 2012, Gareth Richardson
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
	file name: parser.cpp
	date created: 28/09/2012
	date updated: 28/09/2012
	author: Gareth Richardson
	description: This is the Z80 parser. Give it a TokenList object and it will
	parse it and output the machine code for it.
*/

#include <string>

using namespace std;

#include "../lex/tokentype.hpp"
#include "../lex/tokenlist.hpp"
#include "bytecode.hpp"
#include "parser.hpp"

void Z80Parser::init() {
	Z80Parser::tList = NULL;
	Z80Parser::bCode = NULL;
	Z80Parser::errorState = false;
	Z80Parser::errorString = "";
	Z80Parser::address = 0;
}

Z80Parser::Z80Parser(TokenList* tPointer, ByteCode* bPointer) {
	Z80Parser::init();
	Z80Parser::tList = tPointer;
	Z80Parser::bCode = bPointer;
}

void Z80Parser::run() {
	while (!Z80Parser::errorState && !Z80Parser::tList->peekTokenType() == END_OF_FILE) {
		if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == ADC) {
			Z80Parser::tList->pop();
			if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == A) {
				
			}
		}
	}
}

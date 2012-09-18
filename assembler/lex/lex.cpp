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
	file name: lex.hpp
	date created: 29/08/2012
	date updated: 12/09/2012
	author: Gareth Richardson
	description: This is the Lexical Analysis for the Odin assembler.
*/

#include <string>

using namespace std;

#include "lex.hpp"

#include "tokentype.hpp"

/*
	This is a custom method that checks that a CHARACTER is an alphabetical character.
	That is a character between A and Z or a and z.
*/
bool isAlphabetical(CHARACTER value) {
	return (value >= 'a' && value <= 'z') || (value >= 'A' && value <= 'Z');
}

/*
	This is another custom method class that checks that a character is numerical in
	the decimal sense. Between 0 and 9.
*/
bool isNumerical(CHARACTER value) {
	return value >= '0' && value <= '9';
}

TokenNodePtr Lex::getToken() {
	TokenNodePtr newNode = new TokenNode;
	/*
		this is getting rid of the space characters from the CharacterList class.
	*/
	while (!Lex::cList->isEmpty() && Lex::cList->peekValue() == '\t' && Lex::cList->peekValue() == ' ') {
		Lex::cList->pop();
	}
	
	/*
		for getting rid of the comments. Comments are only single line, so we read from a ';' to a
		new line character.
	*/
	if (!Lex::cList->isEmpty() && Lex::cList->peekValue() == ';') {
		Lex::cList->pop();
		while (!Lex::cList->isEmpty() && Lex::cList->peekValue() != '\n') {
			Lex::cList->pop();
		}
	}
	
	if (Lex::cList->isEmpty()) {
		//send end of file state back.
		newNode->type = EOF;
		newNode->value = "";
		newNode->lineNumber = -1;
		newNode->fileName = NULL;
		newNode->next = NULL;
		return newNode;
	}
	
	/*
		This is the string that collects the token value.
	*/
	string retValue = "";
	
	if (isAlphabetical(Lex::cList->peekValue())) {
		/*
		while (Lex::cList->peekValue() >= 'a' && Lex::cList->peekValue() <= 'z' || Lex::cList->peekValue() >= 'A' && Lex::cList->peekValue() <= 'Z') {
			retValue += Lex::cList->peekValue();
			Lex::cList->pop();
		}
		*/
		int line;
		char* file;
		
		while (!Lex::cList->isEmpty() && (isAlphabetical(Lex::cList->peekValue()) || isNumerical(Lex::cList->peekValue()))) {
			retValue += Lex::cList->peekValue();
			line = Lex::cList->peekLineNumber();
			file = Lex::cList->peekFileName();
			Lex::cList->pop();
		}
		/*
			**here have some sort of token type checking to check for keywords.
		*/
		if (retValue.compare("ADC") || retValue.compare("Adc") || retValue.compare("adc")) {
			newNode->type = ADC;
			newNode->lineNumber = line;
			newNode->fileName = file;
			newNode->next = NULL;
		} else if (retValue.compare("ADD") || retValue.compare("Add") || retValue.compare("add")) {
			
		} else if (retValue.compare("AND") || retValue.compare("And") || retValue.compare("and")) {
			
		}
	} else if (isNumerical(Lex::cList->peekValue())) {
		while (!Lex::cList->isEmpty() && (isNumerical(Lex::cList->peekValue()) || isAlphabetical(Lex::cList->peekValue()))) {
			retValue += Lex::cList->peekValue();
			Lex::cList->pop();
		}
	} else if (Lex::cList->peekValue() == '\"') {
		Lex::cList->pop();
		while (Lex::cList->peekValue() != '\"') {
			retValue += Lex::cList->peekValue();
		}
		Lex::cList->pop();
	}
}

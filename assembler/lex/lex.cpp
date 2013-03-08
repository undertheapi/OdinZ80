/*
	Copyright (c) 2013, Gareth Richardson
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
	date updated: 09/03/2013
	author: Gareth Richardson
	description: This is the Lexical Analyserd for the Odin assembler.
*/

#include <string>

using namespace std;

#include "../character/characterlist.hpp"
#include "../general/ctype.hpp"
#include "tokentype.hpp"
#include "tokenlist.hpp"
#include "lex.hpp"

Lex::Lex(CharacterList* cList, TokenList* tList) {
	Lex::cList = cList;
	Lex::tList = tList;
	/*
		there are no errors to begin with, so do not
		set the errorState.
	*/
	Lex::errorState = false;
	Lex::lineNumber = 1;
}

TokenNodePtr Lex::getToken() {
	TokenNodePtr newNode = new TokenNode;
	newNode->type = 170;
	newNode->value = "";
	newNode->lineNumber = Lex::lineNumber;
	newNode->next = NULL;

	/*
		for getting rid of the comments. Comments are only single line, so we read from a ';' to a
		new line character.
	*/
	if (!Lex::cList->isEmpty() && Lex::cList->peekValue()  == ';') {
		Lex::cList->pop();
		while (!Lex::cList->isEmpty() && Lex::cList->peekValue() != '\n') {
			Lex::cList->pop();
		}
	}

	/*
		this is getting rid of the space characters from the CharacterList class.
	*/
	while (!Lex::cList->isEmpty() && (Lex::cList->peekValue() == '\t' || Lex::cList->peekValue() == ' ')) {
		Lex::cList->pop();
	}

	/*
		This is here to stop ANY errors happening.
	*/
	if (Lex::cList->isEmpty()) {
		//send end of file state back.
		newNode->type = END_OF_FILE;
		newNode->value = "";
		newNode->lineNumber = -1;

		return newNode;
	}
	
	/*
		This is here to fix a bug in the program
	*/
	if (!Lex::cList->isEmpty() && Lex::cList->peekValue()  == ';') {
		Lex::cList->pop();
		while (!Lex::cList->isEmpty() && Lex::cList->peekValue() != '\n') {
			Lex::cList->pop();
		}
	}

	/*
		This is the string that collects the token value.
	*/
	string retValue = "";

	if (isAlphabetical(Lex::cList->peekValue())) {

		while (!Lex::cList->isEmpty() && (Lex::cList->peekValue() == '_' || isAlphabetical(Lex::cList->peekValue()) || isNumerical(Lex::cList->peekValue()))) {
			retValue += Lex::cList->peekValue();
			Lex::cList->pop();
		}
		
		const char* instructionArray[] = {
				"adc", "add", "and", "bit", "call", 
				"ccf", "cp", "cpd", "cpdr", "cpi", 
				"cpir", "cpl", "daa", "dec", "di",
				"ei", "ex", "exx", "halt", "im", "in",
				"inc", "ind", "indr", "ini", "inir",
				"jp", "jr", "ld", "ldd", "lddr", "ldi",
				"ldir", "neg", "nop", "or", "otdr", "otir",
				"out", "outd", "outi", "pop", "push",
				"res", "ret", "reti", "retn", "rl", "rla",
				"rlc", "rlca", "rld", "rr", "rra", "rrc",
				"rrca", "rrd", "rst", "sub", "subc", "scf", 
				"set", "sla", "sra", "srl", "xor"
		};
		
		int tokenNumber = 0;
		bool foundToken = false;
		while (tokenNumber < 67 && !foundToken) {
			if (!retValue.compare(instructionArray[tokenNumber]) || 
				!retValue.compare(toUpper(instructionArray[tokenNumber])) ||
				!retValue.compare(toFirstCharUpper(instructionArray[tokenNumber]))) {
				newNode->type = tokenNumber;
				foundToken = true;
			}
			tokenNumber++;
		}
		
		 if (foundToken) {
		 	return newNode;
		 }
		
		/*
			The rest of the key words are checked here. Such as unique ways of writing an
			instruction eg BIT can be declared as BT.
			If the string does not match anything here, it will return a Token Type of ATOM.
		*/
		if (!retValue.compare("BT") || !retValue.compare("Bt") || !retValue.compare("bt")) {
			newNode->type = BIT;
		} else if (!retValue.compare("HLT") || !retValue.compare("Hlt") || !retValue.compare("hlt")) {
			newNode->type = HALT;
		} else if (!retValue.compare("JMP") || !retValue.compare("Jmp") || !retValue.compare("jmp")) {
			newNode->type = JP;
		} else if (!retValue.compare("LDDI") || !retValue.compare("Lddi") || !retValue.compare("lddi")) {
			newNode->type = LDI;
		} else if ( !retValue.compare("SBC") || !retValue.compare("Sbc") || !retValue.compare("sbc")) {
			newNode->type = SUBC;
		} else if (!retValue.compare("A") || !retValue.compare("a")) {
			newNode->type = A;
		} else if (!retValue.compare("F") || !retValue.compare("f")) {
			newNode->type = F;
		} else if (!retValue.compare("B") || !retValue.compare("b")) {
			newNode->type = B;
		} else if (!retValue.compare("C") || !retValue.compare("c")) {
			newNode->type = C;
		} else if (!retValue.compare("D") || !retValue.compare("d")) {
			newNode->type = D;
		} else if (!retValue.compare("E") || !retValue.compare("e")) {
			newNode->type = E;
		} else if (!retValue.compare("H") || !retValue.compare("h")) {
			newNode->type = H;
		} else if (!retValue.compare("L") || !retValue.compare("l")) {
			newNode->type = L;
		} else if (!retValue.compare("BC") || !retValue.compare("bc") || !retValue.compare("Bc")) {
			newNode->type = BC;
		} else if (!retValue.compare("DE") || !retValue.compare("de") || !retValue.compare("De")) {
			newNode->type = DE;
		} else if (!retValue.compare("HL") || !retValue.compare("hl") || !retValue.compare("Hl")) {
			newNode->type = HL;
		} else if (!retValue.compare("I") || !retValue.compare("i")) {
			newNode->type = I;
		} else if (!retValue.compare("R") || !retValue.compare("r")) {
			newNode->type = R;
		} else if (!retValue.compare("IX") || !retValue.compare("ix") || !retValue.compare("Ix")) {
			newNode->type = IX;
		} else if (!retValue.compare("IY") || !retValue.compare("iy") || !retValue.compare("Iy")) {
			newNode->type = IY;
		} else if (!retValue.compare("PC") || !retValue.compare("pc") || !retValue.compare("Pc")) {
			newNode->type = PC;
		} else if (!retValue.compare("SP") || !retValue.compare("sp") || !retValue.compare("Sp")) {
			newNode->type = SP;
		} else if (!retValue.compare("AF") || !retValue.compare("af") || !retValue.compare("Af")) {
			newNode->type = AF;
		} else if (!retValue.compare("CPU") || !retValue.compare("Cpu") || !retValue.compare("cpu")) {
			newNode->type = CPU;
		} else if (!retValue.compare("DB") || !retValue.compare("Db") || !retValue.compare("db") || !retValue.compare("BYTE") || !retValue.compare("Byte") || !retValue.compare("byte")) {
			newNode->type = DB;
		} else if (!retValue.compare("DW") || !retValue.compare("Dw") || !retValue.compare("dw") || !retValue.compare("WORD") || !retValue.compare("Word") || !retValue.compare("word")) {
			newNode->type = DW;
		} else if (!retValue.compare("ORG") || !retValue.compare("Org") || !retValue.compare("org")) {
			newNode->type = ORG;
		} else if (!retValue.compare("REP") || !retValue.compare("Rep") || !retValue.compare("rep")) {
			newNode->type = REP;
		} else if (!retValue.compare("SPECREP") || !retValue.compare("SPECREP") || !retValue.compare("SPECREP")) {
			newNode->type = SPECREP;
		} else if (!retValue.compare("M") || !retValue.compare("m")) {
			newNode->type = M;
		} else if (!retValue.compare("NC") || !retValue.compare("nc")) {
			newNode->type = NC;
		} else if (!retValue.compare("NZ") || !retValue.compare("nz")) {
			newNode->type = NZ;
		} else if (!retValue.compare("P") || !retValue.compare("p")) {
			newNode->type = P;
		} else if (!retValue.compare("PE") || !retValue.compare("pe")) {
			newNode->type = PE;
		} else if (!retValue.compare("PO") || !retValue.compare("po")) {
			newNode->type = PO;
		} else if (!retValue.compare("Z") || !retValue.compare("z")) {
			newNode->type = Z;
		} else {
			/*
				if it is not a reserved word, it is an ATOM:
			*/
			newNode->type = ATOM;
			newNode->value = retValue;
		}
	} else if (isNumerical(Lex::cList->peekValue()) || Lex::cList->peekValue() == '$' || Lex::cList->peekValue() == '#') {
		newNode->type = NUMBER;
		newNode->value = Lex::getNumber();
	} else if (Lex::cList->peekValue() == '\"') {
		Lex::cList->pop();
		while (Lex::cList->peekValue() != '\"' && !Lex::errorState) {
			if (isPrintable(Lex::cList->peekValue())) {
				retValue += Lex::cList->peekValue();
			} else if (Lex::cList->isEmpty()) {
				/*
					incase we reach no more character in the file,
					obviously, a string left open and not closed.
					Sets error state accordingly.
				*/
				Lex::errorState = true;
				Lex::errorString = "A string has been left open!";
			} else {
				/*
					found a bad character in the string, now set
					the error state.
				*/
				Lex::errorState = true;
				Lex::errorString = "Found an invalid character within a string at ";
				Lex::errorString += integerToString(Lex::lineNumber);
			}
			Lex::cList->pop();
		}
		// This is here to pop the end quotation on the string.
		newNode->type = STRING;
		newNode->value = retValue;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == ':') {
		newNode->type = COLON;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == ',') {
		newNode->type = COMMA;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == '\n') {
		newNode->type = NEW_LINE;
		Lex::lineNumber++;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == '[') {
		newNode->type = LEFT_BRACKET;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == '(') {
		newNode->type = LEFT_PARENT;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == ']') {
		newNode->type = RIGHT_BRACKET;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == ')') {
		newNode->type = RIGHT_PARENT;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == '+') {
		newNode->type = PLUS;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == '-') {
		newNode->type = MINUS;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == '*') {
		newNode->type = MULTIPLY;
		Lex::cList->pop();
	} else {
		/*
			if the program gets to this point, there is an obvious error. The error is most
			likely an invalid character in the source code. For example: # @ etc.
		*/
		Lex::errorState = true;
		Lex::errorString = "An invalid character is in the source code at ";
		int lineNumber = Lex::lineNumber;
		Lex::errorString += integerToString(lineNumber);
		Lex::errorString += " ";
		Lex::errorString += convertHex(Lex::cList->peekValue());
		Lex::cList->pop();
	}

	return newNode;
}

string Lex::getNumber() {
	/*
		Dec:
		342
		0d90
		0D342

		Hex:
		0x3f
		0h34
		$3243
		#5454

		Bin:
		0b01110
		0B101011
	*/

	string retValue = "";

	switch (Lex::cList->peekValue()) {
		case '0':
			Lex:cList->pop();
			if (!Lex::cList->isEmpty()) {
				switch (Lex::cList->peekValue()) {
					case 'd':
					case 'D':
						retValue += 'd';
						Lex::cList->pop();
						while (!Lex::cList->isEmpty() && isNumerical(Lex::cList->peekValue())) {
							retValue += Lex::cList->peekValue();
							Lex::cList->pop();
						}
						break;
					case 'x':
					case 'X':
					case 'H':
					case 'h':
						retValue += 'h';
						Lex::cList->pop();
						while (!Lex::cList->isEmpty() && isHex(Lex::cList->peekValue())) {
							retValue += Lex::cList->peekValue();
							Lex::cList->pop();
						}
						break;
					case 'b':
					case 'B':
					case 'y':	//why 'y' I will never know ...
					case 'Y':
						retValue += 'b';
						Lex::cList->pop();
						while (!Lex::cList->isEmpty() && isBinary(Lex::cList->peekValue())) {
							retValue += Lex::cList->peekValue();
							Lex::cList->pop();
						}
						break;
					default:
						string tempValue = "d";
						//Lex::cList->pop();
						while (!Lex::cList->isEmpty() && isNumerical(Lex::cList->peekValue())) {
							retValue += Lex::cList->peekValue();
							Lex::cList->pop();
						}
				}
			} else {
				retValue += "d0";
			}
			break;
		case '$':
		case '#':
			retValue += 'h';
			Lex::cList->pop();
			while (!Lex::cList->isEmpty() && isHex(Lex::cList->peekValue())) {
				retValue += Lex::cList->peekValue();
				Lex::cList->pop();
			}
			break;
		default:
			/* because we have already done validation earlier on, we have a number between 1 -> 9 */
			//Lex::cList->pop();
			retValue += 'd';
			while (!Lex::cList->isEmpty() && isNumerical(Lex::cList->peekValue())) {
				retValue += Lex::cList->peekValue();
				Lex::cList->pop();
			}
			break;
	}

	return retValue;
}

void Lex::run() {
	/*
		This variable keeps track of the last Token Type to be added to
		the TokenList. Part of a bug fix, see the end of this method.
	*/
	TOKEN_TYPE lastToken = 0;

	while (!Lex::errorState && !Lex::cList->isEmpty()) {
		TokenNodePtr newPtr = Lex::getToken();
		if (!Lex::errorState) {
			Lex::tList->push(newPtr);
			lastToken = newPtr->type;
		}
	}

	/* Bug fix, sometimes an END_OF_FILE token is not added to the end of the token list */
	if (!Lex::errorState && lastToken != END_OF_FILE) {
		TokenNodePtr newPtr = new TokenNode;
		newPtr->type = END_OF_FILE;
		newPtr->value = "";
		newPtr->lineNumber = Lex::lineNumber;
		newPtr->next = NULL;
		Lex::tList->push(newPtr);
	}
}

bool Lex::checkForError() {
	return Lex::errorState;
}

string Lex::getError() {
	return Lex::errorString;
}

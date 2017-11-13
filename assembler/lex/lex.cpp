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
	file name:		lex.cpp
	date created:	29/08/2012
	date updated:	13/11/2017
	author:			Gareth Richardson
	description:	This is the Lexical Analyser object code for the Odin assembler.
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
	/*
		Lex always starts at Line One in the file.
	*/
	Lex::lineNumber = 1;
}

bool Lex::checkKeyword(string value, string checker) {
	return !toUpper(checker).compare(value) ||
	!toLower(checker).compare(value) ||
!toFirstCharUpper(checker).compare(value);
	/*if
	(
		!toUpper(checker).compare(value) ||
		!toLower(checker).compare(value) ||
	!toFirstCharUpper(checker).compare(value))
		 {
		return true;
	}
	return false;
	if (!toUpper(checker).compare(value)) {
		return true;
	}
	if (!toLower(checker).compare(value)) {
		return true;
	}
	if (!toFirstCharUpper(checker).compare(value)) {
		return true;
	}
	return false;*/
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
		while (!Lex::cList->isEmpty() && Lex::cList->peekValue() != '\n')
			Lex::cList->pop();
	}

	/*
		this is getting rid of the space characters from the CharacterList class.
	*/
	while (!Lex::cList->isEmpty() && (Lex::cList->peekValue() == '\t' || Lex::cList->peekValue() == ' '))
		Lex::cList->pop();

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
		This is here to fix a bug in the program.
		If the line is commented out, the Assembler will accept it.
	*/
	if (!Lex::cList->isEmpty() && Lex::cList->peekValue()  == ';') {
		Lex::cList->pop();
		while (!Lex::cList->isEmpty() && Lex::cList->peekValue() != '\n')
			Lex::cList->pop();
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

		// int keywordIndex = 0;

		// while (keywordIndex != 91) {
			// if (Lex::checkKeyword(retValue, keywordArray[keywordIndex])) {
				// newNode->type = keywordIndex;
			// } else {
				// newNode->type = ATOM;
				// newNode->value = retValue;
			// }
			// ++keywordIndex;
		// }

		/*
			Here have some sort of token type checking to check for keywords. There has to be a more "effective" way
			of doing this.
			If the string does not match anything here, it will return a Token Type of ATOM.
		*/

		if (Lex::checkKeyword(retValue, "adc")) {
			newNode->type = ADC;
		} else if (Lex::checkKeyword(retValue, "add")) {
			newNode->type = ADD;
		} else if (Lex::checkKeyword(retValue, "and")) {
			newNode->type = AND;
		} else if (Lex::checkKeyword(retValue, "bit") || Lex::checkKeyword(retValue, "bt")) {
			newNode->type = BIT;
		} else if (Lex::checkKeyword(retValue, "call")) {
			newNode->type = CALL;
		} else if (Lex::checkKeyword(retValue, "ccf")) {
			newNode->type = CCF;
		} else if (Lex::checkKeyword(retValue, "cp")) {
			newNode->type = CP;
		} else if (Lex::checkKeyword(retValue, "cpd")) {
			newNode->type = CPD;
		}  else if (Lex::checkKeyword(retValue, "cpdr")) {
			newNode->type = CPDR;
		} else if (Lex::checkKeyword(retValue, "cpi")) {
			newNode->type = CPI;
		} else if (Lex::checkKeyword(retValue, "cpir")) {
			newNode->type = CPIR;
		} else if (Lex::checkKeyword(retValue, "cpl")) {
			newNode->type = CPL;
		} else if (Lex::checkKeyword(retValue, "daa")) {
			newNode->type = DAA;
		} else if (Lex::checkKeyword(retValue, "dec")) {
			newNode->type = DEC;
		} else if (Lex::checkKeyword(retValue, "di")) {
			newNode->type = DI;
		} else if (Lex::checkKeyword(retValue, "ei")) {
			newNode->type = EI;
		} else if (Lex::checkKeyword(retValue, "ex")) {
			newNode->type = EX;
		} else if (Lex::checkKeyword(retValue, "exx")) {
			newNode->type = EXX;
		} else if (Lex::checkKeyword(retValue, "halt") || Lex::checkKeyword(retValue, "hlt")) {
			newNode->type = HALT;
		} else if (Lex::checkKeyword(retValue, "im")) {
			newNode->type = IM;
		} else if (Lex::checkKeyword(retValue, "in")) {
			newNode->type = IN;
		} else if (Lex::checkKeyword(retValue, "inc")) {
			newNode->type = INC;
		} else if (Lex::checkKeyword(retValue, "ind")) {
			newNode->type = IND;
		} else if (Lex::checkKeyword(retValue, "indr")) {
			newNode->type = INDR;
		} else if (Lex::checkKeyword(retValue, "ini")) {
			newNode->type = INI;
		} else if (Lex::checkKeyword(retValue, "inir")) {
			newNode->type = INIR;
		} else if (Lex::checkKeyword(retValue, "jp") || Lex::checkKeyword(retValue, "jmp")) {
			newNode->type = JP;
		} else if (Lex::checkKeyword(retValue, "jr")) {
			newNode->type = JR;
		} else if (Lex::checkKeyword(retValue, "ld")) {
			newNode->type = LD;
		} else if (Lex::checkKeyword(retValue, "ldd")) {
			newNode->type = LDD;
		} else if (Lex::checkKeyword(retValue, "lddr")) {
			newNode->type = LDDR;
		} else if (Lex::checkKeyword(retValue, "ldi") || Lex::checkKeyword(retValue, "lddi")) {
			newNode->type = LDI;
		} else if (Lex::checkKeyword(retValue, "ldir")) {
			newNode->type = LDIR;
		} else if (Lex::checkKeyword(retValue, "neg")) {
			newNode->type = NEG;
		} else if (Lex::checkKeyword(retValue, "nop")) {
			newNode->type = NOP;
		} else if (Lex::checkKeyword(retValue, "or")) {
			newNode->type = OR;
		} else if (Lex::checkKeyword(retValue, "otdr")) {
			newNode->type = OTDR;
		} else if (Lex::checkKeyword(retValue, "otir")) {
			newNode->type = OTIR;
		} else if (Lex::checkKeyword(retValue, "out")) {
			newNode->type = OUT;
		} else if (Lex::checkKeyword(retValue, "outd")) {
			newNode->type = OUTD;
		} else if (Lex::checkKeyword(retValue, "outi")) {
			newNode->type = OUTI;
		} else if (Lex::checkKeyword(retValue, "pop")) {
			newNode->type = POP;
		} else if (Lex::checkKeyword(retValue, "push")) {
			newNode->type = PUSH;
		} else if (Lex::checkKeyword(retValue, "res")) {
			newNode->type = RES;
		} else if (Lex::checkKeyword(retValue, "ret")) {
			newNode->type = RET;
		} else if (Lex::checkKeyword(retValue, "reti")) {
			newNode->type = RETI;
		} else if (Lex::checkKeyword(retValue, "retn")) {
			newNode->type = RETN;
		} else if (Lex::checkKeyword(retValue, "rl")) {
			newNode->type = RL;
		} else if (Lex::checkKeyword(retValue, "rla")) {
			newNode->type = RLA;
		} else if (Lex::checkKeyword(retValue, "rlc")) {
			newNode->type = RLC;
		} else if (Lex::checkKeyword(retValue, "rlca")) {
			newNode->type = RLCA;
		} else if (Lex::checkKeyword(retValue, "rld")) {
			newNode->type = RLD;
		} else if (Lex::checkKeyword(retValue, "rr")) {
			newNode->type = RR;
		} else if (Lex::checkKeyword(retValue, "rra")) {
			newNode->type = RRA;
		} else if (Lex::checkKeyword(retValue, "rrc")) {
			newNode->type = RRC;
		} else if (Lex::checkKeyword(retValue, "rrca")) {
			newNode->type = RRCA;
		} else if (Lex::checkKeyword(retValue, "rrd")) {
			newNode->type = RRD;
		} else if (Lex::checkKeyword(retValue, "rst")) {
			newNode->type = RST;
		} else if (Lex::checkKeyword(retValue, "sbc") || Lex::checkKeyword(retValue, "subc")) {
			newNode->type = SUBC;
		} else if (Lex::checkKeyword(retValue, "scf")) {
			newNode->type = SCF;
		} else if (Lex::checkKeyword(retValue, "set")) {
			newNode->type = SET;
		} else if (Lex::checkKeyword(retValue, "sla")) {
			newNode->type = SLA;
		} else if (Lex::checkKeyword(retValue, "sra")) {
			newNode->type = SRA;
		} else if (Lex::checkKeyword(retValue, "srl")) {
			newNode->type = SRL;
		} else if (Lex::checkKeyword(retValue, "sub")) {
			newNode->type = SUB;
		} else if (Lex::checkKeyword(retValue, "xor")) {
			newNode->type = XOR;
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
		} else if (Lex::checkKeyword(retValue, "bc")) {
			newNode->type = BC;
		} else if (Lex::checkKeyword(retValue, "de")) {
			newNode->type = DE;
		} else if (Lex::checkKeyword(retValue, "hl")) {
			newNode->type = HL;
		} else if (!retValue.compare("I") || !retValue.compare("i")) {
			newNode->type = I;
		} else if (!retValue.compare("R") || !retValue.compare("r")) {
			newNode->type = R;
		} else if (Lex::checkKeyword(retValue, "ix")) {
			newNode->type = IX;
		} else if (Lex::checkKeyword(retValue, "iy")) {
			newNode->type = IY;
		} else if (Lex::checkKeyword(retValue, "pc")) {
			newNode->type = PC;
		} else if (Lex::checkKeyword(retValue, "sp")) {
			newNode->type = SP;
		} else if (Lex::checkKeyword(retValue, "af")) {
			newNode->type = AF;
		} else if (Lex::checkKeyword(retValue, "cpu")) {
			newNode->type = CPU;
		} else if (Lex::checkKeyword(retValue, "db") || Lex::checkKeyword(retValue, "byte")) {
			newNode->type = DB;
		} else if (Lex::checkKeyword(retValue, "dw") || Lex::checkKeyword(retValue, "word")) {
			newNode->type = DW;
		} else if (Lex::checkKeyword(retValue, "ddw") || Lex::checkKeyword(retValue, "dword")) {
			newNode->type = DDW;
		} else if (Lex::checkKeyword(retValue, "org")) {
			newNode->type = ORG;
		} else if (Lex::checkKeyword(retValue, "rep")) {
			newNode->type = REP;
		} else if (Lex::checkKeyword(retValue, "specrep")) {
			newNode->type = SPECREP;
		} else if (!retValue.compare("M") || !retValue.compare("m")) {
			newNode->type = M;
		} else if (Lex::checkKeyword(retValue, "nc")) {
			newNode->type = NC;
		} else if (Lex::checkKeyword(retValue, "nz")) {
			newNode->type = NZ;
		} else if (!retValue.compare("P") || !retValue.compare("p")) {
			newNode->type = P;
		} else if (Lex::checkKeyword(retValue, "pe")) {
			newNode->type = PE;
		} else if (Lex::checkKeyword(retValue, "po")) {
			newNode->type = PO;
		} else if (!retValue.compare("Z") || !retValue.compare("z")) {
			newNode->type = Z;
		} else if (Lex::checkKeyword(retValue, "equ")) {
			newNode->type = DIR_EQU;
		} else {

				//if it is not a reserved word, it is an ATOM:

			newNode->type = ATOM;
			newNode->value = retValue;
		}

	} else if (Lex::cList->peekValue() == '.') {
		retValue = Lex::cList->peekValue();
		Lex::cList->pop();

		while (!Lex::cList->isEmpty() && isAlphabetical(Lex::cList->peekValue())) {
			retValue += Lex::cList->peekValue();
			Lex::cList->pop();
		}

		if (!retValue.compare(".")) {
			newNode->type = DOT_POINT;
		} else {
			/*
				We have a directive command:
			*/
			if (!retValue.compare(".db") || !retValue.compare(".Db") || !retValue.compare(".DB") || !retValue.compare(".byte") || !retValue.compare(".Byte") || !retValue.compare(".BYTE")) {
				newNode->type = DB;
			} else if (!retValue.compare(".dw") || !retValue.compare(".Dw") || !retValue.compare(".DW") || !retValue.compare(".word") || !retValue.compare(".Word") || !retValue.compare(".WORD")) {
				newNode->type = DW;
			} else if (!retValue.compare(".equ") || !retValue.compare(".Equ") || !retValue.compare(".EQU")) {
				newNode->type = DIR_EQU;
			} else {
				newNode->type = ATOM;
				newNode->value = retValue;
			}
		}
	} else if (isNumerical(Lex::cList->peekValue()) || Lex::cList->peekValue() == '$' || Lex::cList->peekValue() == '#' || Lex::cList->peekValue() == '%') {
		newNode->type = NUMBER;
		newNode->value = Lex::getNumber();
	} else if (Lex::cList->peekValue() == '\"') {
		Lex::cList->pop();
		while (Lex::cList->peekValue() != '\"' && !Lex::errorState) {
			if (isPrintable(Lex::cList->peekValue())) {
				retValue += Lex::cList->peekValue();
			} else if (Lex::cList->isEmpty()) {
				/*
					In case we reach no more characters in the file,
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
	} else if (Lex::cList->peekValue() == '/') {
		newNode->type = DIVISION;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == '%') {
		newNode->type = REMAINDER;
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
		%1000000
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
		case '%':
			retValue += 'b';
			Lex::cList->pop();
			while (!Lex::cList->isEmpty() && isBinary(Lex::cList->peekValue())) {
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

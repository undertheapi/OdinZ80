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
	date updated: 18/02/2013
	author: Gareth Richardson
	description: This is the Lexical Analysis for the Odin assembler.
*/

#include <string>

using namespace std;

#include "../character/characterlist.hpp"
#include "tokentype.hpp"
#include "tokenlist.hpp"
#include "lex.hpp"

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

/*
	This method checks if the character value is a printable character. That is, it is not
	the first 32 ASCII values AND not the DEL character.
*/
bool isPrintable(CHARACTER value) {
	return value >= 32 && value <= 126;
}

/*
	This method checks if a CHARACTER value is a hexidecimal value:
*/
bool isHex(CHARACTER value) {
	return (value >= '0' && value <= '9') || (value >= 'a' && value <= 'f') || (value >= 'A' && value <= 'F');
}

bool isBinary(CHARACTER value) {
	return value == '0' || value == '1';
}

bool isDecimalString(string value) {
	bool valid = true;
	int index = 0;
	while (valid && index < value.size()) {
		if (!isNumerical(value.at(index))) {
			valid = false;
		}
		index++;
	}
	return valid;
}

bool isHexString(string value) {
	bool valid = true;
	int index = 0;
	while (valid && index < value.size()) {
		if (!isHex(value.at(index))) {
			valid = false;
		}
		index++;
	}
	return valid;
}

bool isBinaryString(string value) {
	bool valid = true;
	int index = 0;
	while (valid && index < value.size()) {
		if (!isBinary(value.at(index))) {
			valid = false;
		}
		index++;
	}
	return valid;
}

string integerToString(int value) {
	if (value == 0) {
		return "0";
	}

	string retValue = "";

	while (value > 0) {
		retValue += value % 10 + 48;
		value /= 10;
	}

	return retValue;
}

string convertHex(char value) {
	string retString = "";
	char hexArray[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	retString += hexArray[(int)((value >> 4) & 0x000f)];
	retString += hexArray[(int)((value) & 0x000f)];
	return retString;
}

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
		This is the string that collects the token value.
	*/
	string retValue = "";

	if (isAlphabetical(Lex::cList->peekValue())) {

		while (!Lex::cList->isEmpty() && (isAlphabetical(Lex::cList->peekValue()) || isNumerical(Lex::cList->peekValue()))) {
			retValue += Lex::cList->peekValue();
			Lex::cList->pop();
		}
		/*
			Here have some sort of token type checking to check for keywords. There has to be a more "effective" way
			of doing this.
			If the string does not match anything here, it will return a Token Type of ATOM.
		*/
		if (!retValue.compare("ADC") || !retValue.compare("Adc") || !retValue.compare("adc")) {
			newNode->type = ADC;
		} else if (!retValue.compare("ADD") || !retValue.compare("Add") || !retValue.compare("add")) {
			newNode->type = ADD;
		} else if (!retValue.compare("AND") || !retValue.compare("And") || !retValue.compare("and")) {
			newNode->type = AND;
		} else if (!retValue.compare("BIT") || !retValue.compare("Bit") || !retValue.compare("bit") || !retValue.compare("BT") || !retValue.compare("Bt") || !retValue.compare("bt")) {
			newNode->type = BIT;
		} else if (!retValue.compare("CALL") || !retValue.compare("Call") || !retValue.compare("call")) {
			newNode->type = CALL;
		} else if (!retValue.compare("CCF") || !retValue.compare("Ccf") || !retValue.compare("ccf")) {
			newNode->type = CCF;
		} else if (!retValue.compare("CP") || !retValue.compare("Cp") || !retValue.compare("cp")) {
			newNode->type = CP;
		} else if (!retValue.compare("CPD") || !retValue.compare("Cpd") || !retValue.compare("cpd")) {
			newNode->type = CPD;
		}  else if (!retValue.compare("CPDR") || !retValue.compare("Cpdr") || !retValue.compare("cpdr")) {
			newNode->type = CPDR;
		} else if (!retValue.compare("CPI") || !retValue.compare("Cpi") || !retValue.compare("cpi")) {
			newNode->type = CPI;
		} else if (!retValue.compare("CPIR") || !retValue.compare("Cpir") || !retValue.compare("cpir")) {
			newNode->type = CPIR;
		} else if (!retValue.compare("CPL") || !retValue.compare("Cpl") || !retValue.compare("cpl")) {
			newNode->type = CPL;
		} else if (!retValue.compare("DAA") || !retValue.compare("Daa") || !retValue.compare("daa")) {
			newNode->type = DAA;
		} else if (!retValue.compare("DEC") || !retValue.compare("Dec") || !retValue.compare("dec")) {
			newNode->type = DEC;
		} else if (!retValue.compare("DI") || !retValue.compare("Di") || !retValue.compare("di")) {
			newNode->type = DI;
		} else if (!retValue.compare("EI") || !retValue.compare("Ei") || !retValue.compare("ei")) {
			newNode->type = EI;
		} else if (!retValue.compare("EX") || !retValue.compare("Ex") || !retValue.compare("ex")) {
			newNode->type = EX;
		} else if (!retValue.compare("EXX") || !retValue.compare("Exx") || !retValue.compare("exx")) {
			newNode->type = EXX;
		} else if (!retValue.compare("HALT") || !retValue.compare("Halt") || !retValue.compare("halt") || !retValue.compare("HLT") || !retValue.compare("Hlt") || !retValue.compare("hlt")) {
			newNode->type = HALT;
		} else if (!retValue.compare("IM") || !retValue.compare("Im") || !retValue.compare("im")) {
			newNode->type = IM;
		} else if (!retValue.compare("IN") || !retValue.compare("In") || !retValue.compare("in")) {
			newNode->type = IN;
		} else if (!retValue.compare("INC") || !retValue.compare("Inc") || !retValue.compare("inc")) {
			newNode->type = INC;
		} else if (!retValue.compare("IND") || !retValue.compare("Ind") || !retValue.compare("ind")) {
			newNode->type = IND;
		} else if (!retValue.compare("INDR") || !retValue.compare("Indr") || !retValue.compare("indr")) {
			newNode->type = INDR;
		} else if (!retValue.compare("INI") || !retValue.compare("Ini") || !retValue.compare("ini")) {
			newNode->type = INI;
		} else if (!retValue.compare("INIR") || !retValue.compare("Inir") || !retValue.compare("inir")) {
			newNode->type = INIR;
		} else if (!retValue.compare("JP") || !retValue.compare("Jp") || !retValue.compare("jp") || !retValue.compare("JMP") || !retValue.compare("Jmp") || !retValue.compare("jmp")) {
			newNode->type = JP;
		} else if (!retValue.compare("JR") || !retValue.compare("Jr") || !retValue.compare("jr")) {
			newNode->type = JR;
		} else if (!retValue.compare("LD") || !retValue.compare("Ld") || !retValue.compare("ld")) {
			newNode->type = LD;
		} else if (!retValue.compare("LDD") || !retValue.compare("Ldd") || !retValue.compare("ldd")) {
			newNode->type = LDD;
		} else if (!retValue.compare("LDDR") || !retValue.compare("Lddr") || !retValue.compare("lddr")) {
			newNode->type = LDDR;
		} else if (!retValue.compare("LDI") || !retValue.compare("Ldi") || !retValue.compare("ldi")) {
			newNode->type = LDI;
		} else if (!retValue.compare("LDIR") || !retValue.compare("Ldir") || !retValue.compare("ldir")) {
			newNode->type = LDIR;
		} else if (!retValue.compare("NEG") || !retValue.compare("Neg") || !retValue.compare("neg")) {
			newNode->type = NEG;
		} else if (!retValue.compare("NOP") || !retValue.compare("Nop") || !retValue.compare("nop")) {
			newNode->type = NOP;
		} else if (!retValue.compare("OR") || !retValue.compare("or") || !retValue.compare("or")) {
			newNode->type = OR;
		} else if (!retValue.compare("OTDR") || !retValue.compare("OTDR") || !retValue.compare("otdr")) {
			newNode->type = OTDR;
		} else if (!retValue.compare("OTIR") || !retValue.compare("OTiR") || !retValue.compare("otir")) {
			newNode->type = OTIR;
		} else if (!retValue.compare("OUT") || !retValue.compare("Out") || !retValue.compare("out")) {
			newNode->type = OUT;
		} else if (!retValue.compare("OUTD") || !retValue.compare("Outd") || !retValue.compare("outd")) {
			newNode->type = OUTD;
		} else if (!retValue.compare("OUTI") || !retValue.compare("Outi") || !retValue.compare("outi")) {
			newNode->type = OUTI;
		} else if (!retValue.compare("POP") || !retValue.compare("Pop") || !retValue.compare("pop")) {
			newNode->type = POP;
		} else if (!retValue.compare("PUSH") || !retValue.compare("Push") || !retValue.compare("push")) {
			newNode->type = PUSH;
		} else if (!retValue.compare("RES") || !retValue.compare("Res") || !retValue.compare("res")) {
			newNode->type = RES;
		} else if (!retValue.compare("RET") || !retValue.compare("Ret") || !retValue.compare("ret")) {
			newNode->type = RET;
		} else if (!retValue.compare("RETI") || !retValue.compare("Reti") || !retValue.compare("reti")) {
			newNode->type = RETI;
		} else if (!retValue.compare("RETN") || !retValue.compare("Retn") || !retValue.compare("retn")) {
			newNode->type = RETN;
		} else if (!retValue.compare("RL") || !retValue.compare("rl") || !retValue.compare("rl")) {
			newNode->type = RL;
		} else if (!retValue.compare("RLA") || !retValue.compare("Rla") || !retValue.compare("rla")) {
			newNode->type = RLA;
		} else if (!retValue.compare("RLCA") || !retValue.compare("Rlca") || !retValue.compare("rlca")) {
			newNode->type = RLCA;
		} else if (!retValue.compare("RLD") || !retValue.compare("Rld") || !retValue.compare("rld")) {
			newNode->type = RLD;
		} else if (!retValue.compare("RR") || !retValue.compare("rr") || !retValue.compare("rr")) {
			newNode->type = RR;
		} else if (!retValue.compare("RRA") || !retValue.compare("Rra") || !retValue.compare("rra")) {
			newNode->type = RRA;
		} else if (!retValue.compare("RRC") || !retValue.compare("Rrc") || !retValue.compare("rrc")) {
			newNode->type = RRC;
		} else if (!retValue.compare("RRCA") || !retValue.compare("Rrca") || !retValue.compare("rrca")) {
			newNode->type = RRCA;
		} else if (!retValue.compare("RRD") || !retValue.compare("Rrd") || !retValue.compare("rrd")) {
			newNode->type = RRD;
		} else if (!retValue.compare("RST") || !retValue.compare("Rst") || !retValue.compare("rst")) {
			newNode->type = RST;
		} else if (!retValue.compare("SBC") || !retValue.compare("Sbc") || !retValue.compare("sbc") || !retValue.compare("SUBC") || !retValue.compare("Subc") || !retValue.compare("subc")) {
			newNode->type = SUBC;
		} else if (!retValue.compare("SCF") || !retValue.compare("Scf") || !retValue.compare("scf")) {
			newNode->type = SCF;
		} else if (!retValue.compare("SET") || !retValue.compare("Set") || !retValue.compare("set")) {
			newNode->type = SET;
		} else if (!retValue.compare("SLA") || !retValue.compare("Sla") || !retValue.compare("sla")) {
			newNode->type = SLA;
		} else if (!retValue.compare("SRA") || !retValue.compare("Sra") || !retValue.compare("sra")) {
			newNode->type = SRA;
		} else if (!retValue.compare("SRL") || !retValue.compare("Srl") || !retValue.compare("srl")) {
			newNode->type = SRL;
		} else if (!retValue.compare("SUB") || !retValue.compare("Sub") || !retValue.compare("sub")) {
			newNode->type = SUB;
		} else if (!retValue.compare("XOR") || !retValue.compare("Xor") || !retValue.compare("xor")) {
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
			newNode->type = SP;
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

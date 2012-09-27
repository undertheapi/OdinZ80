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
	date updated: 26/09/2012
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
	//cannot use this in release!!!!!!
	if (value == 0) {
		return "0";
	} else {
		string retValue = "";
		
		while (value > 0) {
			retValue += (value % 10) + 48;
			value /= 10;
		}
		
		return retValue;
	}
     /*   
    string temp="";
    string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
	*/
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
}

TokenNodePtr Lex::getToken() {
	TokenNodePtr newNode = new TokenNode;
	newNode->value = "";
	
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
		newNode->fileName = NULL;
		newNode->next = NULL;
		return newNode;
	}
	
	/*
		This is the string that collects the token value.
	*/
	string retValue = "";
	
	if (isAlphabetical(Lex::cList->peekValue())) {
		int line;
		char* file;
		
		while (!Lex::cList->isEmpty() && (isAlphabetical(Lex::cList->peekValue()) || isNumerical(Lex::cList->peekValue()))) {
			retValue += Lex::cList->peekValue();
			line = Lex::cList->peekLineNumber();
			file = Lex::cList->peekFileName();
			Lex::cList->pop();
		}
		/*
			Here have some sort of token type checking to check for keywords. There has to be a more "effective" way
			of doing this.
			If the string does not match anything here, it will return a Token Type of ATOM.
		*/
		if (retValue.compare("ADC") == 0 || retValue.compare("Adc") == 0 || retValue.compare("adc") == 0) {
			newNode->type = ADC;
		} else if (retValue.compare("ADD") == 0 || retValue.compare("Add") == 0 || retValue.compare("add") == 0) {
			newNode->type = ADD;
		} else if (retValue.compare("AND") == 0 || retValue.compare("And") == 0 || retValue.compare("and") == 0) {
			newNode->type = AND;
		} else if (retValue.compare("BIT") == 0 || retValue.compare("Bit") == 0 || retValue.compare("bit") == 0 || retValue.compare("BT") == 0 || retValue.compare("Bt") == 0 || retValue.compare("bt") == 0) {
			newNode->type = BIT;
		} else if (retValue.compare("CALL") == 0 || retValue.compare("Call") == 0 || retValue.compare("call") == 0) {
			newNode->type = CALL;
		} else if (retValue.compare("CCF") == 0 || retValue.compare("Ccf") == 0 || retValue.compare("ccf") == 0) {
			newNode->type = CCF;
		} else if (retValue.compare("CP") == 0 || retValue.compare("Cp") == 0 || retValue.compare("cp") == 0) {
			newNode->type = CP;
		} else if (retValue.compare("CPD") == 0 || retValue.compare("Cpd") == 0 || retValue.compare("cpd") == 0) {
			newNode->type = CPD;
		}  else if (retValue.compare("CPDR") == 0 || retValue.compare("Cpdr") == 0 || retValue.compare("cpdr") == 0) {
			newNode->type = CPDR;
		} else if (retValue.compare("CPI") == 0 || retValue.compare("Cpi") == 0 || retValue.compare("cpi") == 0) {
			newNode->type = CPI;
		} else if (retValue.compare("CPIR") == 0 || retValue.compare("Cpir") == 0 || retValue.compare("cpir") == 0) {
			newNode->type = CPIR;
		} else if (retValue.compare("CPL") == 0 || retValue.compare("Cpl") == 0 || retValue.compare("cpl") == 0) {
			newNode->type = CPL;
		} else if (retValue.compare("DAA") == 0 || retValue.compare("Daa") == 0 || retValue.compare("daa") == 0) {
			newNode->type = DAA;
		} else if (retValue.compare("DEC") == 0 || retValue.compare("Dec") == 0 || retValue.compare("dec") == 0) {
			newNode->type = DEC;
		} else if (retValue.compare("DI") == 0 || retValue.compare("Di") == 0 || retValue.compare("di") == 0) {
			newNode->type = DI;
		} else if (retValue.compare("EI") == 0 || retValue.compare("Ei") == 0 || retValue.compare("ei") == 0) {
			newNode->type = EI;
		} else if (retValue.compare("EX") == 0 || retValue.compare("Ex") == 0 || retValue.compare("ex") == 0) {
			newNode->type = EX;
		} else if (retValue.compare("EXX") == 0 || retValue.compare("Exx") == 0 || retValue.compare("exx") == 0) {
			newNode->type = EXX;
		} else if (retValue.compare("HALT") == 0 || retValue.compare("Halt") == 0 || retValue.compare("halt") == 0 || retValue.compare("HLT") == 0 || retValue.compare("Hlt") == 0 || retValue.compare("hlt") == 0) {
			newNode->type = HALT;
		} else if (retValue.compare("IM") == 0 || retValue.compare("Im") == 0 || retValue.compare("im") == 0) {
			newNode->type = IM;
		} else if (retValue.compare("IN") == 0 || retValue.compare("In") == 0 || retValue.compare("in") == 0) {
			newNode->type = IN;
		} else if (retValue.compare("INC") == 0 || retValue.compare("Inc") == 0 || retValue.compare("inc") == 0) {
			newNode->type = INC;
		} else if (retValue.compare("IND") == 0 || retValue.compare("Ind") == 0 || retValue.compare("ind") == 0) {
			newNode->type = IND;
		} else if (retValue.compare("INDR") == 0 || retValue.compare("Indr") == 0 || retValue.compare("indr") == 0) {
			newNode->type = INDR;
		} else if (retValue.compare("INI") == 0 || retValue.compare("Ini") == 0 || retValue.compare("ini") == 0) {
			newNode->type = INI;
		} else if (retValue.compare("INIR") == 0 || retValue.compare("Inir") == 0 || retValue.compare("inir") == 0) {
			newNode->type = INIR;
		} else if (retValue.compare("JP") == 0 || retValue.compare("Jp") == 0 || retValue.compare("jp") == 0 || retValue.compare("JMP") == 0 || retValue.compare("Jmp") == 0 || retValue.compare("jmp") == 0) {
			newNode->type = JP;
		} else if (retValue.compare("JR") == 0 || retValue.compare("Jr") == 0 || retValue.compare("jr") == 0) {
			newNode->type = JR;
		} else if (retValue.compare("LD") == 0 || retValue.compare("Ld") == 0 || retValue.compare("ld") == 0) {
			newNode->type = LD;
		} else if (retValue.compare("LDD") == 0 || retValue.compare("Ldd") == 0 || retValue.compare("ldd") == 0) {
			newNode->type = LDD;
		} else if (retValue.compare("LDDR") == 0 || retValue.compare("Lddr") == 0 || retValue.compare("lddr") == 0) {
			newNode->type = LDDR;
		} else if (retValue.compare("LDI") == 0 || retValue.compare("Ldi") == 0 || retValue.compare("ldi") == 0) {
			newNode->type = LDI;
		} else if (retValue.compare("LDIR") == 0 || retValue.compare("Ldir") == 0 || retValue.compare("ldir") == 0) {
			newNode->type = LDIR;
		} else if (retValue.compare("NEG") == 0 || retValue.compare("Neg") == 0 || retValue.compare("neg") == 0) {
			newNode->type = NEG;
		} else if (retValue.compare("NOP") == 0 || retValue.compare("Nop") == 0 || retValue.compare("nop") == 0) {
			newNode->type = NOP;
		} else if (retValue.compare("OR") == 0 || retValue.compare("or") == 0 || retValue.compare("or") == 0) {
			newNode->type = OR;
		} else if (retValue.compare("OTDR") == 0 || retValue.compare("OTDR") == 0 || retValue.compare("otdr") == 0) {
			newNode->type = OTDR;
		} else if (retValue.compare("OTIR") == 0 || retValue.compare("OTiR") == 0 || retValue.compare("otir") == 0) {
			newNode->type = OTIR;
		} else if (retValue.compare("OUT") == 0 || retValue.compare("Out") == 0 || retValue.compare("out") == 0) {
			newNode->type = OUT;
		} else if (retValue.compare("OUTD") == 0 || retValue.compare("Outd") == 0 || retValue.compare("outd") == 0) {
			newNode->type = OUTD;
		} else if (retValue.compare("OUTI") == 0 || retValue.compare("Outi") == 0 || retValue.compare("outi") == 0) {
			newNode->type = OUTI;
		} else if (retValue.compare("POP") == 0 || retValue.compare("Pop") == 0 || retValue.compare("pop") == 0) {
			newNode->type = POP;
		} else if (retValue.compare("PUSH") == 0 || retValue.compare("Push") == 0 || retValue.compare("push") == 0) {
			newNode->type = PUSH;
		} else if (retValue.compare("RES") == 0 || retValue.compare("Res") == 0 || retValue.compare("res") == 0) {
			newNode->type = RES;
		} else if (retValue.compare("RET") == 0 || retValue.compare("Ret") == 0 || retValue.compare("ret") == 0) {
			newNode->type = RET;
		} else if (retValue.compare("RETI") == 0 || retValue.compare("Reti") == 0 || retValue.compare("reti") == 0) {
			newNode->type = RETI;
		} else if (retValue.compare("RETN") == 0 || retValue.compare("Retn") == 0 || retValue.compare("retn") == 0) {
			newNode->type = RETN;
		} else if (retValue.compare("RL") == 0 || retValue.compare("rl") == 0 || retValue.compare("rl") == 0) {
			newNode->type = RL;
		} else if (retValue.compare("RLA") == 0 || retValue.compare("Rla") == 0 || retValue.compare("rla") == 0) {
			newNode->type = RLA;
		} else if (retValue.compare("RLCA") == 0 || retValue.compare("Rlca") == 0 || retValue.compare("rlca") == 0) {
			newNode->type = RLCA;
		} else if (retValue.compare("RLD") == 0 || retValue.compare("Rld") == 0 || retValue.compare("rld") == 0) {
			newNode->type = RLD;
		} else if (retValue.compare("RR") == 0 || retValue.compare("rr") == 0 || retValue.compare("rr") == 0) {
			newNode->type = RR;
		} else if (retValue.compare("RRA") == 0 || retValue.compare("Rra") == 0 || retValue.compare("rra") == 0) {
			newNode->type = RRA;
		} else if (retValue.compare("RRC") == 0 || retValue.compare("Rrc") == 0 || retValue.compare("rrc") == 0) {
			newNode->type = RRC;
		} else if (retValue.compare("RRCA") == 0 || retValue.compare("Rrca") == 0 || retValue.compare("rrca") == 0) {
			newNode->type = RRCA;
		} else if (retValue.compare("RRD") == 0 || retValue.compare("Rrd") == 0 || retValue.compare("rrd") == 0) {
			newNode->type = RRD;
		} else if (retValue.compare("RST") == 0 || retValue.compare("Rst") == 0 || retValue.compare("rst") == 0) {
			newNode->type = RST;
		} else if (retValue.compare("SBC") == 0 || retValue.compare("Sbc") == 0 || retValue.compare("sbc") == 0) {
			newNode->type = SBC;
		} else if (retValue.compare("SCF") == 0 || retValue.compare("Scf") == 0 || retValue.compare("scf") == 0) {
			newNode->type = SCF;
		} else if (retValue.compare("SET") == 0 || retValue.compare("Set") == 0 || retValue.compare("set") == 0) {
			newNode->type = SET;
		} else if (retValue.compare("SLA") == 0 || retValue.compare("Sla") == 0 || retValue.compare("sla") == 0) {
			newNode->type = SLA;
		} else if (retValue.compare("SRA") == 0 || retValue.compare("Sra") == 0 || retValue.compare("sra") == 0) {
			newNode->type = SRA;
		} else if (retValue.compare("SRL") == 0 || retValue.compare("Srl") == 0 || retValue.compare("srl") == 0) {
			newNode->type = SRL;
		} else if (retValue.compare("SUB") == 0 || retValue.compare("Sub") == 0 || retValue.compare("sub") == 0) {
			newNode->type = SUB;
		} else if (retValue.compare("XOR") == 0 || retValue.compare("Xor") == 0 || retValue.compare("xor") == 0) {
			newNode->type = XOR;
		} else if (retValue.compare("A") == 0 || retValue.compare("a") == 0) {
			newNode->type = A;
		} else if (retValue.compare("F") == 0 || retValue.compare("f") == 0) {
			newNode->type = F;
		} else if (retValue.compare("B") == 0 || retValue.compare("b") == 0) {
			newNode->type = B;
		} else if (retValue.compare("C") == 0 || retValue.compare("c") == 0) {
			newNode->type = C;
		} else if (retValue.compare("D") == 0 || retValue.compare("d") == 0) {
			newNode->type = D;
		} else if (retValue.compare("E") == 0 || retValue.compare("e") == 0) {
			newNode->type = E;
		} else if (retValue.compare("H") == 0 || retValue.compare("h") == 0) {
			newNode->type = H;
		} else if (retValue.compare("L") == 0 || retValue.compare("l") == 0) {
			newNode->type = L;
		} else if (retValue.compare("BC") == 0 || retValue.compare("bc") == 0) {
			newNode->type = BC;
		} else if (retValue.compare("DE") == 0 || retValue.compare("de") == 0) {
			newNode->type = DE;
		} else if (retValue.compare("HL") == 0 || retValue.compare("hl") == 0) {
			newNode->type = HL;
		} else if (retValue.compare("I") == 0 || retValue.compare("i") == 0) {
			newNode->type = I;
		} else if (retValue.compare("R") == 0 || retValue.compare("r") == 0) {
			newNode->type = R;
		} else if (retValue.compare("IX") == 0 || retValue.compare("ix") == 0) {
			newNode->type = IX;
		} else if (retValue.compare("IY") == 0 || retValue.compare("iy") == 0) {
			newNode->type = IY;
		} else if (retValue.compare("PC") == 0 || retValue.compare("pc") == 0) {
			newNode->type = PC;
		} else if (retValue.compare("SP") == 0 || retValue.compare("sp") == 0) {
			newNode->type = SP;
		} else if (retValue.compare("CPU") == 0 || retValue.compare("Cpu") == 0 || retValue.compare("cpu") == 0) {
			newNode->type = CPU;
		} else if (retValue.compare("DB") == 0 || retValue.compare("Db") == 0 || retValue.compare("db") == 0 || retValue.compare("BYTE") == 0 || retValue.compare("Byte") == 0 || retValue.compare("byte") == 0) {
			newNode->type = DB;
		} else if (retValue.compare("DW") == 0 || retValue.compare("Dw") == 0 || retValue.compare("dw") == 0 || retValue.compare("WORD") == 0 || retValue.compare("Word") == 0 || retValue.compare("word") == 0) {
			newNode->type = DW;
		} else if (retValue.compare("ORG") == 0 || retValue.compare("Org") == 0 || retValue.compare("org") == 0) {
			newNode->type = ORG;
		} else if (retValue.compare("REP") == 0 || retValue.compare("Rep") == 0 || retValue.compare("rep") == 0) {
			newNode->type = REP;
		} else if (retValue.compare("SPECREP") == 0 || retValue.compare("SPECREP") == 0 || retValue.compare("SPECREP") == 0) {
			newNode->type = SPECREP;
		} else if (retValue.compare("M") == 0 || retValue.compare("m") == 0) {
			newNode->type = M;
		} else if (retValue.compare("NC") == 0 || retValue.compare("nc") == 0) {
			newNode->type = NC;
		} else if (retValue.compare("NZ") == 0 || retValue.compare("nz") == 0) {
			newNode->type = NZ;
		} else if (retValue.compare("P") == 0 || retValue.compare("p") == 0) {
			newNode->type = P;
		} else if (retValue.compare("PE") == 0 || retValue.compare("pe") == 0) {
			newNode->type = PE;
		} else if (retValue.compare("PO") == 0 || retValue.compare("po") == 0) {
			newNode->type = PO;
		} else if (retValue.compare("Z") == 0 || retValue.compare("z") == 0) {
			newNode->type = Z;
		} else {
			/*
				if it is not a reserved word, it is an ATOM:
			*/
			newNode->type = ATOM;
			newNode->value = retValue;
		}
		// Adding the rest of the values for the TokenNode:
		newNode->lineNumber = line;
		newNode->fileName = file;
		newNode->next = NULL;
	} else if (Lex::cList->peekValue() == '0') {
		//So, we have a token starting with 0.
		Lex::cList->pop();
		if (!Lex::cList->isEmpty()) {
			string numberValue = "";
			if (Lex::cList->peekValue() == 'd') {
				Lex::cList->pop();
				//we have a decimal number:
				while (!Lex::cList->isEmpty() && isNumerical(Lex::cList->peekValue())) {
					numberValue += Lex::cList->peekValue();
					newNode->lineNumber = Lex::cList->peekLineNumber();
					newNode->fileName = Lex::cList->peekFileName();
					Lex::cList->pop();
				}
				
				if (numberValue.empty()) {
					Lex::errorState = true;
					Lex::errorString = "There is a 0d without any number after it. Every 0d must have a number following it.";
				} else {
					newNode->type = NUMBER;
					newNode->value = "d";
					newNode->value += numberValue;
					newNode->next = NULL;
				}
				
			} else if (Lex::cList->peekValue() == 'x' || Lex::cList->peekValue() == 'h') {
				Lex::cList->pop();
				//we have a hex number:
				while (!Lex::cList->isEmpty() && isHex(Lex::cList->peekValue())) {
					numberValue += Lex::cList->peekValue();
					newNode->lineNumber = Lex::cList->peekLineNumber();
					newNode->fileName = Lex::cList->peekFileName();
					Lex::cList->pop();
				}
				
				if (numberValue.empty()) {
					Lex::errorState = true;
					Lex::errorString = "There is a 0d or 0x without any number after it. Every 0d or 0x must have a number following it.";
				} else {
					newNode->type = NUMBER;
					newNode->value = "h";
					newNode->value += numberValue;
					newNode->next = NULL;
				}
				
			} else if (Lex::cList->peekValue() == 'b') {
				Lex::cList->pop();
				//we have a binary number:
				while (!Lex::cList->isEmpty() && isBinary(Lex::cList->peekValue())) {
					numberValue += Lex::cList->peekValue();
					newNode->lineNumber = Lex::cList->peekLineNumber();
					newNode->fileName = Lex::cList->peekFileName();
					Lex::cList->pop();
				}
				
				if (numberValue.empty()) {
					Lex::errorState = true;
					Lex::errorString = "There is a 0b without any number after it. Every 0b must have a number following it.";
				} else {
					newNode->type = NUMBER;
					newNode->value = "b";
					newNode->value += numberValue;
					newNode->next = NULL;
				}
				
			} else if (isNumerical(Lex::cList->peekValue())) {
				Lex::cList->pop();
				//we have a decimal number:
				numberValue += "0";
				while (!Lex::cList->isEmpty() && isNumerical(Lex::cList->peekValue())) {
					numberValue += Lex::cList->peekValue();
					newNode->lineNumber = Lex::cList->peekLineNumber();
					newNode->fileName = Lex::cList->peekFileName();
					Lex::cList->pop();
				}
				
				newNode->type = NUMBER;
				newNode->value = "d";
				newNode->value += numberValue;
				newNode->next = NULL;
			}
			// ********************* Need to add an else!
		} else {
			newNode->type = NUMBER;
			newNode->value = "d0";
			newNode->next = NULL;
		}
	} else if (isNumerical(Lex::cList->peekValue())) {
		//So if the character is NOT 0, it will be a decimal number:
		string numberValue = "";
		
		while (!Lex::cList->isEmpty() && isNumerical(Lex::cList->peekValue())) {
			numberValue += Lex::cList->peekValue();
			newNode->lineNumber = Lex::cList->peekLineNumber();
			newNode->fileName = Lex::cList->peekFileName();
			Lex::cList->pop();
		}
		
		newNode->type = NUMBER;
		newNode->value = "d";
		newNode->value += numberValue;
		newNode->next = NULL;
	} else if (Lex::cList->peekValue() == '$' || Lex::cList->peekValue() == '#') {
		//We have a hex value:
		Lex::cList->pop();
		
		string hexValue = "";
		while (!Lex::cList->isEmpty() && isHex(Lex::cList->peekValue())) {
			hexValue += Lex::cList->peekValue();
			newNode->lineNumber = Lex::cList->peekLineNumber();
			newNode->fileName = Lex::cList->peekFileName();
			Lex::cList->pop();
		}
		
		if (hexValue.size() == 0) {
			Lex::errorState = true;
			Lex::errorString = "There is a $ with no hexidecimal number after it. There should always be a number after a $.";
			Lex::errorString += hexValue;
		} else {
			newNode->type = NUMBER;
			newNode->value = "h";
			newNode->value += hexValue;
			newNode->next = NULL;
		}
		
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
				Lex::errorString += integerToString(Lex::cList->peekLineNumber());
			}
			Lex::cList->pop();
		}
		// This is here to pop the end quotation on the string.
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == ':') {
		newNode->type = COLON;
		newNode->lineNumber = Lex::cList->peekLineNumber();
		newNode->fileName = Lex::cList->peekFileName();
		newNode->next = NULL;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == ',') {
		newNode->type = COMMA;
		newNode->lineNumber = Lex::cList->peekLineNumber();
		newNode->fileName = Lex::cList->peekFileName();
		newNode->next = NULL;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == '\n') {
		newNode->type = NEW_LINE;
		newNode->lineNumber = Lex::cList->peekLineNumber();
		newNode->fileName = Lex::cList->peekFileName();
		newNode->next = NULL;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == '[' || Lex::cList->peekValue() == '(') {
		newNode->type = LEFT_BRACKET;
		newNode->lineNumber = Lex::cList->peekLineNumber();
		newNode->fileName = Lex::cList->peekFileName();
		newNode->next = NULL;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == ']' || Lex::cList->peekValue() == ')') {
		newNode->type = RIGHT_BRACKET;
		newNode->lineNumber = Lex::cList->peekLineNumber();
		newNode->fileName = Lex::cList->peekFileName();
		newNode->next = NULL;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == '+') {
		newNode->type = PLUS;
		newNode->lineNumber = Lex::cList->peekLineNumber();
		newNode->fileName = Lex::cList->peekFileName();
		newNode->next = NULL;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == '-') {
		newNode->type = MINUS;
		newNode->lineNumber = Lex::cList->peekLineNumber();
		newNode->fileName = Lex::cList->peekFileName();
		newNode->next = NULL;
		Lex::cList->pop();
	} else if (Lex::cList->peekValue() == '*') {
		newNode->type = MULTIPLY;
		newNode->lineNumber = Lex::cList->peekLineNumber();
		newNode->fileName = Lex::cList->peekFileName();
		newNode->next = NULL;
		Lex::cList->pop();
	} else {
		/*
			if the program gets to this point, there is an obvious error. The error is most
			likely an invalid character in the source code. For example: # @ etc.
		*/
		Lex::errorState = true;
		Lex::errorString = "An invalid character is in the source code at ";
		int lineNumber = Lex::cList->peekLineNumber();
		Lex::errorString += integerToString(lineNumber);
		Lex::errorString += " ";
		Lex::errorString += convertHex(Lex::cList->peekValue());
		Lex::cList->pop();
	}
	
	return newNode;
}

void Lex::run() {
	while (!Lex::errorState && !Lex::cList->isEmpty()) {
		TokenNodePtr newPtr = Lex::getToken();
		if (!Lex::errorState) {
			Lex::tList->push(newPtr);
		}
	}
}

bool Lex::checkForError() {
	return Lex::errorState;
}

string Lex::getError() {
	return Lex::errorString;
}

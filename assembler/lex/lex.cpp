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
	date updated: 19/09/2012
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
		} else if (retValue.compare("ADD") || retValue.compare("Add") || retValue.compare("add")) {
			newNode->type = ADD;
		} else if (retValue.compare("AND") || retValue.compare("And") || retValue.compare("and")) {
			newNode->type = AND;
		} else if (retValue.compare("BIT") || retValue.compare("Bit") || retValue.compare("bit") || retValue.compare("BT") || retValue.compare("Bt") || retValue.compare("bt")) {
			newNode->type = BIT;
		} else if (retValue.compare("CALL") || retValue.compare("Call") || retValue.compare("call")) {
			newNode->type = CALL;
		} else if (retValue.compare("CCF") || retValue.compare("Ccf") || retValue.compare("ccf")) {
			newNode->type = CCF;
		} else if (retValue.compare("CP") || retValue.compare("Cp") || retValue.compare("cp")) {
			newNode->type = CP;
		} else if (retValue.compare("CPD") || retValue.compare("Cpd") || retValue.compare("cpd")) {
			newNode->type = CPD;
		}  else if (retValue.compare("CPDR") || retValue.compare("Cpdr") || retValue.compare("cpdr")) {
			newNode->type = CPDR;
		} else if (retValue.compare("CPI") || retValue.compare("Cpi") || retValue.compare("cpi")) {
			newNode->type = CPI;
		} else if (retValue.compare("CPIR") || retValue.compare("Cpir") || retValue.compare("cpir")) {
			newNode->type = CPIR;
		} else if (retValue.compare("CPL") || retValue.compare("Cpl") || retValue.compare("cpl")) {
			newNode->type = CPL;
		} else if (retValue.compare("DAA") || retValue.compare("Daa") || retValue.compare("daa")) {
			newNode->type = DAA;
		} else if (retValue.compare("DEC") || retValue.compare("Dec") || retValue.compare("dec")) {
			newNode->type = DEC;
		} else if (retValue.compare("DI") || retValue.compare("Di") || retValue.compare("di")) {
			newNode->type = DI;
		} else if (retValue.compare("EI") || retValue.compare("Ei") || retValue.compare("ei")) {
			newNode->type = EI;
		} else if (retValue.compare("EX") || retValue.compare("Ex") || retValue.compare("ex")) {
			newNode->type = EX;
		} else if (retValue.compare("EXX") || retValue.compare("Exx") || retValue.compare("exx")) {
			newNode->type = EXX;
		} else if (retValue.compare("HALT") || retValue.compare("Halt") || retValue.compare("halt") || retValue.compare("HLT") || retValue.compare("Hlt") || retValue.compare("hlt")) {
			newNode->type = HALT;
		} else if (retValue.compare("IM") || retValue.compare("Im") || retValue.compare("im")) {
			newNode->type = IM;
		} else if (retValue.compare("IN") || retValue.compare("In") || retValue.compare("in")) {
			newNode->type = IN;
		} else if (retValue.compare("INC") || retValue.compare("Inc") || retValue.compare("inc")) {
			newNode->type = INC;
		} else if (retValue.compare("JP") || retValue.compare("Jp") || retValue.compare("jp") || retValue.compare("JMP") || retValue.compare("Jmp") || retValue.compare("jmp")) {
			newNode->type = JP;
		} else if (retValue.compare("LD") || retValue.compare("Ld") || retValue.compare("ld")) {
			newNode->type = LD;
		} else if (retValue.compare("NEG") || retValue.compare("Neg") || retValue.compare("neg")) {
			newNode->type = NEG;
		} else if (retValue.compare("NOP") || retValue.compare("Nop") || retValue.compare("nop")) {
			newNode->type = NOP;
		} else if (retValue.compare("OUT") || retValue.compare("Out") || retValue.compare("out")) {
			newNode->type = OUT;
		} else if (retValue.compare("POP") || retValue.compare("Pop") || retValue.compare("pop")) {
			newNode->type = POP;
		} else if (retValue.compare("PUSH") || retValue.compare("Push") || retValue.compare("push")) {
			newNode->type = PUSH;
		} else if (retValue.compare("RES") || retValue.compare("Res") || retValue.compare("res")) {
			newNode->type = RES;
		} else if (retValue.compare("RET") || retValue.compare("Ret") || retValue.compare("ret")) {
			newNode->type = RET;
		} else if (retValue.compare("RETI") || retValue.compare("Reti") || retValue.compare("reti")) {
			newNode->type = RETI;
		} else if (retValue.compare("RETN") || retValue.compare("Retn") || retValue.compare("retn")) {
			newNode->type = RETN;
		} else if (retValue.compare("RLA") || retValue.compare("Rla") || retValue.compare("rla")) {
			newNode->type = RLA;
		} else if (retValue.compare("RLCA") || retValue.compare("Rlca") || retValue.compare("rlca")) {
			newNode->type = RLCA;
		} else if (retValue.compare("RLD") || retValue.compare("Rld") || retValue.compare("rld")) {
			newNode->type = RLD;
		} else if (retValue.compare("RRA") || retValue.compare("Rra") || retValue.compare("rra")) {
			newNode->type = RRA;
		} else if (retValue.compare("RRCA") || retValue.compare("Rrca") || retValue.compare("rrca")) {
			newNode->type = RRCA;
		} else if (retValue.compare("RRD") || retValue.compare("Rrd") || retValue.compare("rrd")) {
			newNode->type = RRD;
		} else if (retValue.compare("RST") || retValue.compare("Rst") || retValue.compare("rst")) {
			newNode->type = RST;
		} else if (retValue.compare("SBC") || retValue.compare("Sbc") || retValue.compare("sbc")) {
			newNode->type = SBC;
		} else if (retValue.compare("SCF") || retValue.compare("Scf") || retValue.compare("scf")) {
			newNode->type = SCF;
		} else if (retValue.compare("SET") || retValue.compare("Set") || retValue.compare("set")) {
			newNode->type = SET;
		} 
		//Adding the rest of the values for the TokenNode:
		newNode->lineNumber = line;
		newNode->fileName = file;
		newNode->next = NULL;
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

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
	file name: SRAinstr.cpp
	date created: 20/02/2013
	date updated: 20/02/2013
	author: Gareth Richardson
	description: The object file for the processSRA() method.
*/

#include <string>

using namespace std;

#include "../../lex/tokenlist.hpp"
#include "../bytecode.hpp"
#include "../foundlist.hpp"
#include "../addresslist.hpp"
#include "../parser.hpp"

void Z80Parser::processSRA() {
	unsigned char num8;
	if (Z80Parser::checkToken(A)) {
		Z80Parser::addCode(0xcb, 0x2f);
	} else if (Z80Parser::checkToken(B)) {
		Z80Parser::addCode(0xcb, 0x28);
	} else if (Z80Parser::checkToken(C)) {
		Z80Parser::addCode(0xcb, 0x29);
	} else if (Z80Parser::checkToken(D)) {
		Z80Parser::addCode(0xcb, 0x2a);
	} else if (Z80Parser::checkToken(E)) {
		Z80Parser::addCode(0xcb, 0x2b);
	} else if (Z80Parser::checkToken(H)) {
		Z80Parser::addCode(0xcb, 0x2c);
	} else if (Z80Parser::checkToken(L)) {
		Z80Parser::addCode(0xcb, 0x2d);
	} else if (Z80Parser::checkToken(LEFT_BRACKET)) {
		if (Z80Parser::checkToken(HL)) {
			Z80Parser::addCode(0xcb, 0x2e);
		} else if (Z80Parser::checkToken(IX) && Z80Parser::checkToken(PLUS) && Z80Parser::checkEightBitNumber(num8)) {
			Z80Parser::addCode(0xdd, 0xcb);
			Z80Parser::addCode(num8, 0x2e);
		} else if (Z80Parser::checkToken(IY) && Z80Parser::checkToken(PLUS) && Z80Parser::checkEightBitNumber(num8)) {
			Z80Parser::addCode(0xfd, 0xcb);
			Z80Parser::addCode(num8, 0x2e);
		} else {
			Z80Parser::error("The address is pointer to by either [HL], [IX + 8 bit offset] or [IY + 8 bit offset] only.");
		}
		
		if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
			Z80Parser::error("Missing bracket.");
		}
	} else {
		Z80Parser::error("The SLA instruction parameter is an 8-bit register or a pointer to an 8-bit number.");
	}
	
	if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
		Z80Parser::error("The SLA instruction has to end in a new line.");
	}
}


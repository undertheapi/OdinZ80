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
	file name: EXinstr.hpp
	date created: 17/02/2013
	date updated: 21/02/2013
	author: Gareth Richardson
	description: The processor for EX instructions.
*/

#include <string>

using namespace std;

#include "../../lex/tokenlist.hpp"
#include "../bytecode.hpp"
#include "../foundlist.hpp"
#include "../addresslist.hpp"
#include "../parser.hpp"

void Z80Parser::processEX() {
	if (Z80Parser::checkToken(DE)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(HL)) {
				Z80Parser::addCode(0xeb);
			} else {
				Z80Parser::error("The second parameter can only be HL.");
			}
		} else {
			Z80Parser::error("Missing comma.");
		}
	} else if (Z80Parser::checkToken(AF)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(AF)) {
				Z80Parser::addCode(0x08);
			} else {
				Z80Parser::error("The second parameter can only be AF.");
			}
		} else {
			Z80Parser::error("Missing comma.");
		}
	} else if (		Z80Parser::checkToken(LEFT_BRACKET) /* Doing this just because I can :P */
				&&	Z80Parser::checkToken(SP)
				&&	Z80Parser::checkToken(RIGHT_BRACKET)
				&&	Z80Parser::checkToken(COMMA)
			  ) {
		if (Z80Parser::checkToken(HL)) {
			Z80Parser::addCode(0xe3);
		} else if (Z80Parser::checkToken(IX)) {
			Z80Parser::addCode(0xdd, 0xe3);
		} else if (Z80Parser::checkToken(IY)) {
			Z80Parser::addCode(0xfd, 0xe3);
		} else {
			Z80Parser::error("The second parameter can only be HL, IX or IY.");
		}
	} else {
		Z80Parser::error("EX instruction can only process 16-bit registers.");
	}
	
	if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
		Z80Parser::error("EX instruction must end in a new line.");
	}
}


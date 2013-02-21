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
	file name: INinstr.cpp
	compiled name: INinstr.o
	date created: 21/02/2013
	date updated: 21/02/2013
	author: Gareth Richardson
	description: This is the object file for the processIN() method.
*/

#include <string>

using namespace std;

#include "../../lex/tokenlist.hpp"
#include "../bytecode.hpp"
#include "../foundlist.hpp"
#include "../addresslist.hpp"
#include "../parser.hpp"

void Z80Parser::processIN() {
	unsigned char num8;
	if (Z80Parser::checkToken(A)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(LEFT_BRACKET)) {
				if (Z80Parser::checkEightBitNumber(num8)) {
					Z80Parser::addCode(0xdb, num8);
				} else if (Z80Parser::checkToken(C)) {
					Z80Parser::addCode(0xeb, 0x78);
				} else {
					Z80Parser::error("Instruction can be either IN A, [num8] or IN A, [C].");
				}
				
				if (Z80Parser::checkToken(RIGHT_BRACKET) && !Z80Parser::errorState) {
					Z80Parser::error("Missing Bracket.");
				}
			} else {
				Z80Parser::error("Instruction can be either IN A, [num8] or IN A, [C].");
			}
		} else {
			Z80Parser::error("Missing Comma.");
		}
	} else if (Z80Parser::checkToken(B)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(LEFT_BRACKET) 
			&& Z80Parser::checkToken(C) 
			&& Z80Parser::checkToken(RIGHT_BRACKET)) {
				Z80Parser::addCode(0xeb, 0x40);
			} else {
				Z80Parser::error("Instruction can be either IN B, [C].");
			}
		} else {
			Z80Parser::error("Missing Comma.");
		}
	} else if (Z80Parser::checkToken(C)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(LEFT_BRACKET) 
			&& Z80Parser::checkToken(C) 
			&& Z80Parser::checkToken(RIGHT_BRACKET)) {
				Z80Parser::addCode(0xeb, 0x48);
			} else {
				Z80Parser::error("Instruction can be either IN C, [C].");
			}
		} else {
			Z80Parser::error("Missing Comma.");
		}
	} else if (Z80Parser::checkToken(D)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(LEFT_BRACKET) 
			&& Z80Parser::checkToken(C) 
			&& Z80Parser::checkToken(RIGHT_BRACKET)) {
				Z80Parser::addCode(0xeb, 0x50);
			} else {
				Z80Parser::error("Instruction can be either IN D, [C].");
			}
		} else {
			Z80Parser::error("Missing Comma.");
		}
	} else if (Z80Parser::checkToken(E)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(LEFT_BRACKET) 
			&& Z80Parser::checkToken(C) 
			&& Z80Parser::checkToken(RIGHT_BRACKET)) {
				Z80Parser::addCode(0xeb, 0x58);
			} else {
				Z80Parser::error("Instruction can be either IN E, [C].");
			}
		} else {
			Z80Parser::error("Missing Comma.");
		}
	} else if (Z80Parser::checkToken(H)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(LEFT_BRACKET) 
			&& Z80Parser::checkToken(C) 
			&& Z80Parser::checkToken(RIGHT_BRACKET)) {
				Z80Parser::addCode(0xeb, 0x60);
			} else {
				Z80Parser::error("Instruction can be either IN H, [C].");
			}
		} else {
			Z80Parser::error("Missing Comma.");
		}
	} else if (Z80Parser::checkToken(L)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(LEFT_BRACKET) 
			&& Z80Parser::checkToken(C) 
			&& Z80Parser::checkToken(RIGHT_BRACKET)) {
				Z80Parser::addCode(0xeb, 0x68);
			} else {
				Z80Parser::error("Instruction can be either IN L, [C].");
			}
		} else {
			Z80Parser::error("Missing Comma.");
		}
	} else {
		Z80Parser::error("Incorrect useage of the IN instruction.");
	}
	
	Z80Parser::newLine();
}

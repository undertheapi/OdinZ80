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
	file name: JPinstr.cpp
	compiled name: JPinstr.o
	date created: 20/02/2013
	date updated: 20/02/2013
	author: Gareth Richardson
	description: This is the object file for the processJP() method.
*/

#include <string>

using namespace std;

#include "../../lex/tokenlist.hpp"
#include "../bytecode.hpp"
#include "../foundlist.hpp"
#include "../addresslist.hpp"
#include "../parser.hpp"

void Z80Parser::processJP() {
	unsigned short num16;
	string atom;
	if (Z80Parser::checkSixteenBitNumber(num16)) {
		Z80Parser::addCode(0xc3, (unsigned short) num16, (unsigned short) (num16 >> 8));
	} else if (Z80Parser::checkAtom(atom)) {
		Z80Parser::addCode(0xc3);
		Z80Parser::addAddress(atom);
	} else if (Z80Parser::checkToken(NZ)) {
		Z80Parser::addCode(0xc2);
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkSixteenBitNumber(num16)) {
				Z80Parser::addCode((unsigned short) num16, (unsigned short) (num16 >> 8));
			} else if (Z80Parser::checkAtom(atom)) {
				Z80Parser::addAddress(atom);
			} else {
				Z80Parser::error("Invalid use of the JP instruction.");
			}
		} else {
			Z80Parser::error("Missing comma.");
		}
	} else if (Z80Parser::checkToken(Z)) {
		Z80Parser::addCode(0xca);
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkSixteenBitNumber(num16)) {
				Z80Parser::addCode((unsigned short) num16, (unsigned short) (num16 >> 8));
			} else if (Z80Parser::checkAtom(atom)) {
				Z80Parser::addAddress(atom);
			} else {
				Z80Parser::error("Invalid use of the JP instruction.");
			}
		} else {
			Z80Parser::error("Missing comma.");
		}
	} else if (Z80Parser::checkToken(NC)) {
		Z80Parser::addCode(0xd2);
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkSixteenBitNumber(num16)) {
				Z80Parser::addCode((unsigned short) num16, (unsigned short) (num16 >> 8));
			} else if (Z80Parser::checkAtom(atom)) {
				Z80Parser::addAddress(atom);
			} else {
				Z80Parser::error("Invalid use of the JP instruction.");
			}
		} else {
			Z80Parser::error("Missing comma.");
		}
	} else if (Z80Parser::checkToken(C)) {
		Z80Parser::addCode(0xda);
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkSixteenBitNumber(num16)) {
				Z80Parser::addCode((unsigned short) num16, (unsigned short) (num16 >> 8));
			} else if (Z80Parser::checkAtom(atom)) {
				Z80Parser::addAddress(atom);
			} else {
				Z80Parser::error("Invalid use of the JP instruction.");
			}
		} else {
			Z80Parser::error("Missing comma.");
		}
	} else if (Z80Parser::checkToken(PO)) {
		Z80Parser::addCode(0xe2);
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkSixteenBitNumber(num16)) {
				Z80Parser::addCode((unsigned short) num16, (unsigned short) (num16 >> 8));
			} else if (Z80Parser::checkAtom(atom)) {
				Z80Parser::addAddress(atom);
			} else {
				Z80Parser::error("Invalid use of the JP instruction.");
			}
		} else {
			Z80Parser::error("Missing comma.");
		}
	} else if (Z80Parser::checkToken(PE)) {
		Z80Parser::addCode(0xea);
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkSixteenBitNumber(num16)) {
				Z80Parser::addCode((unsigned short) num16, (unsigned short) (num16 >> 8));
			} else if (Z80Parser::checkAtom(atom)) {
				Z80Parser::addAddress(atom);
			} else {
				Z80Parser::error("Invalid use of the JP instruction.");
			}
		} else {
			Z80Parser::error("Missing comma.");
		}
	} else if (Z80Parser::checkToken(P)) {
		Z80Parser::addCode(0xf2);
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkSixteenBitNumber(num16)) {
				Z80Parser::addCode((unsigned short) num16, (unsigned short) (num16 >> 8));
			} else if (Z80Parser::checkAtom(atom)) {
				Z80Parser::addAddress(atom);
			} else {
				Z80Parser::error("Invalid use of the JP instruction.");
			}
		} else {
			Z80Parser::error("Missing comma.");
		}
	} else if (Z80Parser::checkToken(M)) {
		Z80Parser::addCode(0xfa);
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkSixteenBitNumber(num16)) {
				Z80Parser::addCode((unsigned short) num16, (unsigned short) (num16 >> 8));
			} else if (Z80Parser::checkAtom(atom)) {
				Z80Parser::addAddress(atom);
			} else {
				Z80Parser::error("Invalid use of the JP instruction.");
			}
		} else {
			Z80Parser::error("Missing comma.");
		}
	} else {
		Z80Parser::error("Invalid use of the JP instruction.");
	}
	
	if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
		Z80Parser::error("The JP instruction requires a new line at the end.");
	}
}


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
	file name: RSTinstr.cpp
	compiled name: RSTinstr.o
	date created: 21/02/2013
	date updated: 21/02/2013
	author: Gareth Richardson
	description: This is the object file for the processRST() method.
*/

#include <string>

using namespace std;

#include "../../lex/tokenlist.hpp"
#include "../bytecode.hpp"
#include "../foundlist.hpp"
#include "../addresslist.hpp"
#include "../parser.hpp"

void Z80Parser::processRST() {
	unsigned char num8;
	if (Z80Parser::checkEightBitNumber(num8)) {
		if (num8 == 0x00) {
			Z80Parser::addCode(0xc7);
		} else if (num == 0x08) {
			Z80Parser::addCode(0xcf);
		} else if (num == 0x10) {
			Z80Parser::addCode(0xd7);
		} else if (num == 0x18) {
			Z80Parser::addCode(0xdf)
		} else if (num == 0x20) {
			Z80Parser::addCode(0xe7);
		} else if (num == 0x28) {
			Z80Parser::addCode(0xef)
		} else if (num == 0x30) {
			Z80Parser::addCode(0xf7);
		} else if (num == 0x38) {
			Z80Parser::addCode(0xff)
		} else {
			Z80Parser::error("Wrong number value in the RST instruction.");
		}
		Z80Parser::newLine();
	} else {
		Z80Parser::error("The parameter for the RST instruction must be an 8-bit value only.");
	}
}

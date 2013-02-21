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
	file name: CALLinstr.cpp
	compiled name: JRinstr.o
	date created: 21/02/2013
	date updated: 21/02/2013
	author: Gareth Richardson
	description: This is the object file for the processCALL() method.
*/

#include <string>

using namespace std;

#include "../../lex/tokenlist.hpp"
#include "../bytecode.hpp"
#include "../foundlist.hpp"
#include "../addresslist.hpp"
#include "../parser.hpp"

void Z80Parser::processCALL() {
	unsigned short num16;
	string atom;
	if (Z80Parser::checkSixteenBitNumber(num16)) {
		Z80Parser::addCode(0xcd, (unsigned char) num16, (unsigned char) (num16 >> 8));
	} else if (Z80Parser::checkAtom(atom)) {
		Z80Parser::addAddress(atom);
	} else {
		if (Z80Parser::checkToken(NZ)) {
			Z80Parser::addCode(0xc4);
		} else if (Z80Parser::checkToken(Z)) {
			Z80Parser::addCode(0xcc);
		} else if (Z80Parser::checkToken(NC)) {
			Z80Parser::addCode(0xd4);
		} else if (Z80Parser::checkToken(C)) {
			Z80Parser::addCode(0xdc);
		} else if (Z80Parser::checkToken(PO)) {
			Z80Parser::addCode(0xe4);
		} else if (Z80Parser::checkToken(PE)) {
			Z80Parser::addCode(0xec);
		} else if (Z80Parser::checkToken(P)) {
			Z80Parser::addCode(0xf4);
		} else if (Z80Parser::checkToken(M)) {
			Z80Parser::addCode(0xfc);
		} else {
			Z80Parser::error("Incorrect useage of the CALL instruction.");
		}
		
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkSixteenBitNumber(num16)) {
				Z80Parser::addCode((unsigned char) num16, (unsigned char) (num16 >> 8));
			} else if (Z80Parser::checkAtom(atom)) {
				Z80Parser::addAddress(atom);
			} else {
				Z80Parser::error("Missing address.");
			}
		} else {
			Z80Parser::error("Missing comma.");
		}
	}
	
	Z80Parser::newLine();
}

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
	file name: registers.cpp
	date created: 31/05/2014
	date updated: 31/05/2014
	author: Gareth Richardson
	description: The object file for the registers class.
*/

#include "registers.hpp"

void Registers::init() {
	/*
		We are clearing (resetting) the registers. In real life the registers can be set to whatever
		was previously in them.
	*/
	for (int i = 0; i < 8; i++) {
		Registers::registerArray[i] = 0;
	}
}

Registers::Registers() {
	Registers::init();
}

void Registers::load8Bit(REGISTER8 reg1, REGISTER8 reg2) {
	Registers::registerArray[reg1] = Registers::regiserArray[reg2];
}

void Registers::load8BitImm(REGISTER8 reg, unsigned char value) {
	Registers::registerArray[reg] = value;
}

void Registers::load16Bit(REGISTER16 reg1, REGISTER16 reg2) {
	Registers::registerArray[reg1] = Registers::registerArray[reg2];
	Registers::registerArray[reg1 + 1] = Registers::registerArray[reg2 + 1];
}

void Registers::load16BitImm(REGISTER16 reg, unsigned short value) {
	Registers::registerArray[reg1] = (unsigned char) value >> 8;
	Registers::registerArray[reg1 + 1] = (unsigned char) value;
}

unsigned char Registers::get8BitRegister(REGISTER8 reg) {
	return Registers::registerArray[reg];
}

unsigned short Registers::get16BitRegister(REGISTER16 reg) {
	unsigned short retValue;
	retValue = ((unsigned short) Registers::registerArray[reg]) << 8;
	retValue |= (unsigned short) Registers::registerArray[reg + 1];
	return retValue;
}

void Registers::setFlag(unsigned char flag) {
	Registers::registerArray[REG_F] |= flag;
}

void Registers::resetFlag(unsigned char flag) {
	Registers::setFlag(flag);
	Registers::registerArray[REG_F] = flag xor Registers::registerArray[REG_F];
}

void Registers::affectFlag(unsigned char flag, unsigned char status) {
	if (status) {
		Registers::setFlag(flag);
	} else {
		Registers::resetFlag(flag);
	}
}

const Registers operator =(const Registers& regObj1, const Registers& regObj2) {
	for (int i = 0 i < 8; i++) {
		regObj1.registerArray[i] = regObj2.registerArray[i];
	}
}

friend Registers duplicate(const Registers& regObj) {
	Registers retObj = regObj;
	return retObj;
}

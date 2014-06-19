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
	file name: z80cpu.cpp
	date created: 01/06/2014
	date updated: 19/06/2014
	author: Gareth Richardson
	description: This is the header file for the model CPU in the debugger.
*/

#include <string>

using namespace std;

#include "../general/convert.hpp"
#include "../ram/ram.hpp"
#include "../registers/registers.hpp"
#include "../registers/specialregisters.hpp"

#include "z80cpu.hpp"

string registerArray[8] = {
	"B", "C", "D", "E", "H", "L", "[HL]", "A"
};

void Z80CPU::init() {
	Z80CPU::resetButton = false;
	Z80CPU::instructionString = "";
}

unsigned char Z80CPU::retrieveFromAddress() {
	return Z80CPU::mainRAM.read(Z80CPU::specialPurposeRegisters.getProgramCounter());
}

Z80CPU::Z80CPU() {
	Z80CPU::init();
}

void Z80CPU::loadUpRAM(unsigned short index, unsigned char value) {
	Z80CPU::mainRAM.write(index, value);
}

void Z80CPU::run(unsigned short steps) {
	int counter = steps;
	while (counter != 0) {
		Z80CPU::step();
		--counter;
	}
}
#include <cstdio>
void Z80CPU::step() {
	if (Z80CPU::retrieveFromAddress() == 0x00) {
		/*
			NOP instruction:
			Does absolutely nothing except increment the PC.
		*/
		Z80CPU::instructionString = "NOP";
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
	} else if (Z80CPU::retrieveFromAddress() == 0x76) {
		/*
			HALT INSTRUCTION
		*/
		Z80CPU::instructionString = "HALT";
		if (Z80CPU::resetButton) {
			Z80CPU::specialPurposeRegisters.incrementProgramCounter();
			Z80CPU::toggleReset();
		}
	} else if (Z80CPU::retrieveFromAddress() == 0xdd) {
		/*
			We have an Extended IX register instruction:
		*/
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		if (Z80CPU::retrieveFromAddress() != 0x76) {
			Z80CPU::instructionString = "LD ";
			Z80CPU::instructionString += registerArray[Z80CPU::retrieveFromAddress() >> 3 & 0x07];
			Z80CPU::instructionString += ", [IX + ";
			Z80CPU::instructionString += convertHex(Z80CPU::retrieveFromAddress());
			Z80CPU::mainRegisterSet.load8BitImm(
				Z80CPU::retrieveFromAddress() >> 3 & 0x07,
				Z80CPU::specialPurposeRegisters.getIX() + Z80CPU::retrieveFromAddress() + 1
			);
			Z80CPU::specialPurposeRegisters.incrementProgramCounter();
			Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		}
	} else if (Z80CPU::retrieveFromAddress() == 0xfd) {
		/*
			We have an Extended IY register instruction:
		*/
	} else if (Z80CPU::retrieveFromAddress() >= 0x06 && Z80CPU::retrieveFromAddress() <= 0x3e) {
		//LD r, IMM
		Z80CPU::instructionString = "LD ";
		Z80CPU::instructionString += registerArray[Z80CPU::retrieveFromAddress() >> 3 & 0x07];
		REGISTER8 reg = Z80CPU::mainRAM.read(Z80CPU::specialPurposeRegisters.getProgramCounter()) >> 3 & 0x07;
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		Z80CPU::instructionString += ", ";
		Z80CPU::instructionString += convertHex(Z80CPU::retrieveFromAddress());
		Z80CPU::instructionString += "H";
		Z80CPU::mainRegisterSet.load8BitImm(reg, Z80CPU::mainRAM.read(Z80CPU::specialPurposeRegisters.getProgramCounter()));
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
	} else if (Z80CPU::retrieveFromAddress() >= 0x40 && Z80CPU::retrieveFromAddress() <= 0x7f) {
		Z80CPU::instructionString = "LD ";
		Z80CPU::instructionString += registerArray[Z80CPU::retrieveFromAddress() >> 3 & 0x07];
		Z80CPU::instructionString += ", ";
		Z80CPU::instructionString += registerArray[Z80CPU::retrieveFromAddress() & 0x07];
		printf("%x\n", Z80CPU::retrieveFromAddress() >> 3 & 0x07);
		if (Z80CPU::retrieveFromAddress() & 0x07 == 0x06) {
			// LD r, [hl]
			Z80CPU::mainRegisterSet.load8Bit(
				Z80CPU::retrieveFromAddress() >> 3 & 0x07,
				Z80CPU::mainRAM.read(
					Z80CPU::mainRegisterSet.get16BitRegister(REG_HL)
				)
			);
		} else if (Z80CPU::retrieveFromAddress() & 0x38 == 0x30) {
			// LD [hl], r
			Z80CPU::mainRAM.write(
				Z80CPU::mainRegisterSet.get16BitRegister(REG_HL),
				Z80CPU::mainRegisterSet.get8BitRegister(Z80CPU::retrieveFromAddress() & 0x07)
			);
		} else {
			// LD r, r'
			Z80CPU::mainRegisterSet.load8Bit(
				Z80CPU::retrieveFromAddress() >> 3 & 0x07,
				Z80CPU::retrieveFromAddress() & 0x07
			);
		}
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
	} else {
		Z80CPU::instructionString = "NO INSTRUCTION";
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
	}
}

void Z80CPU::toggleReset() {
	Z80CPU::resetButton = !Z80CPU::resetButton;
}

string Z80CPU::prettyPrint() {
	string retString = "A:";
	retString += convertHex(Z80CPU::mainRegisterSet.get8BitRegister(REG_A));
	retString += " BC:";
	retString += convertHex(Z80CPU::mainRegisterSet.get16BitRegister(REG_BC));
	retString += " DE:";
	retString += convertHex(Z80CPU::mainRegisterSet.get16BitRegister(REG_DE));
	retString += " HL:";
	retString += convertHex(Z80CPU::mainRegisterSet.get16BitRegister(REG_HL));
	retString += "\n";
	retString += "PC: ";
	retString += convertHex(Z80CPU::specialPurposeRegisters.getProgramCounter());
	return retString;
}

string Z80CPU::getCurrentInstruction() {
	return Z80CPU::instructionString;
}

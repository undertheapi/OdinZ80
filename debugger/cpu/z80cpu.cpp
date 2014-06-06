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
	date updated: 06/06/2014
	author: Gareth Richardson
	description: This is the header file for the model CPU in the debugger.
*/

#include <string>

using namespace std;

#include "../ram/ram.hpp"
#include "../registers/registers.hpp"
#include "../registers/specialregisters.hpp"

#include "z80cpu.hpp"

void Z80CPU::init() {
	Z80CPU::instructionString = "";
}

Z80CPU::Z80CPU() {
	Z80CPU::init();
}

void Z80CPU::loadUpRAM(unsigned char *ramPosition, int ramSize) {
	
}

void Z80CPU::run(unsigned short steps) {
	int counter = steps;
	while (counter != 0) {
		Z80CPU::step();
		--counter;
	}
}

void Z80CPU::step() {
	if (Z80CPU::mainRAM.read(Z80CPU::specialPurposeRegisters.getProgramCounter()) == 0x00) {
		/*
			NOP instruction:
			Does absolutely nothing except increment the PC.
		*/
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
	} else if (Z80CPU::mainRAM.read(Z80CPU::specialPurposeRegisters.getProgramCounter()) == 0x76) {
		/*
			HALT INSTRUCTION
		*/
		//Stays were it is.
	} else if (Z80CPU::mainRAM.read(Z80CPU::specialPurposeRegisters.getProgramCounter()) & 0xc0 == 0x40) {
		/*
			8-Bit LD r1, r2
		*/
		if (Z80CPU::mainRAM.read(Z80CPU::specialPurposeRegisters.getProgramCounter()) & 0xc7 == 0x46) {
			/*
				LD r, [HL]
			*/
			Z80CPU::mainRegisterSet.load8BitImm(
				Z80CPU::mainRAM.read(Z80CPU::specialPurposeRegisters.getProgramCounter()) >> 3 & 0x07,
				Z80CPU::mainRAM.read(Z80CPU::mainRegisterSet.get16BitRegister(REG_HL))
			);
			Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		}
	} else if (Z80CPU::mainRAM.read(Z80CPU::specialPurposeRegisters.getProgramCounter()) & 0x06 == 0x06) {
		//LD r, IMM
		REGISTER8 reg = Z80CPU::mainRAM.read(Z80CPU::specialPurposeRegisters.getProgramCounter()) >> 3;
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		Z80CPU::mainRegisterSet.load8BitImm(reg, Z80CPU::mainRAM.read(Z80CPU::specialPurposeRegisters.getProgramCounter()));
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
	}
}

string Z80CPU::prettyPrint() {
	
}

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
	date updated: 23/06/2014
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

/*
	Preprocessors for the Debugger:
	These  Bit Rotation preprocessors have come from Wikipedia. The link is:
	http://en.wikipedia.org/wiki/Circular_shift
*/
#define CHAR_BIT 8

#define ROTATE_LEFT(value, shift) value = (value << shift) | (value >> (sizeof(value) * CHAR_BIT - shift))
#define ROTATE_RIGHT(value, shift) value = (value >> shift) | (value << (sizeof(value) * CHAR_BIT - shift))

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
		Z80CPU::instructionString = "NOP";
	} else if (Z80CPU::retrieveFromAddress() >= 0x80 && Z80CPU::retrieveFromAddress() >= 0x87) {
		//ADC
	}
	
	Z80CPU::specialPurposeRegisters.incrementProgramCounter();
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
	retString += " IX: ";
	retString += convertHex(Z80CPU::specialPurposeRegisters.getIX());
	retString += " IY: ";
	retString += convertHex(Z80CPU::specialPurposeRegisters.getIY());
	retString += "\n";
	retString += "PC: ";
	retString += convertHex(Z80CPU::specialPurposeRegisters.getProgramCounter());
	retString += "\tSP: ";
	retString += convertHex(Z80CPU::specialPurposeRegisters.getStackPointer());
	retString += "\tInterrupt Vector: ";
	retString += convertHex(Z80CPU::specialPurposeRegisters.getInterruptVector());
	return retString;
}

string Z80CPU::getCurrentInstruction() {
	return Z80CPU::instructionString;
}

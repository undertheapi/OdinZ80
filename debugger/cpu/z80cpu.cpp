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
	} else if (Z80CPU::retrieveFromAddress() == 0x01) {
		Z80CPU::instructionString = "LD BC, ";
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		unsigned short immediateValue = (unsigned short) (Z80CPU::retrieveFromAddress());
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		immediateValue |= (unsigned short) (Z80CPU::retrieveFromAddress() << 8);
		Z80CPU::mainRegisterSet.load16BitImm(REG_BC, immediateValue);
		Z80CPU::instructionString += convertHex(immediateValue);
	} else if (Z80CPU::retrieveFromAddress() == 0x02) {
		Z80CPU::instructionString = "LD [BC], A";
		Z80CPU::mainRAM.write(
			Z80CPU::mainRegisterSet.get16BitRegister(REG_BC),
			Z80CPU::mainRegisterSet.get8BitRegister(REG_A)
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x03) {
		Z80CPU::instructionString = "INC BC";
		Z80CPU::mainRegisterSet.load16BitImm(
			REG_BC,
			Z80CPU::mainRegisterSet.get16BitRegister(REG_BC) + 1
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x04) {
		Z80CPU::instructionString = "INC B";
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_B,
			Z80CPU::mainRegisterSet.get8BitRegister(REG_B) + 1
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x05) {
		Z80CPU::instructionString = "DEC B";
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_B,
			Z80CPU::mainRegisterSet.get8BitRegister(REG_B) - 1
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x06) {
		Z80CPU::instructionString = "LD B, ";
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		unsigned char immediateValue = Z80CPU::retrieveFromAddress();
		Z80CPU::instructionString += convertHex(immediateValue);
	} else if (Z80CPU::retrieveFromAddress() == 0x07) {
		Z80CPU::instructionString = "RLCA";
		
		/*
			Check if the left most bit is set on register A
		*/
		if (Z80CPU::mainRegisterSet.get8BitRegister(REG_A) & 0x80) {
			Z80CPU::mainRegisterSet.setFlag(CARRY_FLAG);
		} else {
			Z80CPU::mainRegisterSet.resetFlag(CARRY_FLAG);
		}
		
		Z80CPU::mainRegisterSet.resetFlag(ADD_SUBRACT_FLAG);
		Z80CPU::mainRegisterSet.resetFlag(HALF_CARRY_FLAG);
		
		unsigned char immediateValue = Z80CPU::mainRegisterSet.get8BitRegister(REG_A);
		
		ROTATE_LEFT(immediateValue, 1);
		
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_A,
			immediateValue
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x08) {
		Z80CPU::instructionString = "EX AF, AF\'";
		
		unsigned short tmp = Z80CPU::mainRegisterSet.get16BitRegister(REG_AF);
		
		Z80CPU::mainRegisterSet.load16BitImm(
			REG_AF,
			Z80CPU::alternateRegisterSet.get16BitRegister(REG_AF)
		);
		
		Z80CPU::alternateRegisterSet.load16BitImm(REG_AF, tmp);
	} else if (Z80CPU::retrieveFromAddress() == 0x09) {
		Z80CPU::instructionString = "ADD HL, BC";
		
		Z80CPU::mainRegisterSet.load16BitImm(
			REG_HL,
			Z80CPU::mainRegisterSet.get16BitRegister(REG_BC)
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x0a) {
		Z80CPU::instructionString = "LD A, [BC]";
		
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_A,
			Z80CPU::mainRAM.read(Z80CPU::mainRegisterSet.get16BitRegister(REG_BC))
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x0b) {
		Z80CPU::instructionString = "DEC BC";
		
		Z80CPU::mainRegisterSet.load16BitImm(
			REG_BC,
			Z80CPU::mainRegisterSet.get16BitRegister(REG_BC) - 1
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x0c) {
		Z80CPU::instructionString = "INC C";
		
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_C,
			Z80CPU::mainRegisterSet.get8BitRegister(REG_C) + 1
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x0d) {
		Z80CPU::instructionString = "DEC C";
		
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_C,
			Z80CPU::mainRegisterSet.get8BitRegister(REG_C) - 1
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x0e) {
		Z80CPU::instructionString = "LD C, ";
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_C,
			Z80CPU::retrieveFromAddress()
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x0f) {
		Z80CPU::instructionString = "RRCA";
		
		/*
			Check if the left most bit is set on register A
		*/
		if (Z80CPU::mainRegisterSet.get8BitRegister(REG_A) & 0x01) {
			Z80CPU::mainRegisterSet.setFlag(CARRY_FLAG);
		} else {
			Z80CPU::mainRegisterSet.resetFlag(CARRY_FLAG);
		}
		
		Z80CPU::mainRegisterSet.resetFlag(ADD_SUBRACT_FLAG);
		Z80CPU::mainRegisterSet.resetFlag(HALF_CARRY_FLAG);
		
		unsigned char immediateValue = Z80CPU::mainRegisterSet.get8BitRegister(REG_A);
		
		ROTATE_RIGHT(immediateValue, 1);
		
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_A,
			immediateValue
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x10) {
		Z80CPU::instructionString = "DJNZ ";
		
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_B,
			Z80CPU::mainRegisterSet.get8BitRegister(REG_B) - 1
		);
		
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		
		Z80CPU::instructionString += convertHex(Z80CPU::retrieveFromAddress());
		
		if (Z80CPU::mainRegisterSet.get8BitRegister(REG_B) != 0) {
			Z80CPU::specialPurposeRegisters.loadProgramCounter(
				Z80CPU::specialPurposeRegisters.getProgramCounter() + Z80CPU::retrieveFromAddress()
			);
		}
	} else if (Z80CPU::retrieveFromAddress() == 0x11) {
		Z80CPU::instructionString = "LD DE, ";
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		unsigned short immediateValue = (unsigned short) Z80CPU::retrieveFromAddress();
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		immediateValue |= (unsigned short) (Z80CPU::retrieveFromAddress() << 8);
		Z80CPU::instructionString += convertHex(immediateValue);
		
		Z80CPU::mainRegisterSet.load16BitImm(
			REG_DE,
			immediateValue
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x12) {
		Z80CPU::instructionString = "LD [DE], A";
		
		Z80CPU::mainRAM.write(
			Z80CPU::mainRegisterSet.get16BitRegister(REG_DE),
			Z80CPU::mainRegisterSet.get8BitRegister(REG_A)
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x13) {
		Z80CPU::instructionString = "INC DE";
		
		Z80CPU::mainRegisterSet.load16BitImm(
			REG_DE,
			Z80CPU::mainRegisterSet.get16BitRegister(REG_DE) + 1
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x14) {
		Z80CPU::instructionString = "INC D";
		
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_D,
			Z80CPU::mainRegisterSet.get8BitRegister(REG_D) + 1
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x15) {
		Z80CPU::instructionString = "DEC D";
		
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_D,
			Z80CPU::mainRegisterSet.get8BitRegister(REG_D) - 1
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x16) {
		Z80CPU::instructionString = "LD D, ";
		
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		
		Z80CPU::instructionString += (Z80CPU::retrieveFromAddress());
		
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_D,
			Z80CPU::retrieveFromAddress()
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x17) {
		Z80CPU::instructionString = "RLA";
		
		unsigned char accumValue = Z80CPU::mainRegisterSet.get8BitRegister(REG_A);
		
		unsigned char carryOverValue = 0x00;
		
		if (Z80CPU::mainRegisterSet.getFlag(CARRY_FLAG)) {
			carryOverValue = 0x01;
		}
		
		if (accumValue & 0x80 != 0) {
			Z80CPU::mainRegisterSet.setFlag(CARRY_FLAG);
		} else {
			Z80CPU::mainRegisterSet.resetFlag(CARRY_FLAG);
		}
		
		accumValue = accumValue << 1;
		
		accumValue |= carryOverValue;
		
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_A,
			accumValue
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x18) {
		Z80CPU::instructionString = "JR ";
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		Z80CPU::instructionString = convertHex(Z80CPU::retrieveFromAddress());
		Z80CPU::specialPurposeRegisters.loadProgramCounter(
			Z80CPU::specialPurposeRegisters.getProgamCounter() + Z80CPU::retrieveFromAddress()
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x19) {
		Z80CPU::instructionString = "ADD HL, DE";
		
		Z80CPU::mainRegisterSet.load16BitImm(
			REG_HL,
			Z80CPU::mainRegisterSet.get16BitRegister(REG_HL) + Z80CPU::mainRegisterSet.get16BitRegister(REG_DE)
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x1a) {
		Z80CPU::instructionString = "ADD A, [DE]";
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_A,
			Z80CPU::mainRAM.read(Z80CPU::mainRegisterSet.get16BitRegister(REG_DE))
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x1b) {
		Z80CPU::instructionString = "DEC DE";
		Z80CPU::mainRegisterSet.load16BitImm(
			REG_DE,
			Z80CPU::mainRegisterSet.get16BitRegister(REG_DE) - 1
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x1c) {
		Z80CPU::instructionString = "INC E";
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_E,
			Z80CPU::mainRegisterSet.get8BitRegister(REG_E) + 1
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x1d) {
		Z80CPU::instructionString = "DEC E";
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_E,
			Z80CPU::mainRegisterSet.get8BitRegister(REG_E) - 1
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x1e) {
		Z80CPU::instructionString = "LD E, ";
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		Z80CPU::instructionString += convertHex(Z80CPU::retrieveFromAddress());
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_E,
			Z80CPU::retrieveFromAddress()
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x1f) {
		Z80CPU::instructionString = "RRA";
		
		unsigned char accumValue = Z80CPU::mainRegisterSet.get8BitRegister(REG_A);
		
		unsigned char carryOverValue = 0x00;
		
		if (Z80CPU::mainRegisterSet.getFlag(CARRY_FLAG)) {
			carryOverValue = 0x80;
		}
		
		if (accumValue & 0x80 != 0) {
			Z80CPU::mainRegisterSet.setFlag(CARRY_FLAG);
		} else {
			Z80CPU::mainRegisterSet.resetFlag(CARRY_FLAG);
		}
		
		accumValue = accumValue >> 1;
		
		accumValue |= carryOverValue;
		
		Z80CPU::mainRegisterSet.load8BitImm(
			REG_A,
			accumValue
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x20) {
		Z80CPU::instructionString = "JR NZ ";
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		Z80CPU::instructionString += convertHex(Z80CPU::retrieveFromAddress());
		
		if (!Z80CPU::mainRegisterSet.getFlag(ZERO_FLAG)) {
			
			Z80CPU::specialPurposeRegisters.loadProgramCounter(
				//We minus one as to make up for the next increment in the PC.
				Z80CPU::specialPurposeRegisters.getProgramCounter() + Z80CPU::retrieveFromAddress() - 1
			);
		}
	} else if (Z80CPU::retrieveFromAddress() == 0x21) {
		Z80CPU::instructionString = "LD HL, ";
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		unsigned short immediateValue = (unsigned short) Z80CPU::retrieveFromAddress();
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		immediateValue |= (unsigned short) (Z80CPU::retrieveFromAddress() << 8);
		Z80CPU::instructionString += convertHex(immediateValue);
		Z80CPU::mainRegisterSet.load16BitImm(
			REG_HL,
			immediateValue
		);
	} else if (Z80CPU::retrieveFromAddress() == 0x22) {
		Z80CPU::instructionString = "LD [";
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		unsigned short addressValue = (unsigned short) Z80CPU::retrieveFromAddress();
		Z80CPU::specialPurposeRegisters.incrementProgramCounter();
		addressValue |= (unsigned short) (Z80CPU::retrieveFromAddress() << 8);
		Z80CPU::instructionString += convertHex(addressValue);
		Z80CPU::instructionString += "], HL";
		
		Z80CPU::mainRAM.write(
			addressValue,
			(unsigned char ) Z80CPU::mainRegisterSet.get16BitRegister(REG_HL)
		);
		
		Z80CPU::mainRAM.write(
			addressValue + 1,
			(unsigned char ) (Z80CPU::mainRegisterSet.get16BitRegister(REG_HL) >> 8)
		);
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

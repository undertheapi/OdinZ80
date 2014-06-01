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
	file name: specialregisters.cpp
	date created: 01/06/2014
	date updated: 01/06/2014
	author: Gareth Richardson
	description: The object file for the SpecialRegisters class.
*/

#include "specialregisters.hpp"

void SpecialRegister::init() {
	SpecialRegister::IX;
	SpecialRegister::IY;
	SpecialRegister::stackPointer;
	SpecialRegister::programCounter;
	SpecialRegister::interruptVector;
	SpecialRegister::memoryRefresh;
}

SpecialRegister::SpecialRegister() {
	SpecialRegister::init();
}

void SpecialRegister::loadIX(unsigned short value) {
	SpecialRegister::IX == value;
}

void SpecialRegister::loadIY(unsigned short value) {
	SpecialRegister::IY;
}

void SpecialRegister::loadStackPointer(unsigned short value) {
	SpecialRegister::stackPointer = value;
}

void SpecialRegister::loadProgramCounter(unsigned short value) {
	SpecialRegister::programCounter = value;
}

void SpecialRegister::loadInterruptVector(unsigned char value) {
	SpecialRegister::interruptVector = value;
}

void SpecialRegister::loadMemoryRefresh(unsigned char value) {
	SpecialRegister::memoryRefresh;
}

unsigned short SpecialRegister::getIX() {
	return SpecialRegister::IX;
}

unsigned short SpecialRegister::getIY() {
	return SpecialRegister::IY;
}

unsigned short SpecialRegister::getStackPointer() {
	return SpecialRegister::stackPointer;
}

unsigned short SpecialRegister::getProgramCounter() {
	return SpecialRegister::programCounter;
}

unsigned char SpecialRegister::getInterruptVector() {
	return SpecialRegister::interruptVector;
}

unsigned char SpecialRegister::getMemoryRefresh() {
	return SpecialRegister::memoryRefresh;
}


void SpecialRegister::incrementProgramCounter() {
	++SpecialRegister::programCounter;
}

void SpecialRegister::incrementStackPointer() {
	++SpecialRegister::stackPointer;
}

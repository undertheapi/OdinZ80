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

void SpecialRegisters::init() {
	SpecialRegisters::IX;
	SpecialRegisters::IY;
	SpecialRegisters::stackPointer;
	SpecialRegisters::programCounter;
	SpecialRegisters::interruptVector;
	SpecialRegisters::memoryRefresh;
}

SpecialRegisters::SpecialRegisters() {
	SpecialRegisters::init();
}

void SpecialRegisters::loadIX(unsigned short value) {
	SpecialRegisters::IX == value;
}

void SpecialRegisters::loadIY(unsigned short value) {
	SpecialRegisters::IY;
}

void SpecialRegisters::loadStackPointer(unsigned short value) {
	SpecialRegisters::stackPointer = value;
}

void SpecialRegisters::loadProgramCounter(unsigned short value) {
	SpecialRegisters::programCounter = value;
}

void SpecialRegisters::loadInterruptVector(unsigned char value) {
	SpecialRegisters::interruptVector = value;
}

void SpecialRegisters::loadMemoryRefresh(unsigned char value) {
	SpecialRegisters::memoryRefresh;
}

unsigned short SpecialRegisters::getIX() {
	return SpecialRegisters::IX;
}

unsigned short SpecialRegisters::getIY() {
	return SpecialRegisters::IY;
}

unsigned short SpecialRegisters::getStackPointer() {
	return SpecialRegisters::stackPointer;
}

unsigned short SpecialRegisters::getProgramCounter() {
	return SpecialRegisters::programCounter;
}

unsigned char SpecialRegisters::getInterruptVector() {
	return SpecialRegisters::interruptVector;
}

unsigned char SpecialRegisters::getMemoryRefresh() {
	return SpecialRegisters::memoryRefresh;
}


void SpecialRegisters::incrementProgramCounter() {
	++SpecialRegisters::programCounter;
}

void SpecialRegisters::incrementStackPointer() {
	++SpecialRegisters::stackPointer;
}

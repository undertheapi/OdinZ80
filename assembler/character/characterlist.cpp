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
	file name: characterlist.cpp
	date created: 28/08/2012
	date updated: 06/05/2015
	author: Gareth Richardson
	description: This is the object file for the CharacterList class. Implement all
	the class methods here.
*/

#include "characterlist.hpp"

bool CharacterList::isValidCharacter(CHARACTER value) {
	/*
		so far these are the only valid characters the Odin Assembler can deal with.
	*/
	return value == '\n' || value == '\t' || value >= 32 && value <= 126 || value == 13;
}

void CharacterList::init() {
	/*
		All the variables are initialised to 0.
	*/
	CharacterList::length = CharacterList::currentPosition = CharacterList::errorState = 0;

	/*
		We are making all the bytes in the reserved memory 0x00, just in case
		if there are any bugs in the code.
	*/
	for (int index = 0; index != MAX_SIZE; index++)
		CharacterList::fileInMemory[index] = 0;
}

CharacterList::CharacterList() {
	CharacterList::init();
}

CharacterList::~CharacterList() {
	/*
		while (!CharacterList::isEmpty())
			CharacterList::pop();
	*/

	/*
		The reason for this code below and not the top one is because the
		program kept crashing when the Deconstructor was run. I believe it
		could have been either a buffer overflow, stack overflow or an
		infinite loop.
	*/
	for (int index = 0; index != MAX_SIZE; index++)
		CharacterList::fileInMemory[index] = 0;
}

bool CharacterList::isEmpty() {
	return CharacterList::length == 0;
}

bool CharacterList::isFull() {
	return CharacterList::length == MAX_SIZE;
}

bool CharacterList::push(CHARACTER charValue) {
	if (!CharacterList::isValidCharacter(charValue)) {
		CharacterList::errorState |= INVALID_CHAR;
		return false;
	} else if (CharacterList::isFull()) {
		CharacterList::errorState |= LIST_FULL;
		return false;
	}
	if (charValue != 0x0d) {
		CharacterList::fileInMemory[currentPosition] = charValue;
		++CharacterList::length, ++CharacterList::currentPosition;
	}
	return true;
}

CHARACTER CharacterList::peekValue() {
	if (CharacterList::isEmpty()) {
		CharacterList::errorState |= LIST_EMPTY;
		return 0;
	}
	return CharacterList::fileInMemory[CharacterList::currentPosition];
}

void CharacterList::finishedFile() {
	if (CharacterList::isEmpty())
		CharacterList::errorState |= LIST_EMPTY;

	CharacterList::currentPosition = 0;
}

bool CharacterList::pop() {
	if (!CharacterList::isEmpty()) {
		CharacterList::fileInMemory[CharacterList::currentPosition] = 0;
		++CharacterList::currentPosition;
		--CharacterList::length;

		/*
			If the list is empty now, we set the values back to the first
			position of the reserved memory. This is a bug fix.
		*/
		if (!CharacterList::length)
			CharacterList::currentPosition = 0;

		return true;
	}
	CharacterList::errorState |= LIST_EMPTY;
	return false;
}

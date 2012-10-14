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
	file name: characterlist.cpp
	date created: 28/08/2012
	date updated: 12/10/2012
	author: Gareth Richardson
	description: This is the object file for the CharacterList class. Implement all
	the class methods here.
*/

#include <cstdlib>

#include "characterlist.hpp"

bool CharacterList::isValidCharacter(CHARACTER value) {
	/*
		so far these are the only valid characters the Odin Assembler can deal with.
	*/
	return value == '\n' || value == '\t' || (value >= 32 && value <= 126);
}

void CharacterList::init() {
	/*
		Allocation of memory for the file data here.
		ADD more MEGABYTES when possible.
	*/
	CharacterList::head = (CHARACTER*)malloc(ONE_MEGABYTE);
	CharacterList::tail = CharacterList::head;
	
	/*
		fills that part of memory with 0 (clears memory):
	*/
	for (int index = 0; index < ONE_MEGABYTE; index++) {
		CharacterList::head[index] = 0;
	}
}

CharacterList::CharacterList() {
	CharacterList::init();
}

CharacterList::~CharacterList() {
	while (!CharacterList::isEmpty()) {
		CharacterList::pop();
	}
}

bool CharacterList::isEmpty() {
	/*
		checks for a NULL pointer.
	*/
	return CharacterList::head[0] == 0;
}

bool CharacterList::push(CHARACTER charValue) {
	/*
		fix buffer overflow issue!
	*/
	if (CharacterList::isValidCharacter(charValue)) {
		CharacterList::tail[0] = charValue;
		CharacterList::tail++;
		return true;
	} else {
		return false;
	}
}

CHARACTER CharacterList::peekValue() {
	return CharacterList::head[0];
}

char* CharacterList::peekFileName() {
	return 0;
}

void CharacterList::pop() {
	/*
		should only run this if the list is not empty. So we are
		not throwing any errors.
	*/
	if (!CharacterList::isEmpty()) {
		CharacterList::head++;
		//return CharacterList::head - 1;
	}
}

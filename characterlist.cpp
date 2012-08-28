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
	date updated: 28/08/2012
	author: Gareth Richardson
	description: This is the object file for the CharacterList class. Implement all
	the class methods here.
*/

#include "characterlist.hpp"

/*
	defien the NULL value here. We are not including any c standard libraries here. 
*/
#define NULL 0

bool CharacterList::isValidCharacter(CHARACTER value) {
	/*
		so far these are the only valid characters the Odin Assembler can deal with.
	*/
	return value == '\n' || value == '\t' || (value >= 32 && value <= 126);
}

void CharacterList::init() {
	CharacterList::head = NULL;
	CharacterList::tail = NULL;
}

CharacterList::CharacterList() {
	CharacterList::init();
}

bool CharacterList::isEmpty() {
	return CharacterList::head == NULL;
}

bool CharacterList::push(CHARACTER charValue, int line, char* file) {
	if (!CharacterList::isValidCharacter(charValue)) {
		return false;
	} else {
		CharNodePtr newNode = new CharNode;
		newNode->value = charValue;
		newNode->lineNumber = line;
		newNode->fileName = file;
		newNode->next = NULL;
		if (CharacterList::isEmpty()) {
			CharacterList::head = newNode;
			CharacterList::tail = newNode;
		} else if (CharacterList::head == CharacterList::tail) {
			CharacterList::head->next = newNode;
			CharacterList::tail = newNode;
		} else {
			CharacterList::tail->next = newNode;
			CharacterList::tail = newNode;
		}
		return true;
	}
}

CHARACTER CharacterList::peekValue() {
	return CharacterList::head->value;
}

int CharacterList::peekLine() {
	return CharacterList::head->lineNumber;
}

char* CharacterList::peekFile() {
	return CharacterList::head->fileName;
}

void CharacterList::pop() {
	/*
		should only run this if the list is not empty. So we are
		not throwing any errors.
	*/
	if (!CharacterList::isEmpty()) {
		CharacterList::head = CharacterList::head->next;
	}
}

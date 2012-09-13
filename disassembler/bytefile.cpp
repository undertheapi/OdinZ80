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
	file name: bytefile.cpp
	compiled name: bytefile.o
	date created: 3/8/2012
	date updated: 3/8/2012
	author: Gareth Richardson
	description: this is the object file for the ByteFile
	class. Linked to this file when compiling the whole
	project.
*/

#include "bytefile.hpp"

#define NULL 0

ByteFile::ByteFile() {
	ByteFile::head = NULL;
	ByteFile::tail = NULL;
}

bool ByteFile::isEmpty() {
	if (ByteFile::head == NULL) {
		return true;
	} else {
		return false;
	}
}

void ByteFile::push(BYTE value) {
	ByteNode* newNode = new ByteNode;
	newNode->value = value;
	newNode->next = NULL;
	if (ByteFile::isEmpty()) {
		ByteFile::head = newNode;
		ByteFile::tail = newNode;
	} else {
		if (ByteFile::head == ByteFile::tail) {
			ByteFile::head->next = newNode;
			ByteFile::tail = newNode;
		} else {
			ByteFile::tail->next = newNode;
			ByteFile::tail = newNode;
		}
	}
}

BYTE ByteFile::pop() {
	BYTE retValue = ByteFile::head->value;
	ByteFile::head = ByteFile::head->next;
	return retValue;
}

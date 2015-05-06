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
	file name: bytecode.cpp
	date created: 28/09/2012
	date updated: 05/05/2015
	author: Gareth Richardson
	description: This is the machine code, the output of the assembler.
*/

#include "bytecode.hpp"

/*
	we make our own NULL definition so we do not have to include any standard c libraries.
*/
#define NULL 0

void ByteCode::init() {
	ByteCode::head = ByteCode::tail = NULL;
	ByteCode::size = 0;
}

ByteCode::ByteCode() {
	ByteCode::init();
}

int ByteCode::getSize() {
	return ByteCode::size;
}

/*
	Push an element of the byte code (a BYTE of data) onto the back of the
	Queue.
*/
void ByteCode::pushElement(unsigned char value) {
	ByteNodePtr newNode = new ByteNode;
	newNode->byte = value;
	newNode->next = NULL;
	if (ByteCode::size == 0) {
		ByteCode::head = ByteCode::tail = newNode;
	} else if (ByteCode::head == ByteCode::tail) {
		ByteCode::head->next = ByteCode::tail = newNode;
	} else {
		ByteCode::tail->next = ByteCode::tail = newNode;
	}
	++ByteCode::size;
}

void ByteCode::setElement(int index, unsigned char value) {
	/*
		checks if the index is in range:
	*/
	if (index >= 0 && index < ByteCode::size) {
		int counter = 0;
		ByteNodePtr tempNode = ByteCode::head;
		while (counter++ != index) {
			tempNode = tempNode->next;
		}
		tempNode->byte = value;
	} else {
		ByteCode::pushElement(value);
	}
}

unsigned char ByteCode::getElement(int index) {
	int counter = 0;
	ByteNodePtr tempNode = ByteCode::head;
	while (counter++ != index) {
		tempNode = tempNode->next;
	}
	return tempNode->byte;
}


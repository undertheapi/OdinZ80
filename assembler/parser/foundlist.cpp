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
	file name: foundlist.cpp
	date created: 14/02/2013
	date updated: 14/02/2013
	author: Gareth Richardson
	description: All the found addresses are in this list,this is the object file.
*/

#include <string>

using namespace std;

#include "foundlist.hpp"

//#define NULL 0

void FoundList::init() {
	FoundList::head = NULL;
	FoundList::tail = NULL;
	
	FoundList::size = 0;
}

FoundList::FoundList() {
	FoundList::init();
}

bool FoundList::isEmpty() {
	return FoundList::head == NULL;
}

int FoundList::getSize() {
	return FoundList::size;
}

void FoundList::addAddress(string name, unsigned short addr) {
	AddressNode* newNode = new AddressNode;
	newNode->value = name;
	newNode->address = addr;
	newNode->next = NULL;
	if (FoundList::isEmpty()) {
		FoundList::head = newNode;
		FoundList::tail = newNode;
	} else if (FoundList::head == FoundList::tail) {
		FoundList::tail = newNode;
		FoundList::head->next = newNode;
	} else {
		FoundList::tail->next = newNode;
		FoundList::tail = newNode;
	}
	FoundList::size++;
}

string FoundList::getName(int index) {
	int count = 0;
	AddressNode* pointer = FoundList::head;
	while (count != index) {
		pointer = pointer->next;
		count++;
	}
	return pointer->value;
}

unsigned short FoundList::getAddress(int index) {
	int count = 0;
	AddressNode* pointer = FoundList::head;
	while (count != index) {
		pointer = pointer->next;
		count++;
	}
	return pointer->address;
}

bool FoundList::doesNameExist(string value) {
	if (FoundList::isEmpty()) {
		return false;
	}
	bool found = false;
	int index = 0;
	while (index < FoundList::size && !found) {
		if (FoundList::getName(index).compare(value) == 0) {
			found = true;
		}
		index++;
	}
	return found;
}


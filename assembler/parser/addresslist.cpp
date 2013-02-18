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
	file name: addresslist.cpp
	date created: 14/02/2013
	date updated: 14/02/2013
	author: Gareth Richardson
	description: This is a list of addresses not found yet.
*/

#include <string>

using namespace std;

#include "bytecode.hpp"
#include "addresslist.hpp"

//#define NULL 0

void AddressList::init() {
	AddressList::head = NULL;
	AddressList::tail = NULL;
}

AddressList::AddressList() {
	AddressList::init();
}

bool AddressList::isEmpty() {
	return AddressList::head == NULL;
}

void AddressList::addAddress(string value, unsigned short addr) {
	AddressNode* newNode = new AddressNode;
	newNode->value = value;
	newNode->address = addr;
	newNode->next = NULL;
	if (AddressList::isEmpty()) {
		AddressList::head = newNode;
		AddressList::tail = newNode;
	} else if (AddressList::head == AddressList::tail) {
		AddressList::tail = newNode;
		AddressList::head->next = AddressList::tail;
	} else {
		AddressList::tail->next = newNode;
		AddressList::tail = newNode;
	}
}

string AddressList::getLastName() {
	return AddressList::tail->value;
}

void AddressList::processAddress(string name, unsigned short newAddress, ByteCode* bCode) {
	AddressNode* pointer = AddressList::head;
	
	while (pointer != NULL) {
		if (pointer->value.compare(name) == 0) {
			bCode->setElement((int)pointer->address, (unsigned char) newAddress);
			bCode->setElement((int)(pointer->address + 1), (unsigned char) (newAddress>> 8));
			
			if (pointer == AddressList::head) {
				AddressList::head = AddressList::head->next;
			} else {
				AddressNode* tmp = AddressList::head;
				while (tmp->next != pointer) {
					tmp = tmp->next;
				}
				tmp->next = pointer->next;
			}
			pointer = AddressList::head;
		} else {
			pointer = pointer->next;
		}
	}
}


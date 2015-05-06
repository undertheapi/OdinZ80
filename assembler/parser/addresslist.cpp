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
	file name: addresslist.cpp
	date created: 14/02/2013
	date updated: 16/04/2015
	author: Gareth Richardson
	description: This is a list of addresses not found yet.
*/

#include <string>

using namespace std;

#include "bytecode.hpp"
#include "addresslist.hpp"

/*
	Returns the string element in the AddressList that is at the index.
	The string is the name of the address that is in the AddressList.
	You need to do an array index check before giving the index value to
	this parameter.
*/
string AddressList::getElement(int index) {
	int count = 0;
	AddressNode* pointer = AddressList::head;
	while (count++ != index) {
		pointer = pointer->next;
	}
	return pointer->value;
}

/*
	Returns the integer address element in the AddressList that is at the index.
	You need to do an array index check before giving the index value to
	this parameter.
*/
unsigned short AddressList::getAddress(int index) {
	int count = 0;
	AddressNode* pointer = AddressList::head;
	while (count++ != index) {
		pointer = pointer->next;
	}
	return pointer->address;
}

/*
	Removes the element at the specified index.
	Do an array bounds check before giving the index parameter.
*/
void AddressList::deleteElement(int index) {
	if (!index) {
		if (AddressList::size == 1) {
			AddressList::head = NULL;
		} else {
			AddressList::head = AddressList::head->next;
		}
	} else {
		int count = 1;
		AddressNode* previous = AddressList::head;
		AddressNode* pointer = AddressList::head->next;
		while (count++ != index) {
			previous = pointer;
			pointer = pointer->next;
		}
		previous->next = pointer->next;
	}
	--AddressList::size;
}

/*
	Initiates the Singly Linked List for the Addresses.
*/
void AddressList::init() {
	AddressList::head = NULL;
	AddressList::size = 0;
}

AddressList::AddressList() {
	AddressList::init();
}

bool AddressList::isEmpty() {
	return AddressList::head == NULL;
}

void AddressList::addAddress(string value, unsigned short addr) {
	if (AddressList::isEmpty()) {
		AddressNode* newNode = new AddressNode;
		newNode->value = value;
		newNode->address = addr;
		newNode->next = NULL;
		AddressList::head = newNode;
	} else {
		AddressNode* newNode = new AddressNode;
		newNode->value = value;
		newNode->address = addr;
		newNode->next = AddressList::head;
		AddressList::head = newNode;
	}
	++AddressList::size;
}

string AddressList::getLastName() {
	return AddressList::head->value;
}

void AddressList::processAddress(string name, unsigned short newAddress, ByteCode* bCode) {
	int index = 0;
	while (index < AddressList::size) {
		if (!AddressList::getElement(index).compare(name)) {
			bCode->setElement(AddressList::getAddress(index), (unsigned char) newAddress);
			bCode->setElement(AddressList::getAddress(index) + 1, (unsigned char) (newAddress >> 8));
			AddressList::deleteElement(index);
			index = 0;
		} else {
			++index;
		}
	}
}


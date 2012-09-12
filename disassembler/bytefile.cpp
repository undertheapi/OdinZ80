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

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

#include <string>

using namespace std;

#include "symbol_table.hpp"

SYMBOL_NODE* generateNode(string* strObj, int value, SYMBOL_NODE* next) {
	SYMBOL_NODE* node = new SYMBOL_NODE;
	node->symbol = strObj;
	node->mappedValue = value;
	node->nextNode = next;
	return node;
}

int SYMBOL_TABLE::checkSymbol(string* strObj) {
	if (SYMBOL_TABLE::tableHead == NULL)
		return -1;
	
	SYMBOL_NODE* pointer = SYMBOL_TABLE::tableHead;
	int counter = 0;
	while (pointer != NULL) {
		if (pointer->symbol->compare(strObj->c_str()) == 0)
			return counter;
		else {
			pointer = pointer->nextNode;
			++counter;
		}
	}
	return -1;
}

SYMBOL_TABLE::SYMBOL_TABLE() {
	SYMBOL_TABLE::init();
}

void SYMBOL_TABLE::init() {
	SYMBOL_TABLE::tableHead = NULL;
	SYMBOL_TABLE::tableTail = NULL;
	SYMBOL_TABLE::indexCount = 0;
}

int SYMBOL_TABLE::addSymbol(string* strObj) {
	if (SYMBOL_TABLE::tableHead == NULL) {
		SYMBOL_TABLE::tableHead = generateNode(strObj, -1, NULL);
		SYMBOL_TABLE::tableTail = SYMBOL_TABLE::tableHead;
		return 0;
	} else if (SYMBOL_TABLE::tableHead == SYMBOL_TABLE::tableTail) {
		if (SYMBOL_TABLE::tableHead->symbol->compare(strObj->c_str()) == 0)
			return SYMBOL_TABLE::indexCount;

		SYMBOL_TABLE::tableTail = generateNode(strObj, -1, NULL);
		SYMBOL_TABLE::tableHead->nextNode = SYMBOL_TABLE::tableTail;
		return ++SYMBOL_TABLE::indexCount;
	} else {
		int index = SYMBOL_TABLE::checkSymbol(strObj);
		if (index != -1)
			return index;
		
		SYMBOL_TABLE::tableTail->nextNode = generateNode(strObj, -1, NULL);
		SYMBOL_TABLE::tableTail = SYMBOL_TABLE::tableTail->nextNode;
		return ++SYMBOL_TABLE::indexCount;
	}
}

int SYMBOL_TABLE::addSymbol(string* strObj, int value) {
	int index = SYMBOL_TABLE::addSymbol(strObj);
	SYMBOL_TABLE::setSymbolValue(index, int value);
	return index;
}


int SYMBOL_TABLE::getValue(int index) {
	int count = 0;
	
	SYMBOL_NODE* pointer = SYMBOL_TABLE::tableHead;
	
	while (count++ != index)
		pointer = pointer->nextNode;
	
	return pointer->mappedValue;
}


bool SYMBOL_TABLE::setSymbolValue(int index, int value) {
	if (index < 0 && index >= SYMBOL_TABLE::indexCount)
		return false;
	
	int count = 0;
	
	SYMBOL_NODE* pointer = SYMBOL_TABLE::tableHead;
	
	while (count++ != index)
		pointer = pointer->nextNode;
	
	pointer->mappedValue = value;
	return true;
}

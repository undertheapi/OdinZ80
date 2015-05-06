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
	file name: tokenlist.cpp
	date created: 29/08/2012
	date updated: 05/05/2015
	author: Garth Richardson
	description: The implementation of the TokenList class. The data structure used is a Queue.
*/

#include <string>

using namespace std;

#include "tokenlist.hpp"

void TokenList::init() {
	TokenList::head = NULL;
	TokenList::tail = NULL;
}

TokenList::TokenList() {
	TokenList::init();
}

bool TokenList::isEmpty() {
	return TokenList::head == NULL;
}

/*
	Push the TokenNodePtr structure to the BACK of the Singly Linked List.
	This is used in the Lexical Analyser.
*/
void TokenList::push(TokenNodePtr obj) {
	if (TokenList::isEmpty()) {
		TokenList::head = TokenList::tail = obj;
	} else {
		TokenList::tail->next = TokenList::tail = obj;
	}
}

/*
	The is for the Parser. THis method will push a TokenNodePtr structure
	to the front of the SinglyLinkedList. The Parser uses this when validating
	the Assembly Source Code.
*/
void TokenList::pushFront(TokenNodePtr obj) {
	if (TokenList::isEmpty()) {
		TokenList::head = TokenList::tail = obj;
	} else {
		obj->next = TokenList::tail;
		TokenList::head = obj;
	}
}

/*
	This will remove the top Token on the list (in its head).
	It also returns the TokenNodePtr.
	Use in conjunction with the pushFront() method and the
	parser.
*/
TokenNodePtr TokenList::specialPop() {
	if (!TokenList::isEmpty()) {
		TokenNodePtr pointer = TokenList::head;
		TokenList::head = pointer->next;
		return pointer;
	}
	return NULL;
}

/*
	Removes the top Token from the Singly Linked List.
	TODO Some error state code and validation just in case.
*/
void TokenList::pop() {
	if (!TokenList::isEmpty()) {
		TokenNodePtr pointer = TokenList::head;
		TokenList::head = pointer->next;
		delete pointer;
	}
}

/*
	Returns the token type of the token that is in the front of the Queue.
	It will return a negative number if the token list is empty as a way to capture
	any errors.
*/
TOKEN_TYPE TokenList::peekTokenType() {
	if (!TokenList::isEmpty())
		return TokenList::head->type;
	
	return -1;
}

/*
	This gets the value of the token at the front of the Queue.
	Make sure you can handle the error if the Queue is empty.
*/
string TokenList::peekValue() {
	return TokenList::head->value;
}

int TokenList::peekLineNumber() {
	if (!TokenList::isEmpty())
		return TokenList::head->lineNumber;
	
	return -1;
}

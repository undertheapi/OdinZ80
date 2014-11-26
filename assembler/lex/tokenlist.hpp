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
	file name: tokenlist.hpp
	date created: 29/08/2012
	date updated: 26/11/2014
	author: Gareth Richardson
	description: Were all the Tokens from the Lex class will be stored. The data structure used
	is a Queue.
*/

#include "tokennode.hpp"
#include "tokentype.hpp"

class TokenList {
	private:
		/*
			The TokenList class is a Singly Linked List of TokenNodes. These
			two TokenNode pointers are the typical 'head' and 'tail' parts of
			one of these data structures.
		*/
		TokenNodePtr head;
		TokenNodePtr tail;

		/*
			All initialising code is to go in this method, it is called in the
			constructor.
		*/
		void init();
	public:
		TokenList();

		/*
			When the list is empty, TRUE is returned, else false.
		*/
		bool isEmpty();

		/*
			This method will push a Token Node Pointer to the back of the Queue.
		*/
		void push(TokenNodePtr obj);
		
		/*
			This method will push a Token Node Pointer to the front of the Queue.
			This will be used in the parser.
		*/
		void pushFront(TokenNodePtr obj);

		void pop();
		
		/*
			This method will pop the top Token Node Pointer from the front of the Queue and return it.
			This will be used in the parser.
		*/
		TokenNodePtr pop();

		TOKEN_TYPE peekTokenType();

		string peekValue();

		int peekLineNumber();
};

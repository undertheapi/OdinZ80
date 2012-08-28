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
	file name: characterlist.hpp
	date craeted: 28/8/2012
	date updated: 28/8/2012
	author: Gareth Richardson
	description: This is the header file for the class CharacterList. This stores a
	Singly Linked List of characters using the data structure CharNode. We use this to
	store the characters from a file. This class also does character validation to make
	sure that there are no invalid characters going into the Linked List.
*/

#include "charnode.hpp"

class CharacterList {
	private:
	
		/*
			To store the characters in this class, we are using a Singly Linked
			List data structure rather than an array of characters. These two
			pointers are the standard "head" and "tail" values to make a Singly
			Linked List.
		*/
		CharNodePtr head;
		CharNodePtr tail;
		
		/*
			This method will check if a character to be put into this class is a valid
			character or not. Used in the push method.
		*/
		bool isValidCharacter(CHARACTER value);
		
		/*
			init(): This is called when the constructor is created. Put all the initial
			code here.
		*/
		void init();
	public:
		/*
			An empty constructor. MUST call up init().
		*/
		CharacterList();
		
		/*
			isEmpty(): checks the Singly Linked List if it is empty. True if it is
			empty and false if is has at least one node in the data structure still.
		*/
		bool isEmpty();
		
		/*
			push(): pushes a CharNode into the CharacterList. It will return a false if
			there was an error or if it was an invalid character.
		*/
		bool push(CHARACTER charValue, int line, char* file);
		
		/*
			these peek functions show the values for the top node in the Singly Linked List.
			These do not remove the top node.
		*/
		CHARACTER peekValue();
		int peekLineNumber();
		char* peekFileName();
		
		/*
			pop(): removes the top node from the Singly Linked List.
		*/
		void pop();
};

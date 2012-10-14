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
	date updated: 12/10/2012
	author: Gareth Richardson
	description: This is the header file for the class CharacterList. This stores files
	into an allocated place in memory.
*/

/*
	defining the CHARACTER as a unsigned character (ASCII) for now. But this may change.
*/
#define CHARACTER unsigned char

/*
	The size of a mega byte in bytes. Use for the allocation of memory for the characters
	coming from the files that are going to be assembled.
*/
#define ONE_MEGABYTE (1024 * 1024)

class CharacterList {
	private:
	
		/*
			head is the beginning of the file data, tail is the end of it.
		*/
		CHARACTER* head;
		CHARACTER* tail;
		
		/*
			This method will check if a character to be put into this class is a valid
			character or not. Used in the push method. So, it will check for a New Line
			character, Tab character and all printable ascii characters.
		*/
		bool isValidCharacter(CHARACTER value);
		
		/*
			init(): This is called when the constructor is created. Put all the initial
			code here. So, our memory allocation also happens here.
		*/
		void init();
	public:
		/*
			An empty constructor. MUST call up init().
		*/
		CharacterList();
		
		/*
			The deconstructor empties the CharNodes in the list.
		*/
		~CharacterList();
		
		/*
			isEmpty(): checks the Singly Linked List if it is empty. True if it is
			empty and false if is has at least one node in the data structure still.
		*/
		bool isEmpty();
		
		/*
			push(): pushes a CharNode into the CharacterList. It will return a false if
			there was an error or if it was an invalid character.
		*/
		bool push(CHARACTER charValue);
		
		/*
			these peek functions show the values for the top node in the Singly Linked List.
			These do not remove the top node.
		*/
		CHARACTER peekValue();
		
		/*
			This gets the file name the character is in. If the project that is being assembled
			is going to have more than one file, this comes in handy.
		*/
		char* peekFileName();
		
		/*
			pop(): removes the top node from the Singly Linked List.
		*/
		void pop();
};

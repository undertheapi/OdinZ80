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
	date updated: 18/10/2012
	author: Gareth Richardson
	description: This is the header file for the class CharacterList. This stores a
	Singly Linked List of characters using the data structure CharNode. We use this to
	store the characters from a file. This class also does character validation to make
	sure that there are no invalid characters going into the Linked List.
*/

/*
	A pre-processor defining the maximum amount of characters that can be put into
	the memory. Adjust accordingly.
*/
#define MAX_SIZE 300

#define CHARACTER unsigned char

class CharacterList {
	private:
	
		/*
			This is the length of the current character list we are making.
		*/
		int length;
		
		/*
			The position we are in, will increment every time a character is
			added to it.
		*/
		int currentPosition;
		
		/*
			This is the file in memory
		*/
		char fileInMemory[MAX_SIZE];
		
		/*
			isValidCharacter(): This method will check if a character to be put into 
			this class is a valid character or not. Used in the push method. So, it 
			will check for a New Line character, Tab character and all printable ascii 
			characters.
			
			Precondition: Object has been initialised.
			
			Postcondition: method value = (character is a valid character to be put
			into the reserved memory).
		*/
		bool isValidCharacter(CHARACTER value);
		
		/*
			init(): This is called when the constructor is created. Put all the initial
			code here.
			
			Precondition: A CharacterList object has been declared and put into memory.
			
			Postcondition: The CharacterList object has been initalised.
		*/
		void init();
	public:
		/*
			An empty constructor. MUST call up init().
		*/
		CharacterList();
		
		/*
			The deconstructor empties the CharNodes in the list.
			
			Precondition: A CharacterList object is going to be deleted from
			memory.
			A CharacterList has been initalised.
			
			Postcondition: The resvered memory for the file has all been replaced with
			all 0x00 values.
		*/
		~CharacterList();
		
		/*
			isEmpty(): checks the Singly Linked List if it is empty. True if it is
			empty and false if is has at least one node in the data structure still.
			
			Preconditions: A CharacterList object has been initalised.
			
			Postconditions: Function value = (list is empty).
		*/
		bool isEmpty();
		
		/*
			isFull(): Because we are dealing with a finite memory space, we do not 
			want to go over the designated reserved memory. This method allows us 
			to check for this.
			
			preconditions: A CharacterList object has been initalised.
			
			postconditions: Function value = (list is full).
		*/
		bool isFull();
		
		/*
			push(): pushes a CharNode into the CharacterList. It will return a false if
			there was an error or if it was an invalid character.
			
			preconditions: A CharacterList object has been initalised.
			The CharacterList reserved memory is not full.
			
			postconditions: A character (byte) has been put into memory if it was a valid
			value.
			The length and currentPosition values change.
			Function value = (character added to list).
		*/
		bool push(CHARACTER charValue);
		
		/*
			peekValue(): The character that the current position is returned.
			
			preconditions: The length of the list cannot be zero / empty memory.
			The CharacterList object has been initalised.
			
			postconditions: Function value = (was the list not empty, did a value come back).
			charValue has the value of the character at currentPosition - 1.
		*/
		bool peekValue(CHARACTER &charValue);
		
		/*
			pop(): removes the character currentPosition - 1 is pointing to.
			
			preconditions: CharacterList object has been initalised.
			memory list cannot be empty.
			
			postconditions: length and currentPosition changed.
			currentPosition - 1 is changed to 0.
			Function value = (was list altered).
		*/
		bool pop();
};

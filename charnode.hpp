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
	file name: charnode.hpp
	date created: 27/08/2012
	date updated: 27/08/2012
	author: Gareth Richardson
	description: This is the data structure for the CharNode struct. Use this with the
	CharacterList class to store characters from a file in a Singly Linked List. The
	data type of the characters stored here can alter depending on the situation. So if
	we choose to do it in ASCII or Unicode character sets, it will not matter.
*/

/*
	defining the CHARACTER as a unsigned character (ASCII) for now. But this may change.
*/
#define CHARACTER unsigned char

/*
	CHARACTER value: This is the value of the character.
	unsigned int lineNumber: This is the line number that the character is on in the file.
	char* fileName: A pointer to the file name in cstring format in memory.
	CharNode* next: The typical Singly Linked List next value. Points to the next CharaNode
	structure in memory.
*/
struct CharNode {
	CHARACTER value;
	unsigned int lineNumber;
	char* fileName;
	CharNode* next;
};

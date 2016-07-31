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
	file name: foundlist.hpp
	date created: 14/02/2013
	date updated: 04/03/2016
	author: Gareth Richardson
	description: All the found addresses are in this list.
*/

#include "addressnode.hpp"

class FoundList {
	private:
	/*
			Structure of the singly linked list here:
		*/
		AddressNode* head;
		AddressNode* tail;
		
		/*
			Size of the list, increments by one everytime an
			element is added.
		*/
		int size;
		
		/*
			Initial code is put into this function. It is used within
			the constructor.
		*/
		void init();
		
		/*
			Get a node from a specified index.
		*/
		AddressNode* getNode(int);
	public:
		FoundList();
		
		/*
			When the FoundList object is empty, this returns a true.
		*/
		bool isEmpty();
		
		/*
			Gets the size of the FoundList, use when wanting to know the exact
			size of the FoundList object elements.
		*/
		int getSize();
		
		/*
			Adds a new address to the end of the linked list. New element becomes
			the new tail node in the linked list.
		*/
		void addAddress(string name, unsigned short addr);
		
		/*
			Gets the name of the address at a specified index in the list
		*/
		string getName(int index);
		
		/*
			Gets the short (16 bit) value of the address at a specified index in the list
		*/
		unsigned short getAddress(int index);
		
		bool doesNameExist(string value);
};


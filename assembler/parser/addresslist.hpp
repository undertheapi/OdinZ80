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
	file name: addresslist.hpp
	date created: 14/02/2013
	date updated: 06/03/2013
	author: Gareth Richardson
	description: This is a list of addresses not found yet.
*/

#include "addressnode.hpp"

class AddressList {
	private:
		/*
			Node pointing to the beginning of the linked list. Does not
			need the typical tail node.
		*/
		AddressNode* head;
		
		/*
			The size of the AddressList linked list. increments by one
			everytime a node is added to the linked list.
		*/
		int size;
		
		/*
			Gets the address name at the specified index. Make sure the
			index value is within range as there is no error checking in
			this method.
		*/
		string getElement(int index);
		
		/*
			Get the address specified by the index in the linked list.
			No error checking so make sure the index value is within
			range.
		*/
		unsigned short getAddress(int index);
		
		/*
			Deletes an element from the linked list. Make sure the index
			is with range as there is no error checking.
		*/
		void deleteElement(int index);
		
		/*
			The initiation method, called up in the constructor. Put all
			the initail code in here.
		*/
		void init();
	public:
		AddressList();
		
		/*
			Returns true if the AddressList is empty.
		*/
		bool isEmpty();
		
		/*
			Adds an address to the beginning of the list, does not matter
			were you input the address, so the new address becomes the head
			of the linked list.
		*/
		void addAddress(string value, unsigned short addr);
		
		/*
			just in case we have an address not found, we can know
			what it is.
		*/
		string getLastName();
		
		/*
			Give me the name, address and the byte code and I will populate the
			empty addresses.
		*/
		void processAddress(string name, unsigned short newAddress, ByteCode* bCode);
};


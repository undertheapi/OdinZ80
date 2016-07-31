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
	file name: RAM.cpp
	date created: 22/02/2012
	date updated: 11/09/2015
	author: Gareth Richardson
	description: The object file for the RAM class.
*/

#include <string>

using namespace std;

#include "../general/convert.hpp"

#include "RAM.hpp"

/*
	In this constructor we are going to be clearing the data
	and assuming it will be filled with 0x00. In the real world
	this would not occur.
*/
RAM::RAM() {
	for (int pointer = 0; pointer <= MAX_ADDRESS; ++pointer)
		RAM::write(pointer, 0);
}

unsigned char RAM::read(unsigned short address) {
	return RAM::memory[address];
}

void RAM::write(unsigned short address, unsigned char value) {
	RAM::memory[address] = value;
}

string RAM::memoryFeed(unsigned short start, unsigned short count, FEED_TYPE type) {
	string feedString = "";
	if (type == HEX_FEED) {
		unsigned short index = start;
		while (index != start + count - 1) {
			feedString += convertHex(index);
			feedString += " :: ";
			feedString += convertHex(RAM::memory[index]);
			feedString += "\n";
		}
	} else if (type == BIN_FEED) {

	} else if (type == DEC_FEED) {

	} else if (type == OCT_FEED) {

	} else {
		//get into an error state.
		//Try not to get to this situation.
		feedString = "ERROR";
	}
	return feedString;
}

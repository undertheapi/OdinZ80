/*
	Copyright (c) 2013, Gareth Richardson
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
	file name: RAM.hpp
	date created: 22/02/2012
	date updated: 29/05/2014
	author: Gareth Richardson
	description: This this the header file for the RAM object. Use this with
	the debugger. Can also be used for other CPU simulators and emulators that
	run on a 16-bit addressing system.
	Might change this to a none object though.
*/

#define MAX_ADDRESS 0xffff

#define FEED_TYPE unsigned char
#define HEX_FEED 0
#define BIN_FEED 2
#define DEC_FEED 3
#define OCT_FEED 4

class RAM {
	private:
		unsigned char memory[MAX_ADDRESS];
	public:
		RAM();
		unsigned char read(unsigned short address);
		void write(unsigned short address, unsigned char value);
		string memoryFeed(unsigned short start, FEED_TYPE type);
};


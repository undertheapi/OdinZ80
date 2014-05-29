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
	file name: registers.hpp
	date created: 21/10/2013
	date updated: 29/05/2014
	author: Gareth Richardson
	description: The header file for the registers object
*/

/*
	8 BIT register definitions:
*/
#define REGISTER8 unsigned char
#define REG_A 6
#define REG_B 0
#define REG_C 1
#define REG_D 2
#define REG_E 3
#define REG_F 7
#define REG_H 4
#define REG_L 5

/*
	16 BIT register definitions:
*/
#define REGISTER16 unsigned char
#define REG_BC 0
#define REG_DE 1
#define REG_HL 2
#define REG_SP 3

class Registers {
	private:
		/*
			The register array works like this:
			
			B	C	D	E	H	L	A	F
			0	1	2	3	4	5	6	7
			
			So, BC is made from [0] and [1], DE from [2] and [3],
			HL from [4] and [5] and AF from [6] and [7].
			
			Should the flag be in here as well?
		*/
		unsigned char[8] registerArray;
		unsigned short IP;
		unsigned short IX;
		unsigned short IY;
		
		void init();
	public:
		/*
			Methods dealing with register IP:
		*/
		unsigned short getIP();
		void incrementIP();
		void decrementIP();
		
		/*
			Methods dealing with the Extended Registers:
		*/
		unsigned short getIX();
		unsigned short getIY();
		
		void load8Bit(REGISTER8 reg1, REGISTER8 reg2);
		void load8BitImm(REGISTER8 reg, unsigned char value);
		
		Registers();
		
		/*
			THis returns a string displaying the current state of the registers.
		*/
		string currentStateString();
};
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
	file name: parser.hpp
	date created: 28/09/2012
	date updated: 21/02/13
	author: Gareth Richardson
	description: This is the Z80 parser. Give it a TokenList object and it will
	parse it and output the machine code for it.
*/

class Z80Parser {
	private:
		/*
			Were the tokens are stored.
		*/
		TokenList* tList;

		/*
			Were the bytes compiled will go.
		*/
		ByteCode* bCode;

		/*
			this keeps track of errors.
		*/
		bool errorState;

		/*
			errors from the parser make an error string.
		*/
		string errorString;

		/*
			Keeps track of the address in the program.
		*/
		int address;
		
		AddressList aList;
		FoundList fList;

		/*
			Put this into the constructor.
		*/
		void init();


		bool checkToken(TOKEN_TYPE tok);
		bool checkEightBitNumber(unsigned char &number);
		bool checkSixteenBitNumber(unsigned short &number);
		bool checkStringToken(string &value);
		bool checkAtom(string &value);
		
		void addCode(unsigned char);
		void addCode(unsigned char, unsigned char);
		void addCode(unsigned char, unsigned char, unsigned char);
		
		/*
			Adds an Address to the Address List. The string parameter is the name
			and the actual value comes from the current address attribute in the
			Z80Parser class.
		*/
		void addAddress(string atom);
		void error(string value);
		
		/*
			Makes sure that there is a new line, comes in handy for checking
			if a new line exists.
		*/
		void newLine();
		
		void processLD();
		void processPUSH();
		void processPOP();
		void processEX();
		void processADD();
		void processADC();
		void processSUB();
		void processSUBC();
		void processAND();
		void processOR();
		void processXOR();
		void processCP();
		void processINC();
		void processDEC();
		void processRLC();
		void processRL();
		void processRRC();
		void processRR();
		void processSLA();
		void processSRA();
		void processSRL();
		void processBIT();
		void processSET();
		void processRES();
		void processJP();
		void processJR();
		void processCALL();
		void processRET();
		void processRST();
		void processIN();
		void processOUT();

	public:
		Z80Parser(TokenList* tPointer, ByteCode* bPointer);
		void run();
		bool checkState();
		string getError();
};

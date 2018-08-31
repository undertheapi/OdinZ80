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
	file name: symbol_table.hpp
	date created: 31/08/2018
	date updated: 31/08/2018
	author: Gareth Richardson
	description: This is the Symbol Table Class Header for the Odin assembler.
*/

#include "symbol_node.hpp"

class SYMBOL_TABLE {
	private:
		SYMBOL_NODE* tableHead;
		SYMBOL_NODE* tableTail;
		
		int indexCount;
	
		int checkSymbol(string*);
		
	public:
		SYMBOL_TABLE();
		
		void init();
		
		/*
			Adds a symbol to the table. When it is added, it returns the index of
			where it is in the list.
		*/
		int addSymbol(string*);
		
		/*
			Adds a symbol AND its mapped integer value to the symbol table.
		*/
		int addSymbol(string*, int);
		
		/*
			gets the value from the index. Returns a -1 if it is empty OR out of index.
		*/
		int getValue(int);
		
		/*
			Sets the value of the symbol based on the index. 
			Returns a false if the index was out of bounds. 
		*/
		bool setSymbolValue(int, int);
};

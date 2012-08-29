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
	file name: lex.hpp
	date created: 29/08/2012
	date updated: 29/08/2012
	author: Gareth Richardson
	description: This is the Lexical Analysis for the Odin assembler.
*/

#include "lex.hpp"

TokenNode Lex::getToken() {
	/*
		this is getting rid of the space characters from the CharacterList class.
	*/
	while (!Lex::cList->isEmpty() && Lex::cList->peekValue() == '\t' && Lex::peekValue() == ' ') {
		Lex::cList->pop();
	}
	
	if (Lex::isEmpty()) {
		//send end of file state back.
	}
	
	/*
		This is the string that collects the token value.
	*/
	string retValue = "";
	
	if (Lex::cList->peekValue() >= 'a' && Lex::cList->peekValue <= 'z' || Lex::cList->peekValue() >= 'A' && Lex::cList->peekValue() <= 'Z') {
		while (Lex::cList->peekValue() >= 'a' && Lex::cList->peekValue() <= 'z' || Lex::cList->peekValue() >= 'A' && Lex::cList->peekValue() <= 'Z') {
			retValue += Lex::cList->peekValue();
			Lex::cList->pop();
		}
		/*
			**here have some sort of token type checking to check for keywords.
		*/
	}
}

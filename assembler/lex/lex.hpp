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
	file name: lex.hpp
	date created: 29/08/2012
	date updated: 23/10/2014
	author: Gareth Richardson
	description: This is the Lexical Analysis for the Odin assembler.
*/

class Lex {
	private:
		/*
			This is a pointer to the CharacterList that will be used for storing the
			character strewam from the file.
		*/
		CharacterList* cList;

		/*
			Were the Tokens are going to be stored. This is just a pointer to a
			TokenList.
		*/
		TokenList* tList;

		/*
			The value of the error string. Set if there is an error, otherwise it is not
			set. (Default is "").
		*/
		string errorString;

		/*
			When the Lex obj comes along an error, we set this to true. Otherwise it is false.
		*/
		bool errorState;

		/*
			A counter for the line number in the file.
		*/
		int lineNumber;

		/*
			Gets a number if we want one from the file. Error state ill be set if there
			are any problems.
		*/
		string getNumber();
		
		/*
			This is for checking a string is a keyword:
		*/
		bool checkKeyword(string value, string checker);

		/*
			Gets a unique token from the CharacterList object being pointed to. Sets errorString and errorState
			if there is an error. Called up in run().
		*/
		TokenNodePtr getToken();
		
	public:
		Lex(CharacterList* cList, TokenList* tList);

		/*
			Runs the Lex object and populates the TokenList obj that is being pointed to.
		*/
		void run();

		/*
			This checks errorState and returns its value.
		*/
		bool checkForError();

		/*
			Gets the errorString. Remember, if it is not set, it will return "".
		*/
		string getError();
};

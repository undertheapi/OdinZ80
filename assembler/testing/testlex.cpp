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
	file name: testlex.cpp
	date created: 4/10/2012
	date updated: 4/10/2012
	author: Gareth Richardson
	description: This is the unit test for the Lex class.
*/

#include <assert.h>
#include <stdio.h>
#include <string>

using namespace std;

#include "../character/characterlist.hpp"
#include "../lex/tokenlist.hpp"
#include "../lex/lex.hpp"

void testADC() {
	printf("**Testing ADC tokens in the Lexical Analyser.\n");
	CharacterList cList;
	char array[] = "ADC Adc adc ";
	
	int index = 0;
	while (array[index] != 0) {
		cList.push(array[index]);
		index++;
	}
	
	assert(cList.isEmpty() == false);
	
	cList.finishedFile();
	
	TokenList tList;
	
	Lex lexObj(&cList, &tList);
	
	lexObj.run();
	
	assert(lexObj.checkForError() == false);
	printf("No error has come from the Lexical Analyser.\n");
	
	assert(tList.peekTokenType() == ADC);
	printf("\tFirst token is ADC.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == ADC);
	printf("\tSecond token is ADC.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == ADC);
	printf("\tThird token is ADC.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == END_OF_FILE);
	printf("\tThird token is END_OF_FILE.\n");
	tList.pop();
	
	assert(tList.isEmpty() == true);
	printf("The TokenList object is now empty.\n");
}

void testADD() {
	printf("**Testing ADD tokens in the Lexical Analyser.\n");
	CharacterList cList;
	char array[] = "ADD              Add add    ";
	
	int index = 0;
	while (array[index] != 0) {
		cList.push(array[index]);
		index++;
	}
	
	cList.finishedFile();
	
	TokenList tList;
	
	Lex lexObj(&cList, &tList);
	
	lexObj.run();
	
	assert(lexObj.checkForError() == false);
	printf("No error has come from the Lexical Analyser.\n");
	
	assert(tList.peekTokenType() == ADD);
	printf("\tFirst token is ADD.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == ADD);
	printf("\tSecond token is ADD.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == ADD);
	printf("\tThird token is ADD.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == END_OF_FILE);
	printf("\tThird token is END_OF_FILE.\n");
	tList.pop();
	
	assert(tList.isEmpty() == true);
	printf("The TokenList object is now empty.\n");
}

void testAND() {
	printf("**Testing AND tokens in the Lexical Analyser.\n");
	CharacterList cList;
	char array[] = "   AND             And and    ";
	
	int index = 0;
	while (array[index] != 0) {
		cList.push(array[index]);
		index++;
	}
	
	cList.finishedFile();
	
	TokenList tList;
	
	Lex lexObj(&cList, &tList);
	
	lexObj.run();
	
	assert(lexObj.checkForError() == false);
	printf("No error has come from the Lexical Analyser.\n");
	
	assert(tList.peekTokenType() == AND);
	printf("\tFirst token is AND.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == AND);
	printf("\tSecond token is AND.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == AND);
	printf("\tThird token is AND.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == END_OF_FILE);
	printf("\tThird token is END_OF_FILE.\n");
	tList.pop();
	
	
	assert(tList.isEmpty() == true);
	printf("The TokenList object is now empty.\n");
}

void testBIT() {
	printf("**Testing BIT tokens in the lexical analyser.\n");
	CharacterList cList;
	char array[] = "BIT Bit bit \t\t\t\t\t     BT bt Bt   \t\t\t\t";
	
	int index = 0;
	while (array[index] != 0) {
		cList.push(array[index]);
		index++;
	}
	
	cList.finishedFile();
	
	TokenList tList;
	
	Lex lexObj(&cList, &tList);
	
	lexObj.run();
	
	assert(lexObj.checkForError() == false);
	printf("No error has come from the Lexical Analyser.\n");
	
	assert(tList.peekTokenType() == BIT);
	printf("\tFirst token is BIT.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == BIT);
	printf("\tSecond token is BIT.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == BIT);
	printf("\tThird token is BIT.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == BIT);
	printf("\tFourth token is BIT.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == BIT);
	printf("\tFifth token is BIT.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == BIT);
	printf("\tSixth token is BIT.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == END_OF_FILE);
	printf("\tThird token is END_OF_FILE.\n");
	tList.pop();
	
	
	assert(tList.isEmpty() == true);
	printf("The TokenList object is now empty.\n");
}

void testCALL() {
	printf("**Testing CALL tokens in the lexical analyser.\n");
	CharacterList cList;
	char array[] = "CALL \t\t\tcall Call \t\t\t\t\t     \t\t\t\t";
	
	int index = 0;
	while (array[index] != 0) {
		cList.push(array[index]);
		index++;
	}
	
	cList.finishedFile();
	
	TokenList tList;
	
	Lex lexObj(&cList, &tList);
	
	lexObj.run();
	
	assert(lexObj.checkForError() == false);
	printf("No error has come from the Lexical Analyser.\n");
	
	assert(tList.peekTokenType() == CALL);
	printf("\tFirst token is CALL.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == CALL);
	printf("\tSecond token is CALL.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == CALL);
	printf("\tThird token is CALL.\n");
	tList.pop();
	
	assert(tList.peekTokenType() == END_OF_FILE);
	printf("\tThird token is END_OF_FILE.\n");
	tList.pop();
	
	
	assert(tList.isEmpty() == true);
	printf("The TokenList object is now empty.\n");
}

void testNumbers() {
	printf("**Testing numbers.\n");
	CharacterList cList;
	char array[] = "743   903 0x34f easd 0d43333 0b101011111111 \t\t\t\t 0x433";
	
	int index = 0;
	while (array[index] != 0) {
		cList.push(array[index]);
		index++;
	}
	
	cList.finishedFile();
	
	TokenList tList;
	
	Lex lexObj(&cList, &tList);
	
	lexObj.run();
	
	assert(lexObj.checkForError() == false);
	printf("No error has come from the Lexical Analyser.\n");
	
	assert(tList.peekTokenType() == NUMBER);
	assert(tList.peekValue().compare("d743") == 0);
	printf("Value at position 1 is d743\n");
	tList.pop();
	
	assert(tList.peekTokenType() == NUMBER);
	assert(tList.peekValue().compare("d903") == 0);
	printf("Value at position 2 is d903\n");
	tList.pop();
	
	assert(tList.peekTokenType() == NUMBER);
	assert(tList.peekValue().compare("h34f") == 0);
	printf("Value at position 3 is h34f\n");
	tList.pop();
	
	assert(tList.peekTokenType() == ATOM);
	assert(tList.peekValue().compare("easd") == 0);
	printf("Value at position 4 is easd\n");
	tList.pop();
	
	assert(tList.peekTokenType() == NUMBER);
	assert(tList.peekValue().compare("d43333") == 0);
	printf("Value at position 5 is d43333\n");
	tList.pop();
	
	assert(tList.peekTokenType() == NUMBER);
	assert(tList.peekValue().compare("b101011111111") == 0);
	printf("Value at position 6 is b101011111111\n");
	tList.pop();
	
	assert(tList.peekTokenType() == NUMBER);
	assert(tList.peekValue().compare("h433") == 0);
	printf("Value at position 7 is h433\n");
	tList.pop();
	
	assert(tList.peekTokenType() == END_OF_FILE);
	printf("Value at position 8 is END_OF_FILE\n");
	tList.pop();
}

int main() {
	testADC();
	testADD();
	testAND();
	testBIT();
	testCALL();
	testNumbers();
	return 0;
}

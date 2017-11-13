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
	file name: testcharacterlist.cpp
	date created: 18/10/2012
	date updated: 18/10/2012
	author: Gareth Richardson
	description: The unit test for the CharacterList class.
*/

#include <assert.h>
#include <stdio.h>

#include "../character/characterlist.hpp"

using namespace std;

/*
	Input is all the valid characters that CharacterList can handle and is allowed to handle.
*/
void testValidCharacters() {
	printf("**Test Valid Characters in the CharacterList class.\n");
	CharacterList cList;
	assert(cList.push('\t') == true);
	printf("1: A CharacterList object can handle a Horizontal Tab character \'\\t\'\n");
	assert(cList.push('\n') == true);
	printf("2: A CharacterList object can handle a New Line character \'\\n\'\n");
	int counter = 3;
	CHARACTER charValue = ' ';
	while (charValue != 127) {
		assert(cList.push(charValue) == true);
		printf("%i: A CharacterList object can handle a \'%c\' character\n", counter, charValue);
		counter++;
		charValue++;
	}
}

/*
	Input is all the invalid characters that CharacterList can not handle.
*/
void testInvalidCharacters() {
	printf("**Testing invalid Characters in the CharacterList class.\nNOTE: This part validates the ASCII control characters.\n");
	CharacterList cList;
	assert(cList.push(0) == false);
	printf("1: A CharacterList can handle a NULL character.\n");
	assert(cList.push(1) == false);
	printf("2: A CharacterList can handle a SOH (Start Of Header) character.\n");
	assert(cList.push(2) == false);
	printf("3: A CharacterList can handle a STX (Start of TeXt) character.\n");
	assert(cList.push(3) == false);
	printf("4: A CharacterList can handle an ETX (End of TeXt) character.\n");
	assert(cList.push(4) == false);
	printf("5: A CharacterList can handle an EOT (End Of Transmission) character.\n");
	assert(cList.push(5) == false);
	printf("6: A CharacterList can handle an ENQ (Enquiry) character.\n");
	assert(cList.push(6) == false);
	printf("7: A CharacterList can handle an ACK (Acknowledge) character.\n");
	assert(cList.push(7) == false);
	printf("8: A CharacterList can handle a BELL character.\n");
	assert(cList.push(8) == false);
	printf("9: A CharacterList can handle a Backspace character.\n");
	assert(cList.push(11) == false);
	printf("10: A CharacterList can handle a Vertical Tab character.\n");
	assert(cList.push(12) == false);
	printf("11: A CharacterList can handle a Form Feed (New Page) character.\n");
	assert(cList.push(13) == false);
	printf("12: A CharacterList can handle the Carriage Return character.\n");
	assert(cList.push(14) == false);
	printf("13: A CharacterList can handle the Shift Out character.\n");
	assert(cList.push(15) == false);
	printf("14: A CharacterList can handle the Shift In character.\n");
	assert(cList.push(16) == false);
	printf("15: A CharacterList can handle the DLE (Data Line Escape) character.\n");
	assert(cList.push(17) == false);
	printf("16: A CharacterList can handle the Device Control One character.\n");
	assert(cList.push(18) == false);
	printf("17: A CharacterList can handle the Device Control Two character.\n");
	assert(cList.push(19) == false);
	printf("16: A CharacterList can handle the Device Control Three character.\n");
	assert(cList.push(20) == false);
	printf("17: A CharacterList can handle the Device Control Four character.\n");
	assert(cList.push(21) == false);
	printf("18: A CharacterList can handle the NK (Negative Acknowledge) character.\n");
	assert(cList.push(22) == false);
	printf("19: A CharacterList can handle the SYN (SYNchronous idle) character.\n");
	assert(cList.push(23) == false);
	printf("20: A CharacterList can handle the ETB (End of Transmission Block) character.\n");
	assert(cList.push(24) == false);
	printf("21: A CharacterList can handle the Cancel character.\n");
	assert(cList.push(25) == false);
	printf("22: A CharacterList can handle the EM (End of Medium) character.\n");
	assert(cList.push(26) == false);
	printf("23: A CharacterList can handle the Substitution character.\n");
	assert(cList.push(27) == false);
	printf("24: A CharacterList can handle the Escape character.\n");
	assert(cList.push(28) == false);
	printf("25: A CharacterList can handle the FS (File Separator) character.\n");
	assert(cList.push(29) == false);
	printf("26: A CharacterList can handle the GS (Group Separator) character.\n");
	assert(cList.push(30) == false);
	printf("27: A CharacterList can handle the RS (Record Separator) character.\n");
	assert(cList.push(31) == false);
	printf("28: A CharacterList can handle the US (Unit Separator) character.\n");
	assert(cList.push(127) == false);
	printf("29: A CharacterList can handle the Delete character.\n");

	int counter = 30;
	CHARACTER charValue = 128;
	printf("NOTE: The next characters are part of the Extended ASCII characters.\n");
	while (charValue != 255) {
		assert(cList.push(charValue) == false);
		printf("%i: A CharacterList object can handle a \'%c\' character.\n", counter, charValue);
		counter++;
		charValue++;
	}
}

void testAllCharacters() {
	printf("**Testing ALL input characters, both valid and invalid.\n");
	CharacterList cList;
	int counter = 1;
	CHARACTER charValue = 0;

	while (charValue != 9) {
		assert(cList.push(charValue) == false);
		printf("%i: A CharacterList can handle the \'%c\' character.\n", counter, charValue);
		counter++;
		charValue++;
	}

	assert(cList.push(charValue) == true);
	printf("%i: A CharacterList can handle the TAB character.\n", counter);
	counter++;
	charValue++;

	assert(cList.push(charValue) == true);
	printf("%i: A CharacterList can handle the NEW LINE character.\n", counter);
	counter++;
	charValue++;

	while (charValue != 32) {
		assert(cList.push(charValue) == false);
		printf("%i: A CharacterList can handle the \'%c\' character.\n", counter, charValue);
		counter++;
		charValue++;
	}

	while (charValue != 127) {
		assert(cList.push(charValue) == true);
		printf("%i: A CharacterList can handle the \'%c\' character.\n", counter, charValue);
		counter++;
		charValue++;
	}

	while (charValue != 255) {
		assert(cList.push(charValue) == false);
		printf("%i: A CharacterList can handle the \'%c\' character.\n", counter, charValue);
		counter++;
		charValue++;
	}

	assert(cList.push(charValue) == false);
	printf("%i: A CharacterList can handle the \'%c\' character.\n", counter, charValue);
}

void testEmpty() {
	printf("**Testing an empty CharacterList object.\n");
	CharacterList cList;
	assert(cList.isEmpty() == true);
	printf("\tcList is empty.\n");
	cList.push('a');
	assert(cList.isEmpty() == false);
	printf("\tcList is not empty after \'a\' is pushed.\n");
	cList.push('b');
	assert(cList.isEmpty() == false);
	printf("\tcList is not empty after \'b\' is pushed.\n");
	assert(cList.pop() == true);
	assert(cList.isEmpty() == false);
	printf("\tcList is not empty after \'a\' is popped.\n");
	assert(cList.pop() == true);
	assert(cList.isEmpty() == true);
	printf("\tcList is empty after \'b\' is popped.\n");
}

void testListPositions() {
	printf("**Testing a CharacterList object if the characters are in the correct position.\n");
	CharacterList cList;
	assert(cList.push('a') == true);
	printf("Managed to push \'a\' onto the list.\n");
	assert(cList.push('b') == true);
	printf("Managed to push \'b\' onto the list.\n");
	assert(cList.push('\0') == false);
	printf("Did not manage to push \'null\' onto the list.\n");
	assert(cList.push('c') == true);
	printf("Managed to push \'c\' onto the list.\n");
	cList.finishedFile();
	//CHARACTER value = 0;
	assert(cList.peekValue() == 'a');
	//assert(value == 'a');
	assert(cList.pop() == true);
	assert(cList.peekValue() == 'b');
	//assert(value == 'b');
	assert(cList.pop() == true);
	assert(cList.peekValue() == 'c');
	//assert(value == 'c');
	assert(cList.pop() == true);
	assert(cList.pop() == false);
	assert(cList.pop() == false);

	assert(cList.push('f') == true);
	assert(cList.push('g') == true);
	assert(cList.push('h') == true);
	assert(cList.push('i') == true);

	cList.finishedFile();

	assert(cList.peekValue() == 'f');
	printf("Got an \'f\' from the list.\n");
	assert(cList.pop() == true);
	assert(cList.peekValue() == 'g');
	printf("Got an \'g\' from the list.\n");
	assert(cList.pop() == true);
}

void checkErrorStates() {
	printf("**Testing the errorState byte, checking if it works properly.\n");

	CharacterList cList;

	assert(cList.pop() == false);
	printf("\tPopping an empty list works.\n");

	assert(cList.errorState == LIST_EMPTY);
	printf("\tError state is correct, brought back LIST_EMPTY.\n");

	assert(cList.push(0x01) == false);
	printf("\tPushing an invalid character into list passes, does not put onto list.\n");

	assert(cList.errorState == LIST_EMPTY | INVALID_CHAR);
	printf("\tError state is correct. LIST_EMPTY and INVALID_CHAR are both set.\n");

	int counter = 1;


	while (counter != 20000000) {
		cList.push('a');
		counter++;
	}

	assert(cList.errorState == LIST_EMPTY | INVALID_CHAR | LIST_FULL);
	printf("\tError state is correct. LIST_EMPTY, INVALID_CAHR and LIST_FULL are all set.\n");

	
}

int main() {
	testValidCharacters();
	testInvalidCharacters();
	testAllCharacters();
	testEmpty();
	testListPositions();
	checkErrorStates();
	return 0;
}

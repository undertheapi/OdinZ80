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
	date craeted: 4/10/2012
	date updated: 4/10/2012
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
	assert(cList.push('\t', 0, 0) == true);
	printf("1: A CharacterList object can handle a Horizontal Tab character \'\\t\'\n");
	assert(cList.push('\n', 0, 0) == true);
	printf("2: A CharacterList object can handle a New Line character \'\\n\'\n");
	int counter = 3;
	CHARACTER charValue = ' ';
	while (charValue != 127) {
		assert(cList.push(charValue, 0, 0) == true);
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
	assert(cList.push(0, 0, 0) == false);
	printf("1: A CharacterList can handle a NULL character.\n");
	assert(cList.push(1, 0, 0) == false);
	printf("2: A CharacterList can handle a SOH (Start Of Header) character.\n");
	assert(cList.push(2, 0, 0) == false);
	printf("3: A CharacterList can handle a STX (Start of TeXt) character.\n");
	assert(cList.push(3, 0, 0) == false);
	printf("4: A CharacterList can handle an ETX (End of TeXt) character.\n");
	assert(cList.push(4, 0, 0) == false);
	printf("5: A CharacterList can handle an EOT (End Of Transmission) character.\n");
	assert(cList.push(5, 0, 0) == false);
	printf("6: A CharacterList can handle an ENQ (Enquiry) character.\n");
	assert(cList.push(6, 0, 0) == false);
	printf("7: A CharacterList can handle an ACK (Acknowledge) character.\n");
	assert(cList.push(7, 0, 0) == false);
	printf("8: A CharacterList can handle a BELL character.\n");
	assert(cList.push(8, 0, 0) == false);
	printf("9: A CharacterList can handle a Backspace character.\n");
	assert(cList.push(11, 0, 0) == false);
	printf("10: A CharacterList can handle a Vertical Tab character.\n");
	assert(cList.push(12, 0, 0) == false);
	printf("11: A CharacterList can handle a Form Feed (New Page) character.\n");
	assert(cList.push(13, 0, 0) == false);
	printf("12: A CharacterList can handle the Carriage Return character.\n");
	assert(cList.push(14, 0, 0) == false);
	printf("13: A CharacterList can handle the Shift Out character.\n");
	assert(cList.push(15, 0, 0) == false);
	printf("14: A CharacterList can handle the Shift In character.\n");
	assert(cList.push(16, 0, 0) == false);
	printf("15: A CharacterList can handle the DLE (Data Line Escape) character.\n");
	assert(cList.push(17, 0, 0) == false);
	printf("16: A CharacterList can handle the Device Control One character.\n");
	assert(cList.push(18, 0, 0) == false);
	printf("17: A CharacterList can handle the Device Control Two character.\n");
	assert(cList.push(19, 0, 0) == false);
	printf("16: A CharacterList can handle the Device Control Three character.\n");
	assert(cList.push(20, 0, 0) == false);
	printf("17: A CharacterList can handle the Device Control Four character.\n");
	assert(cList.push(21, 0, 0) == false);
	printf("18: A CharacterList can handle the NK (Negative Acknowledge) character.\n");
	assert(cList.push(22, 0, 0) == false);
	printf("19: A CharacterList can handle the SYN (SYNchronous idle) character.\n");
	assert(cList.push(23, 0, 0) == false);
	printf("20: A CharacterList can handle the ETB (End of Transmission Block) character.\n");
	assert(cList.push(24, 0, 0) == false);
	printf("21: A CharacterList can handle the Cancel character.\n");
	assert(cList.push(25, 0, 0) == false);
	printf("22: A CharacterList can handle the EM (End of Medium) character.\n");
	assert(cList.push(26, 0, 0) == false);
	printf("23: A CharacterList can handle the Substitution character.\n");
	assert(cList.push(27, 0, 0) == false);
	printf("24: A CharacterList can handle the Escape character.\n");
	assert(cList.push(28, 0, 0) == false);
	printf("25: A CharacterList can handle the FS (File Separator) character.\n");
	assert(cList.push(29, 0, 0) == false);
	printf("26: A CharacterList can handle the GS (Group Separator) character.\n");
	assert(cList.push(30, 0, 0) == false);
	printf("27: A CharacterList can handle the RS (Record Separator) character.\n");
	assert(cList.push(31, 0, 0) == false);
	printf("28: A CharacterList can handle the US (Unit Separator) character.\n");
	assert(cList.push(127, 0, 0) == false);
	printf("29: A CharacterList can handle the Delete character.\n");
	
	int counter = 30;
	CHARACTER charValue = 128;
	printf("NOTE: The next characters are part of the Extended ASCII characters.\n");
	while (charValue != 255) {
		assert(cList.push(charValue, 0, 0) == false);
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
		assert(cList.push(charValue, 0, 0) == false);
		printf("%i: A CharacterList can handle the \'%c\' character.\n", counter, charValue);
		counter++;
		charValue++;
	}
	
	assert(cList.push(charValue, 0, 0) == true);
	printf("%i: A CharacterList can handle the TAB character.\n", counter);
	counter++;
	charValue++;
	
	assert(cList.push(charValue, 0, 0) == true);
	printf("%i: A CharacterList can handle the NEW LINE character.\n", counter);
	counter++;
	charValue++;
	
	while (charValue != 32) {
		assert(cList.push(charValue, 0, 0) == false);
		printf("%i: A CharacterList can handle the \'%c\' character.\n", counter, charValue);
		counter++;
		charValue++;
	}
	
	while (charValue != 127) {
		assert(cList.push(charValue, 0, 0) == true);
		printf("%i: A CharacterList can handle the \'%c\' character.\n", counter, charValue);
		counter++;
		charValue++;
	}
	
	while (charValue != 255) {
		assert(cList.push(charValue, 0, 0) == false);
		printf("%i: A CharacterList can handle the \'%c\' character.\n", counter, charValue);
		counter++;
		charValue++;
	}
	
	assert(cList.push(charValue, 0, 0) == false);
	printf("%i: A CharacterList can handle the \'%c\' character.\n", counter, charValue);
}

void testEmpty() {
	printf("**Testing an empty CharacterList object.\n");
	CharacterList cList;
	assert(cList.isEmpty() == true);
	printf("\tcList is empty.\n");
	cList.push('a', 0, 0);
	assert(cList.isEmpty() == false);
	printf("\tcList is not empty after \'a\' is pushed.\n");
	cList.push('b', 0, 0);
	assert(cList.isEmpty() == false);
	printf("\tcList is not empty after \'b\' is pushed.\n");
	cList.pop();
	assert(cList.isEmpty() == false);
	printf("\tcList is not empty after \'a\' is popped.\n");
	cList.pop();
	assert(cList.isEmpty() == true);
	printf("\tcList is empty after \'b\' is popped.\n");
}

int main() {
	testValidCharacters();
	testInvalidCharacters();
	testAllCharacters();
	testEmpty();
	return 0;
}
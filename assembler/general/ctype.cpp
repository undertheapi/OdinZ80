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
	file name: ctype.cpp
	date created: 09/03/2012
	date updated: 09/03/2013
	author: Gareth Richardson
	description: The object for string and character functions that the odin assembler will use.
	Used for validation, manipulation and convertion.
*/

#include <string>

using namespace std;

#include "../character/charnode.hpp"
#include "ctype.hpp"


/*
	This is a custom method that checks that a CHARACTER is an alphabetical character.
	That is a character between A and Z or a and z.
*/
bool isAlphabetical(CHARACTER value) {
	return (value >= 'a' && value <= 'z') || (value >= 'A' && value <= 'Z');
}

/*
	This is another custom method class that checks that a character is numerical in
	the decimal sense. Between 0 and 9.
*/
bool isNumerical(CHARACTER value) {
	return value >= '0' && value <= '9';
}

/*
	This method checks if the character value is a printable character. That is, it is not
	the first 32 ASCII values AND not the DEL character.
*/
bool isPrintable(CHARACTER value) {
	return value >= 32 && value <= 126;
}

/*
	This method checks if a CHARACTER value is a hexidecimal value:
*/
bool isHex(CHARACTER value) {
	return (value >= '0' && value <= '9') || (value >= 'a' && value <= 'f') || (value >= 'A' && value <= 'F');
}

bool isBinary(CHARACTER value) {
	return value == '0' || value == '1';
}

bool isDecimalString(string value) {
	bool valid = true;
	int index = 0;
	while (valid && index < value.size()) {
		if (!isNumerical(value.at(index))) {
			valid = false;
		}
		index++;
	}
	return valid;
}

bool isHexString(string value) {
	bool valid = true;
	int index = 0;
	while (valid && index < value.size()) {
		if (!isHex(value.at(index))) {
			valid = false;
		}
		index++;
	}
	return valid;
}

bool isBinaryString(string value) {
	bool valid = true;
	int index = 0;
	while (valid && index < value.size()) {
		if (!isBinary(value.at(index))) {
			valid = false;
		}
		index++;
	}
	return valid;
}

string integerToString(int value) {
	if (value == 0) {
		return "0";
	}

	string retValue = "";

	while (value > 0) {
		retValue += value % 10 + 48;
		value /= 10;
	}

	return retValue;
}

string convertHex(char value) {
	string retString = "";
	char hexArray[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	retString += hexArray[(int)((value >> 4) & 0x000f)];
	retString += hexArray[(int)((value) & 0x000f)];
	return retString;
}

string toUpper(string value) {
	string retString = "";
	for (int i = 0; i < value.size(); i++) {
		if (value[i] >= 'a' && value[i] <= 'z') {
			retString += value[i] - 32;
		} else {
			retString += value[i];
		}
	}
	return retString;
}

string toFirstCharUpper(string value) {
	string retString = "";
	if (value[0] >= 'a' && value[0] <= 'z') {
		retString += value[0] - 32;
	} else {
		retString += value[0];
	}
	
	for (int i = 1; i < value.size(); i++) {
		retString += value[i];
	}
	
	return retString;
}


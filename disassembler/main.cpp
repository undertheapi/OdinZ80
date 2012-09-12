#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

#include "bytefile.hpp"
#include "z80.hpp"

ByteFile fileData;

BYTE convertFromHex(char* array);

int main( int argc, char *argv[]) {
	if (argc == 1) {
		cout << "no input file declared." << endl;
	} else if (argc == 2) {
		ifstream input;
		input.open(argv[1], ios::binary);
		if(input.fail()) {
			cout << "File failed to open." << endl;;
			return 0;
		}
		while (!input.eof()) {
			char valueFromFile;
			input.get(valueFromFile);
			fileData.push(valueFromFile);
		}
		input.close();
		ofstream output;
		output.open("output.asm");
		output << ";-----------------------------" << endl;
		output << ";  disassembled using the" << endl;
		output << ";  odin Z80 development" << endl;
		output << ";  suite." << endl;
		output << ";-----------------------------" << endl;
		while (!fileData.isEmpty()) {
			string outputString = runZ80(fileData);
			output << outputString;
		}
		output.close();
	} else {
		bool stringState = false; //treats the char value as a hex string.
		/*
			add more boolean states here
		*/
		int indexOfString = 1;
		for (int index = 0; index < argc; index++) {
			if (strcmp(argv[index], "-s") == 0) {
				stringState = true;
			} else {
				indexOfString = index;
			}
		}
		if (stringState) {
			char* hexString = argv[indexOfString];
			bool validHexString = true;
			int index = 0;
			while (validHexString && index < strlen(hexString)) {
				if (isxdigit(hexString[index]) == 0) {
					validHexString = false;
				}
				index++;
			}
			if (!validHexString) {
				cout << "not a valid hex string." << endl;
			} else {
				if (strlen(hexString) % 2 != 0) {
					strcat(hexString, "0");
					cout << "added a \"0\" to the end of the string to make it even." << endl;
				}
				/*
					now to convert the hex string into a ByteFile object.
				*/
				index = 0;
				ByteFile smallList;
				while (index < strlen(hexString)) {
					char array[2];
					array[0] = hexString[index];
					index++;
					array[1] = hexString[index];
					index++;
					smallList.push(convertFromHex(&array[0]));
				}
				/*
					now the hex string is in smallList, run the
					dissassembler now!
				*/
				while (!smallList.isEmpty()) {
					string val = runZ80(smallList);
					cout << val;
				}
			}
		}
	}
	return 0;
}

BYTE convertFromHex(char* array) {
	/*
		now the pointer has to be 2 chars ONLY
	*/
	BYTE retValue = 0;
	if (array[0] >= '0' && array[0] <= '9') {
		retValue |= (array[0] - 48) << 4;
	} else {
		retValue |= (array[0] - 87) << 4;
	}
	if (array[1] >= '0' && array[1] <= '9') {
		retValue |= (array[1] - 48) & 0x0f;
	} else {
		retValue |= (array[1] - 87) & 0x0f;
	}
	return retValue;
}

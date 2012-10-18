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

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>

/*
	This is for the getopt() method. In Linux, it is part of the unistd
	header file, but in MingW Gcc, we have the getopt.h to include.
*/
#ifdef __linux__
	#include <unistd.h>
#endif

#ifdef _WIN32
	#include <getopt.h>
#endif

using namespace std;

#include "bytefile.hpp"
#include "z80.hpp"

ByteFile fileData;

BYTE convertFromHex(char* array);

int main( int argc, char *argv[]) {
if (argc == 1) {
		printf("ZDIS: There has been no file, options or string input specified.\n");
	} else {
		bool fileFlag = true;
		bool stringFlag = false;
		int startPosition = 0;
		int endPosition = -1;
		char* hexString = 0;
		char* inputFile = 0;
		char* outputFile = 0;
		
		int opt = getopt(argc, argv, "sa:b:e:o:hi");
		while (opt != -1) {
			switch (opt) {
				case 's':
					/* found a string input */
					stringFlag = true;
					fileFlag = false;
					break;
				case 'a':
					/* address to be set */
					//address = atoi(optarg);
					break;
				case 'b':
					/* The starting position of the disassembler */
					//########We should do some error checking here:
					startPosition = atoi(optarg);
					break;
				case 'e':
					/* This is were the disassembler should end */
					//########We should do some error checking here:
					endPosition = atoi(optarg);
					break;
				case 'o':
					/* the output file that will contain the opcodes. */
					/* If this is not set, the opcodes will be        */
					/* displayed on  the console. */
					outputFile = optarg;
					break;
				case 'h':
					/* Help options. */
					break;
				case 'i':
					/* info on ZDIS etc. */
					break;
				case ':':
					printf("ZDIS: There is an option that needs a value in the command prompt.\n");
					//get out of system ASAP!
					exit(0);
					break;
				case '?':
					printf("ZIDS: These is an unknown option \'%c\' in the command prompt.\n", opt);
					break;
			}
			opt = getopt(argc, argv, "s:a:b:e:o:hi");
		}
		
		//If zdis has been told NOT to manipulate a string, it is a file.
		if (!stringFlag && optind != -1) {
			inputFile = argv[optind];
		}
		
		if (!fileFlag && optind != -1) {
			hexString = argv[optind];
		}
		
		if (stringFlag) {
			//Processes a string from the prompt.
			bool validHexString = true;
			int index = 0;
			while (validHexString && index < strlen(hexString)) {
				if (isxdigit(hexString[index]) == 0) {
					validHexString = false;
				}
				index++;
			}
			if (!validHexString) {
				printf("ZDIS: The input string is not a valid Hex String.\n");
			} else {
				if (strlen(hexString) % 2 != 0) {
					strcat(hexString, "0");
					printf("ZDIS: Added a \"0\" to the end of the string to make it even.");
				}
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
				while (!smallList.isEmpty()) {
					string val = runZ80(smallList);
					printf("%s", val.c_str());	//No need to at a NEW LINE character.
				}
			}
		} else {
			//we have a file
			#ifdef __linux__
				
			#endif
			
			#ifdef _WIN32
				
			#endif
		}
	}
	exit(0);
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

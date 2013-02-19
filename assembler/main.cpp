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
	file name: main.cpp
	date created: 18/02/2012
	date updated: 19/02/2013
	author: Gareth Richardson
	description: This is the main method for the zdis program.
*/

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <fstream>
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

#include "character/characterlist.hpp"
#include "lex/tokenlist.hpp"
#include "lex/lex.hpp"
#include "parser/bytecode.hpp"
#include "parser/addresslist.hpp"
#include "parser/foundlist.hpp"
#include "parser/parser.hpp"

ifstream::pos_type size;
char * memblock;
char backupName[] = "output.bin";

//unsigned char* asBytes(

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("ODIN: There has been no file specified.\n");
	} else {
		char* inputFile = 0;
		char* outputFile = 0;
		int opt = getopt(argc, argv, "o:");
		//printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.\n");
		while (opt != -1) {
			switch(opt) {
				case 'o':
					outputFile = optarg;
					break;
				case ':':
					printf("ODIN: There is an option that needs a value in the command prompt.\n");
					//get out of system ASAP!
					exit(0);
					break;
				case '?':
					printf("ODIN: There is an unknown option \'%c\' in the command prompt.\n", opt);
					exit(0);
					break;
			}
			opt = getopt(argc, argv, "o:");
		}
		
		if (optind != -1) {
			inputFile = argv[optind];
		} else {
			printf("ODIN: No input file has been specified.\n");
			exit(0);
		}
		
		if (outputFile == 0) {
			outputFile = &backupName[0];
		}
		
		ifstream file(inputFile, ios::binary);
		if (!file) {
			printf("ODIN: The file \"%s\" does not exist.\n", inputFile);
			exit(0);
		}
		
    	CharacterList cList;
    	
    	char val;
    	while (file.read(static_cast<char*>(&val), sizeof(unsigned char))) {
    		cList.push(val);
    	}
    	
    	file.close();
    	
    	
    	if (cList.errorState) {
    		printf("ODIN: Invalid character in the file.\n");
    		exit(0);
    	}
    	
    	cList.finishedFile();
    	
    	TokenList tList;
	
		Lex lexObj(&cList, &tList);
	
		lexObj.run();
		
		if (lexObj.checkForError()) {
			printf("%s\n", lexObj.getError().c_str());
			exit(0);
		}
		
		ByteCode bObj;
		
		Z80Parser pObj(&tList, &bObj);
		
		pObj.run();
		
		if (pObj.checkState()) {
			printf("%s\n", pObj.getError().c_str());
			exit(0);
		}
		
		ByteCode bCode;
		ofstream out(outputFile, ios::binary);
		for (int index = 0; index < bCode.getSize(); index++) {
			out.put(bCode.getElement(index));
		}
		out.close();
	}
	return 0;
}


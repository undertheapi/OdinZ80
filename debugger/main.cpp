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
	file name: main.cpp
	date created: 09/06/2014
	date updated: 02/05/2015
	author: Gareth Richardson
	description: This is the main program source. The program is to start here.
*/

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#include "ram/ram.hpp"
#include "registers/registers.hpp"
#include "registers/specialregisters.hpp"
#include "cpu/z80cpu.hpp"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("ZDEBUG: There has been no file specified.\n");
		return 0;
	}
	
	string fileLocation = argv[1];
	ifstream file(fileLocation.c_str(), ios::binary);
	
	if (file) {
		Z80CPU box;
		
		/*
			Put the binary file into the ram.
		*/
		char val;
		unsigned short index = 0;
		while (file.read(static_cast<char*>(&val), sizeof(unsigned char))) {
			box.loadUpRAM(index, val);
			index++;
		}
		
		/*
			Now we end up in the command loop:
		*/
		bool invalidJump = false;
		
		while (!invalidJump) {
			string command = "";
			
			cout << ">>";
			cin >> command;
			
			if (!command.compare("step") || !command.compare("STEP") || !command.compare("s") || !command.compare("S")) {
				box.step();
				cout << box.getCurrentInstruction() << endl;
			} else if (!command.compare("reg") || !command.compare("REG") || !command.compare("r") || !command.compare("R")) {
				cout << box.prettyPrint() << endl;
			} else if (!command.compare("exit") || !command.compare("Exit") || !command.compare("EXIT") || !command.compare("e") || !command.compare("E")) {
				invalidJump = true;
			} else {
				continue;
			}
		}
	} else {
		printf("ZDEBUG: The file location is incorrect.\n");
		return 0;
	}
	return 0;
}

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
	file name: meta.cpp
	date created: 05/07/2014
	date updated: 05/07/2014
	author: Gareth Richardson
	description: The object file of the meta methods.
*/

#include <cstdio>
#include <string>

using namespace std;

#include "meta.hpp"

/*
	This is the version of the release.
*/
string version = "1.0";

/*
	The exact time and date when the source code was compiled.
*/
string timeCreated = __TIME__;

string dateCreated = __DATE__;

void helpPrettyPrint() {
	printf("odin <file_location> will output a binary file called output.bin.\n");
	printf("odin <file_location> -o <file name> will output a binary file of the specified name.\n");
	printf("odin -a will display an about display.\n");
	printf("odin -h will display this.\n");
}

void aboutPrettyPrint() {
	printf("ODIN Z80 assembler. An assembler for the 8-BIT Zilog Z80 CPU.\n");
	printf("Created in C++ %s\n", dateCreated.c_str());
}
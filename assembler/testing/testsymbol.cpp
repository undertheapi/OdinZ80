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

#include <assert.h>
#include <stdio.h>
#include <string>

using namespace std;

#include "../symbol_table/symbol_table.hpp"

int main() {
	string* value1 = new string;
	value1->assign("Peter");
	string* value2 = new string;
	value2->assign("Daniel");
	string* value3 = new string;
	value3->assign("June");
	string* value4 = new string;
	value4->assign("Jeramie");
	string* value5 = new string;
	value5->assign("June");
	string* value6 = new string;
	value6->assign("Bruno");
	string* value7 = new string;
	value7->assign("Ethan");
	string* value8 = new string;
	value8->assign("Bruno");
	
	SYMBOL_TABLE* table = new SYMBOL_TABLE;
	
	table->init();
	
	assert(table->addSymbol(value1) == 0);
	assert(table->addSymbol(value2) == 1);
	assert(table->addSymbol(value3) == 2);
	assert(table->addSymbol(value4) == 3);
	assert(table->addSymbol(value5) == 2);
	assert(table->addSymbol(value6) == 4);
	assert(table->addSymbol(value7) == 5);
	assert(table->addSymbol(value8) == 4);
	
	return 0;
}
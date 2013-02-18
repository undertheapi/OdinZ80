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
	file name: testparser.cpp
	date created: 13/2/2013
	date updated: 15/2/2013
	author: Gareth Richardson
	description: Unt test for the Z80Parser class.
*/

#include <assert.h>
#include <stdio.h>
#include <string>

using namespace std;

#include "../character/characterlist.hpp"
#include "../lex/tokenlist.hpp"
#include "../lex/lex.hpp"
#include "../parser/bytecode.hpp"
#include "../parser/addresslist.hpp"
#include "../parser/foundlist.hpp"
#include "../parser/parser.hpp"

void testDB() {
	printf("**Testing the DB command in the Parser.\n");
	CharacterList cList;
	char array[] = "DB 45\nDB 10, 12, 14\n";
	
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
	
	ByteCode bObj;
	
	Z80Parser pObj(&tList, &bObj);
	printf("Attempt to run parser.\n");
	pObj.run();
	
	assert(pObj.checkState() == false);
	
	assert(bObj.getElement(0) == 45);
	assert(bObj.getElement(1) == 10);
	assert(bObj.getElement(2) == 12);
	assert(bObj.getElement(3) == 14);
}

void testDBString() {
	printf("**Testing the DB command in the Parser using a string.\n");
	CharacterList cList;
	char array[] = "DB 45\nDB \"Hello World!\"\n\n";
	
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
	
	ByteCode bObj;
	
	Z80Parser pObj(&tList, &bObj);
	printf("Attempt to run parser.\n");
	pObj.run();
	
	assert(pObj.checkState() == false);
	
	assert(bObj.getElement(0) == 45);
	assert(bObj.getElement(1) == 72);
	assert(bObj.getElement(2) == 101);
	assert(bObj.getElement(3) == 108);
	assert(bObj.getElement(4) == 108);
	assert(bObj.getElement(5) == 111);
	assert(bObj.getElement(6) == 32);
	assert(bObj.getElement(7) == 87);
	assert(bObj.getElement(8) == 111);
	assert(bObj.getElement(9) == 114);
	assert(bObj.getElement(10) == 108);
	assert(bObj.getElement(11) == 100);
	assert(bObj.getElement(12) == 33);
}

void testDW() {
	printf("**Testing the DW command in the Parser.\n");
	CharacterList cList;
	char array[] = "DB $45\nDW $4578\n\nDW $5690, $4790\n\n\n";
	
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
	
	ByteCode bObj;
	
	Z80Parser pObj(&tList, &bObj);
	printf("Attempt to run parser.\n");
	pObj.run();
	
	if (pObj.checkState()) {
		printf("ERROR:: %s\n", pObj.getError().c_str());
	}
	assert(pObj.checkState() == false);
	
	assert(bObj.getElement(0) == 0x45);
	assert(bObj.getElement(1) == 0x78);
	assert(bObj.getElement(2) == 0x45);
	assert(bObj.getElement(3) == 0x90);
	//printf("should be 0x56 but %x\n", (int) bObj.getElement(4));
	assert(bObj.getElement(4) == 0x56);
	//printf("should be 0x90 but %x\n", (int) bObj.getElement(4));
	assert(bObj.getElement(5) == 0x90);
	//printf("should be 0x47 but %x\n", (int) bObj.getElement(4));
	assert(bObj.getElement(6) == 0x47);
}

void testREP() {
	printf("**Testing the REP command in the Parser.\n");
	CharacterList cList;
	char array[] = "DB $45\nDW $4578\n\nDW $5690, $4790\nREP 3, $97\n\n\nREP 5, $7510\n\n";
	
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
	
	ByteCode bObj;
	
	Z80Parser pObj(&tList, &bObj);
	pObj.run();
	
	if (pObj.checkState()) {
		printf("%s\n", pObj.getError().c_str());
	}
	assert(pObj.checkState() == false);
	
	//printf("Size of the byte code: %i\n", bObj.getSize());
	assert(bObj.getSize() == 20);
	
	assert(bObj.getElement(0) == 0x45);
	assert(bObj.getElement(1) == 0x78);
	assert(bObj.getElement(2) == 0x45);
	assert(bObj.getElement(3) == 0x90);
	assert(bObj.getElement(4) == 0x56);
	assert(bObj.getElement(5) == 0x90);
	assert(bObj.getElement(6) == 0x47);
	
	/*
		The REP instruction results:
	*/
	
	assert(bObj.getElement(7) == 0x97);
	assert(bObj.getElement(8) == 0x97);
	assert(bObj.getElement(9) == 0x97);
	
	assert(bObj.getElement(10) == 0x10);
	assert(bObj.getElement(11) == 0x75);

	assert(bObj.getElement(12) == 0x10);
	assert(bObj.getElement(13) == 0x75);
	
	assert(bObj.getElement(14) == 0x10);
	assert(bObj.getElement(15) == 0x75);
	
	assert(bObj.getElement(16) == 0x10);
	assert(bObj.getElement(17) == 0x75);
	
	assert(bObj.getElement(18) == 0x10);
	assert(bObj.getElement(19) == 0x75);
	
	//printf("IN REP TESTING\n");
}

void testLD1() {
	printf("**1::Testing the LD command in the Parser.\n");
	CharacterList cList;
	char array[] = "DB $45\nDW $4578\nLD B, C\n   LD A, H\n\n";
	
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
	
	ByteCode bObj;
	
	Z80Parser pObj(&tList, &bObj);
	pObj.run();
	
	assert(pObj.checkState() == false);
	
	assert(bObj.getElement(0) == 0x45);
	assert(bObj.getElement(1) == 0x78);
	assert(bObj.getElement(2) == 0x45);
	
	/* the LD in machine code: */
	assert(bObj.getElement(3) == 0x41);
	assert(bObj.getElement(4) == 0x7c);
}

void testLD2() {
	printf("**2::Testing the LD command in the Parser.\n");
	CharacterList cList;
	char array[] = "DB $70\nLD B, H\n\t\tld H, a\nLd b   , H\n\nLD A, $45\nLD b, $af\nld [IX+$5], $69\n";
	
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
	
	ByteCode bObj;
	
	Z80Parser pObj(&tList, &bObj);
	pObj.run();
	
	assert(pObj.checkState() == false);
	
	assert(bObj.getElement(0) == 0x70);
	
	/* the LD in machine code: */
	assert(bObj.getElement(1) == 0x44);
	assert(bObj.getElement(2) == 0x67);
	assert(bObj.getElement(3) == 0x44);
	assert(bObj.getElement(4) == 0x3e);
	assert(bObj.getElement(5) == 0x45);
	assert(bObj.getElement(6) == 0x06);
	assert(bObj.getElement(7) == 0xaf);
	assert(bObj.getElement(8) == 0xdd);
	assert(bObj.getElement(9) == 0x36);
	assert(bObj.getElement(10) == 0x05);
	assert(bObj.getElement(11) == 0x69);
}

void testLD3() {
	printf("**3::Testing the LD command in the Parser.\n");
	CharacterList cList;
	char array[] = "LD [IX + 60], A\n\nLD B, [iy+$40]\n";
	
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
	
	ByteCode bObj;
	
	Z80Parser pObj(&tList, &bObj);
	pObj.run();
	
	assert(pObj.checkState() == false);
	
	assert(bObj.getElement(0) == 0xdd);
	assert(bObj.getElement(1) == 0x77);
	assert(bObj.getElement(2) == 60);
	assert(bObj.getElement(3) == 0xfd);
	assert(bObj.getElement(4) == 0x46);
	assert(bObj.getElement(5) == 0x40);
}

 void testLD4() {
 	printf("**4::Testing the LD command in the Parser.\n");
	CharacterList cList;
	char array[] = "LD [HL], A\n\nLD B, [iy+$40]\n\n\n\tld b, [hl]\nld [hl], $10\n";
	
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
	
	ByteCode bObj;
	
	Z80Parser pObj(&tList, &bObj);
	pObj.run();
	
	assert(pObj.checkState() == false);
	
	assert(bObj.getElement(0) == 0x77);
	assert(bObj.getElement(1) == 0xfd);
	assert(bObj.getElement(2) == 0x46);
	assert(bObj.getElement(3) == 0x40);
	assert(bObj.getElement(4) == 0x46);
	assert(bObj.getElement(5) == 0x36);
	assert(bObj.getElement(6) == 0x10);
 }
 
 void testLD5() {
 	printf("**5::Testing the LD command in the Parser.\n");
	CharacterList cList;
	char array[] = "lbl:\t\t\tld b, d\n\nLD [ix + $5], d\nld a, [lbl]\n\n\n\nLD a, [bc]\n\nlab:\nld c,d\nld d,e\n\n\nLD a, [lab  ]\n";
	
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
	
	ByteCode bObj;
	
	Z80Parser pObj(&tList, &bObj);
	
	pObj.run();
	assert(pObj.checkState() == false);
	
	assert(bObj.getElement(0) == 0x42);
	assert(bObj.getElement(1) == 0xdd);
	assert(bObj.getElement(2) == 0x72);
	assert(bObj.getElement(3) == 0x05);
	assert(bObj.getElement(4) == 0x3a);
	assert(bObj.getElement(5) == 0x00);
	assert(bObj.getElement(6) == 0x00);
	assert(bObj.getElement(7) == 0x0a);
	assert(bObj.getElement(8) == 0x4a);
	assert(bObj.getElement(9) == 0x53);
	assert(bObj.getElement(10) == 0x3a);
	assert(bObj.getElement(11) == 0x08);
	assert(bObj.getElement(12) == 0x00);
 }
 
 void testLD6() {
 	printf("**6::Testing the LD command in the Parser.\n");
	CharacterList cList;
	char array[] = "ld bc, [$05]\nld de, [$9050]\nld hl , [$1020]\nld sp, [$8412]\nld [$1523], hl\n";
	
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
	
	ByteCode bObj;
	
	Z80Parser pObj(&tList, &bObj);
	
	pObj.run();
	assert(pObj.checkState() == false);
	
	assert(bObj.getElement(0) == 0xed);
	assert(bObj.getElement(1) == 0x4b);
	assert(bObj.getElement(2) == 0x05);
	assert(bObj.getElement(3) == 0x00);
	
	assert(bObj.getElement(4) == 0xed);
	assert(bObj.getElement(5) == 0x5b);
	assert(bObj.getElement(6) == 0x50);
	assert(bObj.getElement(7) == 0x90);
	
	assert(bObj.getElement(8) == 0xed);
	assert(bObj.getElement(9) == 0x6b);
	assert(bObj.getElement(10) == 0x20);
	assert(bObj.getElement(11) == 0x10);
	
	assert(bObj.getElement(12) == 0xed);
	assert(bObj.getElement(13) == 0x7b);
	assert(bObj.getElement(14) == 0x12);
	assert(bObj.getElement(15) == 0x84);
	
	assert(bObj.getElement(16) == 0x22);
	assert(bObj.getElement(17) == 0x23);
	assert(bObj.getElement(18) == 0x15);
 }
 
 void testAddressing() {
 	printf("**Testing Addressing.\n");
	CharacterList cList;
	char array[] = "ld bc, [var1]\nld de, [var2]\nld hl, [var3]\n\nLD HL, [var1]\n  ld sp, [ var4 ]\nvar1: db $05, $06, $07\nvar2: dw $5545\n var3: dw $5653, $5758\nvar4: db \"01234\"\nld IX, [$4500]\nld ix, [var4]\n";
	
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
	
	ByteCode bObj;
	
	Z80Parser pObj(&tList, &bObj);
	
	pObj.run();

	assert(pObj.checkState() == false);
	
	assert(bObj.getElement(0) == 0xed);
	assert(bObj.getElement(1) == 0x4b);
	assert(bObj.getElement(2) == 20);
	assert(bObj.getElement(3) == 0x00);
	
	assert(bObj.getElement(4) == 0xed);
	assert(bObj.getElement(5) == 0x5b);
	assert(bObj.getElement(6) == 23);
	assert(bObj.getElement(7) == 0x00);
	
	assert(bObj.getElement(8) == 0xed);
	assert(bObj.getElement(9) == 0x6b);
	assert(bObj.getElement(10) == 25);
	assert(bObj.getElement(11) == 0x00);
	
	assert(bObj.getElement(12) == 0xed);
	assert(bObj.getElement(13) == 0x6b);
	assert(bObj.getElement(14) == 20);
	assert(bObj.getElement(15) == 0x00);
	
	assert(bObj.getElement(16) == 0xed);
	assert(bObj.getElement(17) == 0x7b);
	assert(bObj.getElement(18) == 29);
	assert(bObj.getElement(19) == 0x00);
	
	assert(bObj.getElement(20) == 5);
	assert(bObj.getElement(21) == 6);
	assert(bObj.getElement(22) == 7);
	assert(bObj.getElement(23) == 0x45);
	assert(bObj.getElement(24) == 0x55);
	assert(bObj.getElement(25) == 0x53);
	assert(bObj.getElement(26) == 0x56);
	assert(bObj.getElement(27) == 0x58);
	assert(bObj.getElement(28) == 0x57);
	
	assert(bObj.getElement(29) == 48);
	assert(bObj.getElement(30) == 49);
	assert(bObj.getElement(31) == 50);
	assert(bObj.getElement(32) == 51);
	assert(bObj.getElement(33) == 52);
	
	assert(bObj.getElement(34) == 0xdd);
	assert(bObj.getElement(35) == 0x2a);
	assert(bObj.getElement(36) == 0x00);
	assert(bObj.getElement(37) == 0x45);
	assert(bObj.getElement(38) == 0xdd);
	assert(bObj.getElement(39) == 0x2a);
	assert(bObj.getElement(40) == 29);
	assert(bObj.getElement(41) == 0);
 }

int main() {
	testDB();
	testDBString();
	testDW();
	testREP();
	testLD1();
	testLD2();
	testLD3();
	testLD4();
	testLD5();
	testLD6();
	testAddressing();
	return 0;
}


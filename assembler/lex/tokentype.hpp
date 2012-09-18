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
	file name: tokentype.hpp
	date created: 3/09/2012
	date updated: 12/09/2012
	author: Gareth Richardson
	description: This is a file of definitions for the types of tokens that are valid
	in the assembler. The TOkenNode data structure stores the type as an unsigned char,
	so make sure that the amount of tokens do not exceed 256.
*/

/*
	these are the opcode types:
*/
#define ADC 0
#define ADD 1
#define AND 2
#define BIT 3
#define CALL 4
#define CCF 5
#define CPL 6
#define DAA 7
#define DEC 8
#define DI 9
#define EI 10
#define EXX 11
#define HALT 12
#define IM 13
#define IN 14
#define INC 15
#define JP 16
#define LD 17
#define NEG 18
#define NOP 19
#define OUT 20
#define POP 21
#define PUSH 22
#define RES 23
#define RET 24
#define RETI 25
#define RETN 26
#define RLA 27
#define RLCA 28
#define RLD 29
#define RRA 30
#define RRCA 31
#define RRD 32
#define RST 33
#define SBC 34
#define SCF 35
#define SET 36

/*
	these are registers:
*/
#define A 37
#define F 38
#define B 39
#define C 40
#define D 41
#define E 42
#define H 43
#define L 44
#define BC 45
#define DE 46
#define HL 47
#define I 48
#define R 49
#define IX 50
#define IY 51
#define SP 52
#define PC 53

/*
	these are assembler instructions:
*/
#define CPU 54
#define DB 55
#define DW 56
#define ORG 57
#define REP 58
#define SPECREP 59

/*
	grammar:
*/
#define ATOM 60
#define COLON 61
#define COMMA 62
#define NEW_LINE 63

/*
	an end of file token type:
*/
#define EOF 255
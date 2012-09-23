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
	date updated: 23/09/2012
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
#define CP 6
#define CPD 7
#define CPDR 8
#define CPI 9
#define CPIR 10
#define CPL 11
#define DAA 12
#define DEC 13
#define DI 14
#define DJNZ 15
#define EI 16
#define EX 17
#define EXX 18
#define HALT 19
#define IM 20
#define IN 21
#define INC 22 
#define IND 23
#define INDR 24
#define INI 25
#define INIR 26
#define JP 27
#define JR 28
#define LD 29
#define LDD 30
#define LDDR 31
#define LDI 32
#define LDIR 33
#define NEG 34
#define NOP 35
#define OR 36
#define OTDR 37
#define OTIR 38
#define OUT 39
#define OUTD 40
#define OUTI 41
#define POP 42
#define PUSH 43
#define RES 44
#define RET 45
#define RETI 46
#define RETN 47
#define RL 48
#define RLA 49
#define RLCA 50
#define RLD 51
#define RR 52
#define RRA 53
#define RRC 54
#define RRCA 55
#define RRD 56
#define RST 57
#define SBC 58
#define SCF 59
#define SET 60
#define SLA 61
#define SRA 62
#define SRL 63
#define SUB 64
#define XOR 65

/*
	these are registers:
*/
#define A 66
#define F 67
#define B 68
#define C 69	// Also the Carry token as well
#define D 70
#define E 71
#define H 72
#define L 73
#define BC 74
#define DE 75
#define HL 76
#define I 77
#define R 78
#define IX 79
#define IY 80
#define PC 81
#define SP 82

/*
	these are assembler instructions:
*/
#define CPU 83		// CPU type (for future compatibility).
#define DB 84		// Declare a byte in the output machine code.
#define DW 85		// Declare a word in the output machine code.
#define ORG 86		// The address the byte code will be executed from.
#define REP 87		// Repeats a byte a specified amount of times.
#define SPECREP 88	// A custom repeat command. Repeats a set of bytes instead of one.

/*
	grammar:
*/
#define ATOM 89			// A none reserved word in the source code, includes numbers as well.
#define COLON 90		// A ":" character, used for labels and addresses.
#define COMMA 91		// A ',' character.
#define NEW_LINE 92
#define LEFT_BRACKET 93
#define RIGHT_BRACKET 94

/*
	This are the JMP condition Tokens:
	(Note that the C "Carry" condition type is also the same as the C register,
	so, it has been declared above in the Register section of this file).
*/
#define M 95
#define NC 96
#define NZ 97
#define P 98
#define PE 99
#define PO 100
#define Z 101

/*
	an end of file token type:
*/
#define END_OF_FILE 255

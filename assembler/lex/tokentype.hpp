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
	file name: tokentype.hpp
	date created: 3/09/2012
	date updated: 05/12/2014
	author: Gareth Richardson
	description: This is a file of definitions for the types of tokens that are valid
	in the assembler. The TokenNode data structure stores the type as an unsigned char,
	so make sure that the amount of tokens do not exceed 256.
	TODO: Turn this into an enumeration.
*/

/*
	these are the op-code types:
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
#define RLC 50
#define RLCA 51
#define RLD 52
#define RR 53
#define RRA 54
#define RRC 55
#define RRCA 56
#define RRD 57
#define RST 58
#define SUB 59
#define SUBC 60
#define SCF 61
#define SET 62
#define SLA 63
#define SRA 64
#define SRL 65
#define XOR 66

/*
	these are registers:
*/
#define F 67
#define B 68
#define C 69	// Also the Carry token as well
#define D 70
#define E 71
#define H 72
#define L 73
#define A 74
#define BC 75
#define DE 76
#define HL 77
#define I 78
#define R 79
#define IX 80
#define IY 81
#define PC 82
#define SP 83
#define AF 84

/*
	these are assembler instructions:
*/
#define CPU 85		// CPU type (for future compatibility).
#define DB 86		// Declare a byte in the output machine code.
#define DW 87		// Declare a word in the output machine code.
#define DDW 88		// Declare a double word in the output machine code.
#define ORG 89		// The address the byte code will be executed from.
#define REP 90		// Repeats a byte a specified amount of times.
#define SPECREP 91	// A custom repeat command. Repeats a set of bytes instead of one.

/*
	grammar:
*/
#define ATOM 92			// A none reserved word in the source code, includes numbers as well.
#define COLON 93		// A ":" character, used for labels and addresses.
#define COMMA 94		// A ',' character.
#define NEW_LINE 95
#define LEFT_BRACKET 96
#define RIGHT_BRACKET 97
#define PLUS 98
#define MINUS 99
#define MULTIPLY 100

/*
	This are the JMP condition Tokens:
	(Note that the C "Carry" condition type is also the same as the C register,
	so, it has been declared above in the Register section of this file).
*/
#define M 101
#define NC 102
#define NZ 103
#define P 104
#define PE 105
#define PO 106
#define Z 107

/*
	Other Token Types here:
*/
#define NUMBER 160
#define STRING 161

#define LEFT_PARENT 162
#define RIGHT_PARENT 163

#define DOT_POINT 164 //a dot '.'

/*
	Directive Instruction set:
*/
#define DIR_EQU 165


/*
	an end of file token type:
*/
#define END_OF_FILE 255

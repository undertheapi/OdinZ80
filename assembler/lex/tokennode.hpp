/*
	Copyright (c) 2013, Gareth Richardson
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
	file name: tokennode.hpp
	date created: 28/08/2012
	date updated: 25/10/2012
	author: Gareth Richardson
	description: This is the data structure for the TokenNode in the TokenList class. The
	TokenList class is an implementation of a Singly Linked List data structure. This
	structure is the Node representation in the TokenList class.
*/

/*
	In a token, a byte that represents the type of token is present. Most likely the
	byte will be more than enough as there is at the moment less than 255 token types
	in the assembler.
*/
#define TOKEN_TYPE unsigned char

/*
	Here is the structure for the TokenNode.
	For now, we are not having a file name in the structure. Odin at the moment will
	be assembling one file at a time with no includes from other files.
*/
struct TokenNode {
	TOKEN_TYPE type;
	string value;
	int lineNumber;
	/* char* fileName; */
	TokenNode* next;
};

/*
	This is a pointer type definition of a TokenNode.
*/
typedef TokenNode* TokenNodePtr;

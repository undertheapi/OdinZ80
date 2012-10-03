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
	file name: parser.cpp
	date created: 28/09/2012
	date updated: 28/09/2012
	author: Gareth Richardson
	description: This is the Z80 parser. Give it a TokenList object and it will
	parse it and output the machine code for it.
*/

#include <string>

using namespace std;

#include "../lex/tokentype.hpp"
#include "../lex/tokenlist.hpp"
#include "bytecode.hpp"
#include "parser.hpp"

void Z80Parser::init() {
	Z80Parser::tList = NULL;
	Z80Parser::bCode = NULL;
	Z80Parser::errorState = false;
	Z80Parser::errorString = "";
	Z80Parser::address = 0;
}

Z80Parser::Z80Parser(TokenList* tPointer, ByteCode* bPointer) {
	Z80Parser::init();
	Z80Parser::tList = tPointer;
	Z80Parser::bCode = bPointer;
}

void Z80Parser::run() {
	while (!Z80Parser::errorState && !Z80Parser::tList->isEmpty()) {
		if (Z80Parser::tList->peekTokenType() == ADC) {
			Z80Parser::tList->pop();
			if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == A) {
				Z80Parser::tList->pop();
				if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == COMMA) {
					Z80Parser::tList->pop();
					if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == A) {
						if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NEW_LINE) {
							/*
								ADC A, A
							*/
							Z80Parser::tList->pop();
							Z80Parser::bCode->pushElement(0x8f);
							Z80Parser::address++;
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
						}
					} else if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == B) {
						if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NEW_LINE) {
							/*
								ADC A, B
							*/
							Z80Parser::tList->pop();
							Z80Parser::bCode->pushElement(0x88);
							Z80Parser::address++;
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
						}
					} else if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == C) {
						if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NEW_LINE) {
							/*
								ADC A, C
							*/
							Z80Parser::tList->pop();
							Z80Parser::bCode->pushElement(0x89);
							Z80Parser::address++;
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
						}
					} else if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == D) {
						if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NEW_LINE) {
							/*
								ADC A, D
							*/
							Z80Parser::tList->pop();
							Z80Parser::bCode->pushElement(0x8a);
							Z80Parser::address++;
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
						}
					} else if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == E) {
						if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NEW_LINE) {
							/*
								ADC A, E
							*/
							Z80Parser::tList->pop();
							Z80Parser::bCode->pushElement(0x8b);
							Z80Parser::address++;
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
						}
					} else if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == H) {
						if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NEW_LINE) {
							/*
								ADC A, H
							*/
							Z80Parser::tList->pop();
							Z80Parser::bCode->pushElement(0x8c);
							Z80Parser::address++;
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
						}
					} else if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == L) {
						if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NEW_LINE) {
							/*
								ADC A, L
							*/
							Z80Parser::tList->pop();
							Z80Parser::bCode->pushElement(0x88);
							Z80Parser::address++;
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
						}
					} else if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NUMBER) {
						if (isByteSize(Z80Parser::tList->peekValue()) {
							Z80Parser::bCode->pushElement(0xce);
							Z80Parser::bCode->pushElement(getByte(Z80Parser::tList->peekValue()));
							Z80Parser::tList->pop();
							if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NEW_LINE) {
								/*
									ADD A, Imm
								*/
								Z80Parser::tList->pop();
								Z80Parser::address++;
							} else {
								Z80Parser::errorState = true;
								Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
							}
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "The Number value in the ADC instruction is not a byte.";
						}
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
					}
				} else if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NEW_LINE) {
					/*
								ADC A
					*/
					Z80Parser::tList->pop();
					Z80Parser::bCode->pushElement(0x8f);
					Z80Parser::address++;
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
				}
			} else if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == B) {
				if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NEW_LINE) {
					/*
								ADC B
					*/
					Z80Parser::tList->pop();
					Z80Parser::bCode->pushElement(0x88);
					Z80Parser::address++;
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
				}
			} else if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == C) {
				if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NEW_LINE) {
					/*
								ADC C
					*/
					Z80Parser::tList->pop();
					Z80Parser::bCode->pushElement(0x89);
					Z80Parser::address++;
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
				}
			} else if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == D) {
				if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NEW_LINE) {
					/*
								ADC D
					*/
					Z80Parser::tList->pop();
					Z80Parser::bCode->pushElement(0x8a);
					Z80Parser::address++;
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
				}
			} else if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == E) {
				if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NEW_LINE) {
					/*
								ADC E
					*/
					Z80Parser::tList->pop();
					Z80Parser::bCode->pushElement(0x8b);
					Z80Parser::address++;
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
				}
			} else if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == H) {
				if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NEW_LINE) {
					/*
								ADC H
					*/
					Z80Parser::tList->pop();
					Z80Parser::bCode->pushElement(0x8c);
					Z80Parser::address++;
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
				}
			} else if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == L) {
				if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NEW_LINE) {
					/*
								ADC L
					*/
					Z80Parser::tList->pop();
					Z80Parser::bCode->pushElement(0x88);
					Z80Parser::address++;
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
				}
			} else if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NUMBER) {
				if (isByteSize(Z80Parser::tList->peekValue()) {
					Z80Parser::bCode->pushElement(0xce);
					Z80Parser::bCode->pushElement(getByte(Z80Parser::tList->peekValue()));
					Z80Parser::tList->pop();
					if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NEW_LINE) {
						/*
							ADD Imm
						*/
						Z80Parser::tList->pop();
						Z80Parser::address++;
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
					}
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "The Number value in the ADC instruction is not a byte.";
				}
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "An ADC instruction has to be in the format of \"ADC A, reg8\", \"ADC reg8\" or \"ADC HL, reg16\"";
			}
		} else {
			Z80Parser::errorState = true;
			Z80Parser::errorString = "An invalid instruction.";
		}
		// if (Z80Parser::tList->peekTokenType() == CPU) {
			// Z80Parser::tList->pop();
			// if (Z80Parser::tList->peekTokenType() == ATOM && Z80Parser::tList->peekValue().compare("Z80") == 0) {
				// Z80Parser::tList->pop();
				// if (Z80Parser::tList->peekTokenType() == NEW_LINE) {
					// Z80Parser::tList->pop();
				// } else {
					// Z80Parser::errorState = true;
					// Z80Parser::errorString = "The CPU declarative must end with a new line after its parameter.";
				// }
			// } else {
				// Z80Parser::errorState = true;
				// Z80Parser::errorString = "The CPU declarative must only be Z80 in its parameter.";
			// }
		// } else if (Z80Parser::tList->peekTokenType() == DB) {
			// Z80Parser::tList->pop();
			// if (Z80Parser::tList->peekTokenType() == STRING) {
				// string strValue = Z80Parser::tList->peekValue();
				// Z80Parser::tList->pop();
				// while (!Z80Parser::tList->isEmpty() && !Z80Parser::errorState && Z80Parser::tList->peekTokenType() == COMMA) {
					// Z80Parser::tList->pop();
					// if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == STRING) {
						// strValue += Z80Parser::tList->peekValue();
					// } else if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NUMBER) {
						// strValue += convertNumberStringToNumber(Z80Parser::tList->peekValue());
					// } else {
						// Z80Parser::errorState = true;
						// Z80Parser::errorString = "The DB declarative can only have numbers or strings in its paramters.";
					// }
					// Z80Parser::tList->pop();
				// }
				
				// if (!Z80Parser::tList->isEmpty() && !Z80Parser::errorState && Z80Parser::tList->peekTokenType() == NEW_LINE) {
					// Z80Parser::tList->pop();
				// } else {
					// Z80Parser::errorState = true;
					// Z80Parser::errorString = "The DB declarative can only have numbers or strings in its paramters.";
				// }
			// } else if (Z80Parser::tList->peekTokenType() == NUMBER) {
				// string strValue = convertNumberStringToNumber(Z80Parser::tList->peekValue());
				// Z80Parser::tList->pop();
				// while (!Z80Parser::tList->isEmpty() && !Z80Parser::errorState && Z80Parser::tList->peekTokenType() == COMMA) {
					// Z80Parser::tList->pop();
					// if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == STRING) {
						// strValue += Z80Parser::tList->peekValue();
					// } else if (!Z80Parser::tList->isEmpty() && Z80Parser::tList->peekTokenType() == NUMBER) {
						// strValue += convertNumberStringToNumber(Z80Parser::tList->peekValue());
					// } else {
						// Z80Parser::errorState = true;
						// Z80Parser::errorString = "The DB declarative can only have numbers or strings in its paramters.";
					// }
					// Z80Parser::tList->pop();
				// }
				
				// if (!Z80Parser::tList->isEmpty() && !Z80Parser::errorState && Z80Parser::tList->peekTokenType() == NEW_LINE) {
					// Z80Parser::tList->pop();
				// } else {
					// Z80Parser::errorState = true;
					// Z80Parser::errorString = "The DB declarative can only have numbers or strings in its paramters.";
				// }
			// } else {
				// Z80Parser::errorState = true;
				// Z80Parser::errorString = "The DB declarative must have a parameter that is either a number or a string.";
			// }
		// } else if (Z80Parser::tList->peekTokenType() == ORG) {
			// Z80Parser::tList->pop();
			// if (Z80Parser::tList->peekTokenType() == NUMBER) {
				// int newAddress = convertNumberStringToNumber(Z80Parser::tList->peekValue());
				// Z80Parser::tList->pop();
				// if (Z80Parser::tList->peekTokenType() == NEW_LINE) {
					// Z80Parser::address = newAddress;
					// Z80Parser::tList->pop();
				// } else {
					// Z80Parser::errorState = true;
					// Z80Parser::errorString = "An ORG declarative must end with a new line after its number parameter";
				// }
			// } else {
				// Z80Parser::errorState = true;
				// Z80Parser::errorString = "An ORG declarative most have a number as its parameter.";
			// }
		// }
	}
	
}

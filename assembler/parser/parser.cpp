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
	date updated: 20/02/2013
	author: Gareth Richardson
	description: This is the Z80 parser. Give it a TokenList object and it will
	parse it and output the machine code for it.
*/

#include <string>

using namespace std;

#include "../lex/tokenlist.hpp"
#include "bytecode.hpp"
#include "foundlist.hpp"
#include "addresslist.hpp"
#include "parser.hpp"

void Z80Parser::init() {
	Z80Parser::tList = NULL;
	Z80Parser::bCode = NULL;
	Z80Parser::errorState = false;
	Z80Parser::errorString = "";
	Z80Parser::address = 0;
}

bool Z80Parser::checkToken(TOKEN_TYPE tok) {
	if (!Z80Parser::errorState) {
		if (!Z80Parser::tList->isEmpty()) {
			if (Z80Parser::tList->peekTokenType() != tok) {
				return false;
			} else {
				Z80Parser::tList->pop();
				return true;
			}
		} else {
			return false;
		}
	}
	return false;
}

bool Z80Parser::checkAtom(string &value) {
	if (!Z80Parser::errorState) {
		if (!Z80Parser::tList->isEmpty()) {
			if (Z80Parser::tList->peekTokenType() != ATOM) {
				return false;
			} else {
				value = Z80Parser::tList->peekValue();
				Z80Parser::tList->pop();
				return true;
			}
		}
	}
	return false;
}

bool Z80Parser::checkEightBitNumber(unsigned char &number) {
	if (!Z80Parser::errorState) {
		if (!Z80Parser::tList->isEmpty()) {
			if (Z80Parser::tList->peekTokenType() == NUMBER) {
				string value = Z80Parser::tList->peekValue();
				number = 0;
				if (value[0] == 'd') {
					if (value.length() >= 2 && value.length() <= 4) {
						int index = value.length() - 1;
						int base = 1;
						while (index > 0) {
							number += (value[index] - 48) * base;
							base *= 10;
							index--;
						}
						Z80Parser::tList->pop();
						return true;
					} else {
						return false;
					}
				} else if (value[0] == 'h') {
					if (value.length() >= 2 && value.length() <= 3) {
						int index = value.length() - 1;
						int base = 1;
						while (index > 0) {
							if (value[index] >= 'a' && value[index] <= 'f') {
								number += (value[index] - 87) * base;
							} else if (value[index] >= 'A' && value[index] <= 'F') {
								number += (value[index] - 55) * base;
							} else {
								number += (value[index] - 48) * base;
							}
							base *= 16;
							index--;
						}
						Z80Parser::tList->pop();
						return true;
					} else {
						return false;
					}
				} else if (value[0] == 'b') {
					if (value.length() >= 2 && value.length() <= 9) {
						int index = value.length() - 1;
						int base = 1;
						while (index > 0) {
							number += (value[index] - 48) * base;
							base *= 2;
							index--;
						}
						Z80Parser::tList->pop();
						return true;
					} else {
						return false;
					}
				}else {
					return false;
				}
			} else {
				return false;
			}
		} else {
			Z80Parser::errorState = true;
			Z80Parser::errorString = "Byte is out of range.";
		}
	}
	return false;
}

bool Z80Parser::checkSixteenBitNumber(unsigned short &number) {
	if (!Z80Parser::errorState) {
		if (!Z80Parser::tList->isEmpty()) {
			if (Z80Parser::tList->peekTokenType() == NUMBER) {
				number = 0;
				string value = Z80Parser::tList->peekValue();
				if (value[0] == 'd') {
					if (value.length() >= 2 && value.length() <= 6) {
						int index = value.length() - 1;
						int base = 1;
						while (index > 0) {
							number += (value[index] - 48) * base;
							base *= 10;
							index--;
						}
						Z80Parser::tList->pop();
						return true;
					} else {
						Z80Parser::errorString = "Short is out of range.";
						Z80Parser::errorState = true;
					}
				} else if (value[0] == 'h') {
					if (value.length() >= 2 && value.length() <= 5) {
						int index = value.length() - 1;
						int base = 1;
						while (index > 0) {
							if (value[index] >= 'a' && value[index] <= 'f') {
								number += (value[index] - 87) * base;
							} else if (value[index] >= 'A' && value[index] <= 'F') {
								number += (value[index] - 55) * base;
							} else {
								number += (value[index] - 48) * base;
							}
							base *= 16;
							index--;
						}
						Z80Parser::tList->pop();
						return true;
					} else {
						Z80Parser::errorString = "Short is out of range.";
						Z80Parser::errorState = true;
					}
				} else if (value[0] == 'b') {
					if (value.length() >= 2 && value.length() <= 17) {
						int index = value.length() - 1;
						int base = 1;

						while (index > 0) {
							number += (value[index] - 48) * base;
							base *= 2;
							index--;
						}
						Z80Parser::tList->pop();
						return true;
					} else {
						Z80Parser::errorString = "Short is out of range.";
						Z80Parser::errorState = true;
					}
				} else {
					Z80Parser::errorString = "Short is out of range.";
					Z80Parser::errorState = true;
				}
			}
		}
	}
	return false;
}

bool Z80Parser::checkStringToken(string &value) {
	if (!Z80Parser::errorState) {
		if (!Z80Parser::tList->isEmpty()) {
			if (Z80Parser::tList->peekTokenType() == STRING) {
				value = Z80Parser::tList->peekValue();
				Z80Parser::tList->pop();
				return true;
			}
		}
	}
	return false;
}

void Z80Parser::addCode(unsigned char byte) {
	Z80Parser::bCode->pushElement(byte);
	Z80Parser::address++;
}

void Z80Parser::addCode(unsigned char byte1, unsigned char byte2) {
	Z80Parser::bCode->pushElement(byte1);
	Z80Parser::bCode->pushElement(byte2);
	Z80Parser::address += 2;
}

void Z80Parser::addCode(unsigned char byte1, unsigned char byte2, unsigned char byte3) {
	Z80Parser::bCode->pushElement(byte1);
	Z80Parser::bCode->pushElement(byte2);
	Z80Parser::bCode->pushElement(byte3);
	Z80Parser::address += 3;
}

void Z80Parser::addAddress(string atom) {
	if (Z80Parser::fList.doesNameExist(atom)) {
		int index = 0;
		while (index < Z80Parser::fList.getSize()) {
			if (Z80Parser::fList.getName(index).compare(atom) == 0) {
				break;
			}
			index++;
		}
		unsigned short num16 = Z80Parser::fList.getAddress(index);
		Z80Parser::addCode((unsigned char) num16, (unsigned char) (num16 >> 8));
	} else {
		Z80Parser::aList.addAddress(atom, Z80Parser::address);
		Z80Parser::addCode(0x00, 0x00);
	}
}

string intToString(int value) {
	if (value == 0) {
		return "0";
	}
	
	string retValue = "";
	
	while (value > 0) {
		retValue += value % 10 + 48;
		value /= 10;
	}
	
	return retValue;
}

void Z80Parser::error(string value) {
	Z80Parser::errorState = true;
	Z80Parser::errorString = intToString(Z80Parser::tList->peekLineNumber());
	Z80Parser::errorString += "::";
	Z80Parser::errorString += value;
}

Z80Parser::Z80Parser(TokenList* tPointer, ByteCode* bPointer) {
	Z80Parser::init();
	Z80Parser::tList = tPointer;
	Z80Parser::bCode = bPointer;
}

void Z80Parser::run() {
	string strValue;
	
	while (!Z80Parser::errorState && !Z80Parser::checkToken(END_OF_FILE) && !Z80Parser::tList->isEmpty()) {
		if (Z80Parser::checkToken(DB)) {
			unsigned char retValue;
			if (Z80Parser::checkEightBitNumber(retValue)) {
				if (Z80Parser::checkToken(NEW_LINE)) {
					Z80Parser::addCode(retValue);
				} else if (Z80Parser::checkToken(COMMA)) {
					Z80Parser::addCode(retValue);
					while (!Z80Parser::errorState) {
						if (Z80Parser::checkEightBitNumber(retValue)) {
							if (Z80Parser::checkToken(NEW_LINE)) {
								Z80Parser::addCode(retValue);
								break;
							} else if (Z80Parser::checkToken(COMMA)) {
								Z80Parser::addCode(retValue);
							} else {
								Z80Parser::error("You must declare a byte array separated by commas.");
							}
						} else {
							Z80Parser::error("DB must declare a bytes.");
						}
					}
				} else {
					Z80Parser::error("DB must end with a new line.");
				}
			} else if (Z80Parser::checkStringToken(strValue)) {
				if (Z80Parser::checkToken(NEW_LINE)) {
					for (int index = 0; index < strValue.length(); index++) {
						Z80Parser::addCode((unsigned char) strValue[index]);
					}
				} else {
					Z80Parser::error("DB must end with a new line.");
				}
			} else {
				Z80Parser::error("DB must declare a byte or an array of bytes.");
			}
		} else if (Z80Parser::checkToken(DW)) {
			unsigned short retValue;
			if (Z80Parser::checkSixteenBitNumber(retValue)) {
				if (Z80Parser::checkToken(NEW_LINE)) {
					Z80Parser::addCode((unsigned char) retValue, (unsigned char) (retValue >> 8));
				} else if (Z80Parser::checkToken(COMMA)) {
					Z80Parser::addCode((unsigned char) retValue, (unsigned char) (retValue >> 8));
					while (!Z80Parser::errorState) {
						if (Z80Parser::checkSixteenBitNumber(retValue)) {
							if (Z80Parser::checkToken(NEW_LINE)) {
								Z80Parser::addCode((unsigned char) retValue, (unsigned char) (retValue >> 8));
								break;
							} else if (Z80Parser::checkToken(COMMA)) {
								Z80Parser::addCode((unsigned char) retValue, (unsigned char) (retValue >> 8));
							} else {
								Z80Parser::error("You must declare a Word array separated by commas.");
							}
						} else {
							Z80Parser::error("DW must declare a bytes.");
						}
					}
				} else {
					Z80Parser::error("DW must end with a new line.");
				}
			} else {
				Z80Parser::error("DW must declare a Word or an array of Words.");
			}
		} else if (Z80Parser::checkToken(ORG)) {
			unsigned short newAddress;
			if (Z80Parser::checkSixteenBitNumber(newAddress)) {
				if (Z80Parser::checkToken(NEW_LINE)) {
					Z80Parser::address = newAddress;
				} else {
					Z80Parser::error("ORG must end in a new line.");
				}
			} else {
				Z80Parser::error("ORG must be followed by a Word for the Address.");
			}
		} else if (Z80Parser::checkToken(REP)) {
			unsigned char count;
			unsigned char byteValue;
			unsigned short shortValue;
			if (Z80Parser::checkEightBitNumber(count)) {
				if (Z80Parser::checkToken(COMMA)) {
					if (Z80Parser::checkEightBitNumber(byteValue)) {
						//Got a byte to repeat.
						if (Z80Parser::checkToken(NEW_LINE)) {
							while (count != 0) {
								Z80Parser::addCode(byteValue);
								count--;
							}
						} else {
							Z80Parser::error("REP is two parameters then a new line.");
						}
					} else if (Z80Parser::checkSixteenBitNumber(shortValue)) {
						//Got a Short to repeat.
						if (Z80Parser::checkToken(NEW_LINE)) {
							while (count != 0) {
								Z80Parser::addCode((unsigned char) shortValue, (unsigned char) (shortValue >> 8));
								count--;
							}
						} else {
							Z80Parser::error("REP is two parameters then a new line.");
						}
					} else {
						Z80Parser::error("REP is two numeric parameters then a new line.");
					}
				} else {
					Z80Parser::error("REP is two parameters then a new line separated by a comma.");
				}
			} else {
				Z80Parser::error("REP must start with a byte that signifies how many times the value should repeat.");
			}
		} else if (Z80Parser::checkAtom(strValue)) {
			if (Z80Parser::checkToken(COLON)) {
				if (!Z80Parser::fList.doesNameExist(strValue)) {
				
					Z80Parser::fList.addAddress(strValue, Z80Parser::address);
					Z80Parser::aList.processAddress(strValue, Z80Parser::address, bCode);
				} else {
					string val = "The Address \"";
					val += strValue;
					val += "\" already exists.";
					Z80Parser::error(val);
				}
			} else {
				Z80Parser::error("An Address has to be followed by a colon.");
			}
			
		} else if (Z80Parser::checkToken(LD)) {
			Z80Parser::processLD();
		} else if (Z80Parser::checkToken(PUSH)) {
			Z80Parser::processPUSH();
		} else if (Z80Parser::checkToken(EXX)) {
			Z80Parser::addCode(0xd9);
		} else if (Z80Parser::checkToken(LDI)) {
			Z80Parser::addCode(0xed, 0xa0);
		} else if (Z80Parser::checkToken(LDIR)) {
			Z80Parser::addCode(0xed, 0xb0);
		} else if (Z80Parser::checkToken(LDD)) {
			Z80Parser::addCode(0xed, 0xa8);
		} else if (Z80Parser::checkToken(LDDR)) {
			Z80Parser::addCode(0xed, 0xb8);
		} else if (Z80Parser::checkToken(CPI)) {
			Z80Parser::addCode(0xed, 0xa1);
		} else if (Z80Parser::checkToken(CPIR)) {
			Z80Parser::addCode(0xed, 0xb1);
		} else if (Z80Parser::checkToken(CPD)) {
			Z80Parser::addCode(0xed, 0xa9);
		} else if (Z80Parser::checkToken(CPDR)) {
			Z80Parser::addCode(0xed, 0xb9);
		} else if (Z80Parser::checkToken(ADD)) {
			Z80Parser::processADD();
		} else if (Z80Parser::checkToken(ADC)) {
			Z80Parser::processADC();
		} else if (Z80Parser::checkToken(SUB)) {
			Z80Parser::processSUB();
		} else if (Z80Parser::checkToken(SUBC)) {
			Z80Parser::processSUBC();
		} else if (Z80Parser::checkToken(AND)) {
			Z80Parser::processAND();
		} else if (Z80Parser::checkToken(OR)) {
			Z80Parser::processOR();
		} else if (Z80Parser::checkToken(XOR)) {
			Z80Parser::processXOR();
		} else if (Z80Parser::checkToken(CP)) {
			Z80Parser::processCP();
		} else if (Z80Parser::checkToken(INC)) {
			Z80Parser::processINC();
		} else if (Z80Parser::checkToken(DEC)) {
			Z80Parser::processDEC();
		} else if (Z80Parser::checkToken(NEW_LINE)) {
			//Do nothing!!!!
		} else if (Z80Parser::checkToken(DAA)) {
			Z80Parser::addCode(0x27);
			if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
				Z80Parser::error("DAA instruction must end in a new line.");
			}
		} else if (Z80Parser::checkToken(CPL)) {
			Z80Parser::addCode(0x2f);
			if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
				Z80Parser::error("CPL instruction must end in a new line.");
			}
		} else if (Z80Parser::checkToken(NEG)) {
			Z80Parser::addCode(0xed, 0x44);
			if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
				Z80Parser::error("NEG instruction must end in a new line.");
			}
		} else if (Z80Parser::checkToken(CCF)) {
			Z80Parser::addCode(0x3f);
			if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
				Z80Parser::error("CCF instruction must end in a new line.");
			}
		} else if (Z80Parser::checkToken(SCF)) {
			Z80Parser::addCode(0x37);
			if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
				Z80Parser::error("SCF instruction must end in a new line.");
			}
		} else if (Z80Parser::checkToken(NOP)) {
			Z80Parser::addCode(0x00);
			if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
				Z80Parser::error("NOP instruction must end in a new line.");
			}
		} else if (Z80Parser::checkToken(HALT)) {
			Z80Parser::addCode(0x76);
			if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
				Z80Parser::error("HALT instruction must end in a new line.");
			}
		} else if (Z80Parser::checkToken(DI)) {
			Z80Parser::addCode(0xf3);
			if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
				Z80Parser::error("DI instruction must end in a new line.");
			}
		} else if (Z80Parser::checkToken(EI)) {
			Z80Parser::addCode(0xfb);
			if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
				Z80Parser::error("EI instruction must end in a new line.");
			}
		} else if (Z80Parser::checkToken(IM)) {
			unsigned char retValue;
			if (Z80Parser::checkEightBitNumber(retValue)) {
				if (retValue == 0) {
					Z80Parser::addCode(0xed, 0x46);
				} else if (retValue == 1) {
					Z80Parser::addCode(0xed, 0x56);
				} else if (retValue == 2) {
					Z80Parser::addCode(0xed, 0x5e);
				} else {
					Z80Parser::error("The IM instruction can only have a number that is either 0, 1 or 2.");
				}
			} else {
				Z80Parser::error("The IM instruction can only have a number as its parameter.");
			}
			if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
				Z80Parser::error("IM instruction must end in a new line.");
			}
		} else if (Z80Parser::checkToken(RLCA)) {
			Z80Parser::addCode(0x07);
			if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
				Z80Parser::error("EI instruction must end in a new line.");
			}
		} else if (Z80Parser::checkToken(RLA)) {
			Z80Parser::addCode(0x17);
			if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
				Z80Parser::error("EI instruction must end in a new line.");
			}
		} else if (Z80Parser::checkToken(RRCA)) {
			Z80Parser::addCode(0x0f);
			if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
				Z80Parser::error("EI instruction must end in a new line.");
			}
		} else if (Z80Parser::checkToken(RRA)) {
			Z80Parser::addCode(0x1f);
			if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
				Z80Parser::error("EI instruction must end in a new line.");
			}
		} else if (Z80Parser::checkToken(RLC)) {
			Z80Parser::processRLC();
		} else if (Z80Parser::checkToken(RL)) {
			Z80Parser::processRL();
		} else if (Z80Parser::checkToken(RRC)) {
			Z80Parser::processRRC();
		} else if (Z80Parser::checkToken(RR)) {
			Z80Parser::processRR();
		} else if (Z80Parser::checkToken(SLA)) {
			Z80Parser::processSLA();
		} else if (Z80Parser::checkToken(SRA)) {
			Z80Parser::processSRA();
		} else if (Z80Parser::checkToken(SRL)) {
			Z80Parser::processSRL();
		} else if (Z80Parser::checkToken(RLD)) {
			Z80Parser::addCode(0xed, 0x6f);
			if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
				Z80Parser::error("EI instruction must end in a new line.");
			}
		} else if (Z80Parser::checkToken(RRD)) {
			Z80Parser::addCode(0xed, 0x67);
			if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
				Z80Parser::error("EI instruction must end in a new line.");
			}
		} else if (Z80Parser::checkToken(BIT)) {
			Z80Parser::processBIT();
		} else if (Z80Parser::checkToken(SET)) {
			Z80Parser::processSET();
		} else if (Z80Parser::checkToken(RES)) {
			Z80Parser::processRES();
		} else if (Z80Parser::checkToken(JP)) {
			Z80Parser::processJP();
		} else {
			Z80Parser::error("Incorrect instruction.");
		}
		
		/*
			This is for a situation were there is a line with no instruction:
		*/
		Z80Parser::checkToken(NEW_LINE);
	}
}

bool Z80Parser::checkState() {
	return Z80Parser::errorState;
}

string Z80Parser::getError() {
	return Z80Parser::errorString;
}


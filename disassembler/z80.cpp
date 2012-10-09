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
	file name: z80.cpp
	compiled name: z80.o
	created date: 7/8/2012
	date updated: 7/8/2012
	author: Gareth Richardson
	description: the implementation of the disassembler
	method.
*/

#include <string>

using namespace std;

#include "bytefile.hpp"
#include "z80.hpp"

string convertHex(short value) {
	string retString = "";
	char hexArray[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	retString += hexArray[(int)(value >> 12)];
	retString += hexArray[(int)((value >> 8) & 0x000f)];
	retString += hexArray[(int)((value >> 4) & 0x000f)];
	retString += hexArray[(int)((value) & 0x000f)];
	return retString;
}

string convertHex(BYTE value) {
	string retString = "";
	char hexArray[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	retString += hexArray[(int)((value >> 4) & 0x000f)];
	retString += hexArray[(int)((value) & 0x000f)];
	return retString;
}

short address = 0;

string runZ80(ByteFile &obj) {
	string retString;
	BYTE value = obj.pop();
	retString = convertHex(address);
	retString += ": ";
	retString += convertHex(value);
	string temp = "";
	string temp2 = "";
	switch((unsigned char)value) {
		case 0x00:
			retString += "\t\tNOP\n";
			break;
		case 0x01:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tLD BC, [";
					retString += temp2;
					retString += temp;
					retString += "H]\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
		case 0x03:
			retString += "\t\tINC BC\n";
			break;
		case 0x04:
			retString += "\t\tINC B\n";
			break;
		case 0x05:
			retString += "\t\tDEC B\n";
			break;
		case 0x06:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\tLD B, ";
				retString += temp;
				retString += "H\n";
				address++;
			} else {
				retString += "\n";
			}
			break;
		case 0x08:
			retString += "\t\tEX AF, AF\'\n";
			break;
		case 0x09:
			retString += "\t\tADD HL, BC\n";
			break;
		case 0x0b:
			retString += "\t\tDEC BC\n";
			break;
		case 0x0c:
			retString += "\t\tINC C\n";
			break;
		case 0x0d:
			retString += "\t\tDEC C\n";
			break;
		case 0x0e:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\tLD C, ";
				retString += temp;
				retString += "H\n";
				address++;
			} else {
				retString += "\n";
			}
			break;
		case 0x10:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\t DJNZ ";
				retString += temp;
				retString += "H\n";
				address++;
			} else {
				retString += "\n";
			}
			break;
		case 0x11:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tLD DE, [";
					retString += temp2;
					retString += temp;
					retString += "H]\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
		case 0x13:
			retString += "\t\tINC DE\n";
			break;
		case 0x14:
			retString += "\t\tINC D\n";
			break;
		case 0x15:
			retString += "\t\tDEC D\n";
			break;
		case 0x16:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\tLD D, ";
				retString += temp;
				retString += "H\n";
				address++;
			} else {
				retString += "\n";
			}
			break;
		case 0x18:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\tJR ";
				retString += temp;
				retString += "H\n";
				address++;
			} else {
				retString += "\n";
			}
			break;
		case 0x19:
			retString += "\t\tADD HL, DE\n";
			break;
		case 0x1b:
			retString += "\t\tDEC DE\n";
			break;
		case 0x1c:
			retString += "\t\tINC E\n";
			break;
		case 0x1d:
			retString += "\t\tDEC E\n";
			break;
		case 0x1e:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\tLD E, ";
				retString += temp;
				retString += "H\n";
				address++;
			} else {
				retString += "\n";
			}
			break;
		case 0x20:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\tJR NZ, ";
				retString += temp;
				retString += "H\n";
				address++;
			} else {
				retString += "\n";
			}
			break;
		case 0x21:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tLD HL, [";
					retString += temp2;
					retString += temp;
					retString += "H]\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
		case 0x23:
			retString += "\t\tINC HL\n";
			break;
		case 0x24:
			retString += "\t\tINC H\n";
			break;
		case 0x25:
			retString += "\t\tDEC H\n";
			break;
		case 0x26:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\tLD H, ";
				retString += temp;
				retString += "H\n";
				address++;
			} else {
				retString += "\n";
			}
			break;
		case 0x27:
			retString += "\t\tDAA\n";
			break;
		case 0x28:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\tJR Z, ";
				retString += temp;
				retString += "H\n";
				address++;
			} else {
				retString += "\n";
			}
			break;
		case 0x29:
			retString += "\t\tADD HL, HL\n";
			break;
		case 0x2b:
			retString += "\t\tDEC HL\n";
			break;
		case 0x2c:
			retString += "\t\tINC L\n";
			break;
		case 0x2d:
			retString += "\t\tDEC L\n";
			break;
		case 0x2e:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\tLD L, ";
				retString += temp;
				retString += "H\n";
				address++;
			} else {
				retString += "\n";
			}
			break;
		case 0x2f:
			retString += "\t\tCPL\n";
			break;
		case 0x30:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\tJR NC, ";
				retString += temp;
				retString += "H\n";
				address++;
			} else {
				retString += "\n";
			}
			break;
		case 0x31:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tLD SP, [";
					retString += temp2;
					retString += temp;
					retString += "H]\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
		case 0x33:
			retString += "\t\tINC SP\n";
			break;
		case 0x34:
			retString += "\t\tINC [HL]\n"
			break;
		case 0x35:
			retString += "\t\tDEC [HL]\n";
			break;
		case 0x38:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\tJR C, ";
				retString += temp;
				retString += "H\n";
				address++;
			} else {
				retString += "\n";
			}
			break;
		case 0x39:
			retString += "\t\tADD HL, SP\n";
			break;
		case 0x3b:
			retString += "\t\tDEC SP\n";
			break;
		case 0x3c:
			retString += "\t\tINC A\n";
			break;
		case 0x3d:
			retString += "\t\tDEC A\n";
			break;
		case 0x3e:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\tLD A, ";
				retString += temp;
				retString += "H\n";
				address++;
			} else {
				retString += "\n";
			}
			break;
		case 0x3f:
			retString += "\t\tCCF\n";
			break;
		case 0x4a:
			retString += "\t\tADC HL, BC\n";
			break;
		case 0x5a:
			retString += "\t\tADC HL, DE\n";
			break;
		case 0x6a:
			retString += "\t\tADC HL, HL\n";
			break;
		case 0x76:
			retString += "\t\tHALT\n";
			break;
		case 0x7a:
			retString += "\t\tADC HL, SP\n";
			break;
		case 0x80:
			retString += "\t\tADD A, B\n";
			break;
		case 0x81:
			retString += "\t\tADD A, C\n";
			break;
		case 0x82:
			retString += "\t\tADD A, D\n";
			break;
		case 0x83:
			retString += "\t\tADD A, E\n";
			break;
		case 0x84:
			retString += "\t\tADD A, H\n";
			break;
		case 0x85:
			retString += "\t\tADD A, L\n";
			break;
		case 0x86:
			retString += "\t\tADD A, [HL]\n";
			break;
		case 0x87:
			retString += "\t\tADD A, A\n";
			break;
		case 0x88:
			retString += "\t\tADC A, B\n";
			break;
		case 0x89:
			retString += "\t\tADC A, C\n";
			break;
		case 0x8a:
			retString += "\t\tADC A, D\n";
			break;
		case 0x8b:
			retString += "\t\tADC A, E\n";
			break;
		case 0x8c:
			retString += "\t\tADC A, H\n";
			break;
		case 0x8d:
			retString += "\t\tADC A, L\n";
			break;
		case 0x8e:
			retString += "\t\tADC A, [HL]\n";
			break;
		case 0x8f:
			retString += "\t\tADC A, A\n";
			break;
		case 0xa0:
			retString += "\t\tAND A, B\n";
			break;
		case 0xa1:
			retString += "\t\tAND A, C\n";
			break;
		case 0xa2:
			retString += "\t\tAND A, D\n";
			break;
		case 0xa3:
			retString += "\t\tAND A, E\n";
			break;
		case 0xa4:
			retString += "\t\tAND A, H\n";
			break;
		case 0xa5:
			retString += "\t\tAND A, L\n";
			break;
		case 0xa6:
			retString += "\t\tAND A, [HL]\n";
			break;
		case 0xa7:
			retString += "\t\tAND A, A\n";
			break;
		case 0xb8:
			retString += "\t\tCP B\n";
			break;
		case 0xb9:
			retString += "\t\tCP C\n";
			break;
		case 0xba:
			retString += "\t\tCP D\n";
			break;
		case 0xbb:
			retString += "\t\tCP E\n";
			break;
		case 0xbc:
			retString += "\t\tCP H\n";
			break;
		case 0xbd:
			retString += "\t\tCP L\n";
			break;
		case 0xbe:
			retString += "\t\tCP [HL]\n";
			break;
		case 0xbf:
			retString += "\t\tCP A\n";
			break;
		case 0xc2:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tJP NZ, ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xc3:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tJP ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xc4:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tCALL NZ, ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
					address++;
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xc6:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\tADD A, ";
				retString += temp;
				retString += "H\n";
			} else {
				retString += '\n';
			}
			address++;
			break;
		case 0xca:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tJP Z, ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xcb:
			if (!obj.isEmpty()) {
				value = obj.pop();
				switch((unsigned char)value) {
					case 0x40:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 0, B\n";
						address++;
						break;
					case 0x41:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 0, C\n";
						address++;
						break;
					case 0x42:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 0, D\n";
						address++;
						break;
					case 0x43:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 0, E\n";
						address++;
						break;
					case 0x44:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 0, H\n";
						address++;
						break;
					case 0x45:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 0, L\n";
						address++;
						break;
					case 0x46:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 0, [HL]\n";
						address++;
						break;
					case 0x47:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 0, A\n";
						address++;
						break;
					case 0x48:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 1, B\n";
						address++;
						break;
					case 0x49:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 1, C\n";
						address++;
						break;
					case 0x4a:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 1, D\n";
						address++;
						break;
					case 0x4b:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 1, E\n";
						address++;
						break;
					case 0x4c:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 1, H\n";
						address++;
						break;
					case 0x4d:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 1, L\n";
						address++;
						break;
					case 0x4e:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 1, [HL]\n";
						address++;
						break;
					case 0x4f:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 1, A\n";
						address++;
						break;
					case 0x50:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 2, B\n";
						address++;
						break;
					case 0x51:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 2, C\n";
						address++;
						break;
					case 0x52:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 2, D\n";
						address++;
						break;
					case 0x53:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 2, E\n";
						address++;
						break;
					case 0x54:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 2, H\n";
						address++;
						break;
					case 0x55:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 2, L\n";
						address++;
						break;
					case 0x56:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 2, [HL]\n";
						address++;
						break;
					case 0x57:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 2, A\n";
						address++;
						break;
					case 0x58:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 3, B\n";
						address++;
						break;
					case 0x59:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 3, C\n";
						address++;
						break;
					case 0x5a:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 3, D\n";
						address++;
						break;
					case 0x5b:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 3, E\n";
						address++;
						break;
					case 0x5c:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 3, H\n";
						address++;
						break;
					case 0x5d:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 3, L\n";
						address++;
						break;
					case 0x5e:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 3, [HL]\n";
						address++;
						break;
					case 0x5f:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 3, A\n";
						address++;
						break;
					case 0x60:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 4, B\n";
						address++;
						break;
					case 0x61:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 4, C\n";
						address++;
						break;
					case 0x62:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 4, D\n";
						address++;
						break;
					case 0x63:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 4, E\n";
						address++;
						break;
					case 0x64:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 4, H\n";
						address++;
						break;
					case 0x65:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 4, L\n";
						address++;
						break;
					case 0x66:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 4, [HL]\n";
						address++;
						break;
					case 0x67:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 4, A\n";
						address++;
						break;
					case 0x68:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 5, B\n";
						address++;
						break;
					case 0x69:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 5, C\n";
						address++;
						break;
					case 0x6a:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 5, D\n";
						address++;
						break;
					case 0x6b:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 5, E\n";
						address++;
						break;
					case 0x6c:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 5, H\n";
						address++;
						break;
					case 0x6d:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 5, L\n";
						address++;
						break;
					case 0x6e:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 5, [HL]\n";
						address++;
						break;
					case 0x6f:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 5, A\n";
						address++;
						break;
					case 0x70:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 6, B\n";
						address++;
						break;
					case 0x71:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 6, C\n";
						address++;
						break;
					case 0x72:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 6, D\n";
						address++;
						break;
					case 0x73:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 6, E\n";
						address++;
						break;
					case 0x74:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 6, H\n";
						address++;
						break;
					case 0x75:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 6, L\n";
						address++;
						break;
					case 0x76:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 6, [HL]\n";
						address++;
						break;
					case 0x77:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 6, A\n";
						address++;
						break;
					case 0x78:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 7, B\n";
						address++;
						break;
					case 0x79:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 7, C\n";
						address++;
						break;
					case 0x7a:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 7, D\n";
						address++;
						break;
					case 0x7b:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 7, E\n";
						address++;
						break;
					case 0x7c:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 7, H\n";
						address++;
						break;
					case 0x7d:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 7, L\n";
						address++;
						break;
					case 0x7e:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 7, [HL]\n";
						address++;
						break;
					case 0x7f:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tBIT 7, A\n";
						address++;
						break;
					default:
						retString += " ";
						retString += convertHex(value);
						retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xcc:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tCALL Z, ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xcd:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tCALL ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xce:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\tADC A, ";
				retString += temp;
				retString += "H\n";
			} else {
				retString += '\n';
			}
			address++;
			break;
		case 0xd2:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tJP NC, ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xd4:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tCALL NC, ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xd9:
			retString += "\t\tEXX\n";
			break;
		case 0xda:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tJP C, ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xdb:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\tIN A, [";
				retString += temp;
				retString += "]\n";
			} else {
				retString += "\n";
			}
			address++;
			break;
		case 0xdc:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tCALL C, ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xdd:
			if (!obj.isEmpty()) {
				value = obj.pop();
				retString += " ";
				address++;
				if (!obj.isEmpty()) {
					switch ((unsigned char)value) {
						case 0x09:
							retString += convertHex(value);
							retString += "\t\tADD IX, BC\n";
							break;
						case 0x19:
							retString += convertHex(value);
							retString += "\t\tADD IX, DE\n";
							break;
						case 0x23:
							retString += convertHex(value);
							retString += "\t\tINC IX\n";
							break;
						case 0x29:
							retString += convertHex(value);
							retString += "\t\tADD IX, IX\n";
							break;
						case 0x2b:
							retString += convertHex(value);
							retString += "\t\tDEC IX\n";
							break;
						case 0x34:
							retString += convertHex(value);
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tINC [IX + ";
							retString += temp;
							retString += "H]\n";
							address++;
						case 0x35:
							retString += convertHex(value);
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tDEC [IX + ";
							retString += temp;
							retString += "H]\n";
							address++;
						case 0x39:
							retString += "39\t\tADD IX, SP\n";
							break;
						case 0x86:
							value = obj.pop();
							temp = convertHex(value);
							retString += "86";
							retString += temp;
							retString += "\t\tADD A, [IX + ";
							retString += temp;
							retString += "H]\n";
							address++;
							break;
						case 0x8e:
							value = obj.pop();
							temp = convertHex(value);
							retString += "8E";
							retString += temp;
							retString += "\t\tADC A, [IX + ";
							retString += temp;
							retString += "H]\n";
							address++;
							break;
						case 0xa6:
							value = obj.pop();
							temp = convertHex(value);
							retString += "A6";
							retString += temp;
							retString += "\t\tAND A, [IX + ";
							retString += temp;
							retString += "]\n";
							address++;
							break;
						case 0xcb:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += "CB";
							retString += temp;
							value = obj.pop();
							address++;
							switch ((unsigned char)value) {
								case 0x46:
									retString += " ";
									retString += convertHex(value);
									retString += "\t\tBIT 0, [IX + ";
									retString += temp;
									retString += "]\n";
									address++;
									break;
								case 0x4e:
									retString += " ";
									retString += convertHex(value);
									retString += "\t\tBIT 1, [IX + ";
									retString += temp;
									retString += "]\n";
									address++;
									break;
								case 0x56:
									retString += " ";
									retString += convertHex(value);
									retString += "\t\tBIT 2, [IX + ";
									retString += temp;
									retString += "]\n";
									address++;
									break;
								case 0x5e:
									retString += " ";
									retString += convertHex(value);
									retString += "\t\tBIT 3, [IX + ";
									retString += temp;
									retString += "]\n";
									address++;
									break;
								case 0x66:
									retString += " ";
									retString += convertHex(value);
									retString += "\t\tBIT 4, [IX + ";
									retString += temp;
									retString += "]\n";
									address++;
									break;
								case 0x6e:
									retString += " ";
									retString += convertHex(value);
									retString += "\t\tBIT 5, [IX + ";
									retString += temp;
									retString += "]\n";
									address++;
									break;
								case 0x76:
									retString += " ";
									retString += convertHex(value);
									retString += "\t\tBIT 6, [IX + ";
									retString += temp;
									retString += "]\n";
									address++;
									break;
								case 0x7e:
									retString += " ";
									retString += convertHex(value);
									retString += "\t\tBIT 7, [IX + ";
									retString += temp;
									retString += "]\n";
									address++;
									break;
								default:
									retString += " ";
									retString += convertHex(value);
							}
						case 0xbe:
							if (!obj.isEmpty()) {
								retString += " ";
								retString += convertHex(value);
								if (!obj.isEmpty()) {
									retString += " ";
									value = obj.pop();
									temp = convertHex(value);
									retString += temp;
									retString += "\t\tCP [IX + ";
									retString += temp;
									retString += "H]\n";
									address += 2;
								} else {
									retString += "\n";
								}
							} else {
								retString += "\n";
							}
							break;
						case 0xe3:
							retString += " E3\t\tEX [SP], IX\n";
							break;
						case 0xe9:
							retString += "\t\tJP [IX]\n";
							break;
						default:
							retString += "\n";
					}
				} else {
					retString += convertHex(value);
					retString += '\n';
				}
				address++;
			} else {
				retString += '\n';
			}
			break;
		case 0xe2:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tJP P0, ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xe3:
			retString += "\t\tEX [SP], HL\n";
			break;
		case 0xe4:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tCALL P0, ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xe6:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString = " ";
				retString += temp;
				retString += "\t\tAND A, ";
				retString += temp;
				retString += "H\n";
				address++;
			} else {
				retString += '\n';
			}
			break;
		case 0xe9:
			retString += "\t\tJP [HL]\n";
			break;
		case 0xea:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tJP PE, ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xeb:
			retString += "\t\tEX DE, HL\n";
			break;
		case 0xec:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tCALL PE, ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xed:
			if (!obj.isEmpty()) {
				value = obj.pop();
				switch ((unsigned char)value) {
					case 0x40:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tIN B, [C]\n";
						break;
					case 0x46:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tIM 0\n";
						break;
					case 0x48:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tIN C, [C]\n";
						break;
					case 0x4b:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							address++;
							if (!obj.isEmpty()) {
								address++;
								value = obj.pop();
								retString += " ";
								retString += temp2;
								retString += "\t\tLD BC, [";
								retString += temp2;
								retString += temp;
								retString += "H]\n";
							} else {
								retString += "\n";
							}
						} else {
							retString += "\n";
						}
					case 0x50:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tIN D, [C]\n";
						break;
					case 0x56:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tIM 1\n";
						break;
					case 0x58:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tIN E, [C]\n";
						break;
					case 0x5b:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							address++;
							if (!obj.isEmpty()) {
								address++;
								value = obj.pop();
								retString += " ";
								retString += temp2;
								retString += "\t\tLD DE, [";
								retString += temp2;
								retString += temp;
								retString += "H]\n";
							} else {
								retString += "\n";
							}
						} else {
							retString += "\n";
						}
					case 0x5e:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tIM 2\n";
						break;
					case 0x60:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tIN H, [C]\n";
						break;
					case 0x68:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tIN L, [C]\n";
						break;
					case 0x6b:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							address++;
							if (!obj.isEmpty()) {
								address++;
								value = obj.pop();
								retString += " ";
								retString += temp2;
								retString += "\t\tLD HL, [";
								retString += temp2;
								retString += temp;
								retString += "H]\n";
							} else {
								retString += "\n";
							}
						} else {
							retString += "\n";
						}
					case 0x78:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tIN A, [C]\n";
						break;
					case 0x7b:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							address++;
							if (!obj.isEmpty()) {
								address++;
								value = obj.pop();
								retString += " ";
								retString += temp2;
								retString += "\t\tLD SP, [";
								retString += temp2;
								retString += temp;
								retString += "H]\n";
							} else {
								retString += "\n";
							}
						} else {
							retString += "\n";
						}
					case 0xa1:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tCPI\n";
						break;
					case 0xa2:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tINI\n";
						break;
					case 0xa9:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tCPD\n";
						break;
					case 0xaa:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tIND\n"
						break;
					case 0xb1:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tCPIR\n";
						break;
					case 0xb2:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tINIR\n";
						break;
					case 0xb9:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tCPDR\n";
						break;
					case 0xba:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tINDR\n";
						break;
					default:
						retString += " ";
						retString += convertHex(value);
						retString += "\n";
				}
				address++;
			} else {
				retString += "\n";
			}
			break;
		case 0xf2:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tJP P, ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xf3:
			retString += "\t\tDI\n";
			break;
		case 0xf4:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tCALL P, ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xfa:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tJP M, ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xfb:
			retString += "\t\tEI\n";
			break;
		case 0xfc:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					retString += " ";
					retString += temp2;
					retString += "\t\tCALL M, ";
					retString += temp2;
					retString += temp;
					retString += "H\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0xfd:
			if (!obj.isEmpty()) {
				value = obj.pop();
				retString += " ";
				if (!obj.isEmpty()) {
					switch ((unsigned char)value) {
						case 0x09:
							retString += "\t\tADD IY, BC\n";
							break;
						case 0x19:
							retString += "\t\tADD IY, DE\n";
							break;
						case 0x23:
							retString += convertHex(value);
							retString += "\t\tINC IY\n";
							break;
						case 0x29:
							retString += "\t\tADD IY, IY\n";
							break;
						case 0x2b:
							retString += "\t\tDEC IY\n";
							break;
						case 0x34:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tINC [IY + ";
							retString += temp;
							retString += "H]\n";
							address += 2;
						case 0x35:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tDEC [IY + ";
							retString += temp;
							retString += "H]\n";
							address += 2;
						case 0x39:
							retString += "\t\tADD IY, SP\n";
							break;
						case 0x86:
							value = obj.pop();
							temp = convertHex(value);
							retString += "8E";
							retString += temp;
							retString += "\t\tADD A, [IY + ";
							retString += temp;
							retString += "H]\n";
							break;
						case 0x8e:
							value = obj.pop();
							temp = convertHex(value);
							retString += "8E";
							retString += temp;
							retString += "\t\tADC A, [IY + ";
							retString += temp;
							retString += "H]\n";
							break;
						case 0xa6:
							value = obj.pop();
							temp = convertHex(value);
							retString += "A6";
							retString += temp;
							retString += "\t\tAND A, [IY + ";
							retString += temp;
							retString += "]\n";
							break;
						case 0xbe:
							if (!obj.isEmpty()) {
								retString += " ";
								retString += convertHex(value);
								if (!obj.isEmpty()) {
									retString += " ";
									value = obj.pop();
									temp = convertHex(value);
									retString += temp;
									retString += "\t\tCP [IY + ";
									retString += temp;
									retString += "H]\n";
									address += 2;
								} else {
									retString += "\n";
								}
							} else {
								retString += "\n";
							}
							break;
						case 0xcb:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += "CB";
							retString += temp;
							value = obj.pop();
							switch ((unsigned char)value) {
								case 0x46:
									retString += " ";
									retString += convertHex(value);
									retString += "\t\tBIT 0, [IY + ";
									retString += temp;
									retString += "]\n";
									break;
								case 0x4e:
									retString += " ";
									retString += convertHex(value);
									retString += "\t\tBIT 1, [IY + ";
									retString += temp;
									retString += "]\n";
									break;
								case 0x56:
									retString += " ";
									retString += convertHex(value);
									retString += "\t\tBIT 2, [IY + ";
									retString += temp;
									retString += "]\n";
									break;
								case 0x5e:
									retString += " ";
									retString += convertHex(value);
									retString += "\t\tBIT 3, [IY + ";
									retString += temp;
									retString += "]\n";
									break;
								case 0x66:
									retString += " ";
									retString += convertHex(value);
									retString += "\t\tBIT 4, [IY + ";
									retString += temp;
									retString += "]\n";
									break;
								case 0x6e:
									retString += " ";
									retString += convertHex(value);
									retString += "\t\tBIT 5, [IY + ";
									retString += temp;
									retString += "]\n";
									break;
								case 0x76:
									retString += " ";
									retString += convertHex(value);
									retString += "\t\tBIT 6, [IY + ";
									retString += temp;
									retString += "]\n";
									break;
								case 0x7e:
									retString += " ";
									retString += convertHex(value);
									retString += "\t\tBIT 7, [IY + ";
									retString += temp;
									retString += "]\n";
									break;
								default:
									retString += " ";
									retString += convertHex(value);
							}
							break;
						case 0xe9:
							retString += "\t\tJP [IY]\n";
							break;
						case 0xe3:
							retString += " E3\t\tEX [SP], IY\n";
							break;
						default:
							retString += "\n";
							retString += runZ80(obj);
					}
				} else {
					retString += convertHex(value);
					retString += '\n';
				}
			} else {
				retString += '\n';
			}
			
			address += 2;
			break;
		case 0xfe:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\tCP ";
				retString += temp;
				retString += "H\n";
			} else {
				retString += "\n";
			}
		default:
			retString += '\n';
	}
	address++;
	return retString;
}

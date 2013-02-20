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
	date updated: 21/02/2013
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

/*
	put this into the header, so we can alter its value when needed.
*/
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
					temp2 = convertHex(value);
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
			break;
		case 0x02:
			retString += "\t\tLD [BC], A\n";
			break;
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
		case 0x0a:
			retString += "\t\tLD A, [BC]\n";
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
				retString += "\t\tDJNZ ";
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
					temp2 += convertHex(value);
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
			break;
		case 0x12:
			retString += "\t\tLD [DE], A\n";
			break;
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
		case 0x1a:
			retString += "\t\tLD A, [DE]\n";
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
					temp2 += convertHex(value);
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
			break;
		case 0x22:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					temp2 += convertHex(value);
					retString += " ";
					retString += temp2;
					retString += "\t\tLD [";
					retString += temp2;
					retString += temp;
					retString += "H], HL\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
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
		case 0x2a:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					temp2 += convertHex(value);
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
					temp2 += convertHex(value);
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
			break;
		case 0x32:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					temp2 += convertHex(value);
					retString += " ";
					retString += temp2;
					retString += "\t\tLD [";
					retString += temp2;
					retString += temp;
					retString += "H], A\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
			break;
		case 0x33:
			retString += "\t\tINC SP\n";
			break;
		case 0x34:
			retString += "\t\tINC [HL]\n";
			break;
		case 0x35:
			retString += "\t\tDEC [HL]\n";
			break;
		case 0x36:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				retString += "\t\tLD [HL], ";
				retString += temp;
				retString += "H\n";
				address++;
			} else {
				retString += "\n";
			}
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
		case 0x3a:
			if (!obj.isEmpty()) {
				value = obj.pop();
				temp = convertHex(value);
				retString += " ";
				retString += temp;
				address++;
				if (!obj.isEmpty()) {
					address++;
					value = obj.pop();
					temp2 = convertHex(value);
					retString += " ";
					retString += temp2;
					retString += "\t\tLD A, [";
					retString += temp2;
					retString += temp;
					retString += "H]\n";
				} else {
					retString += "\n";
				}
			} else {
				retString += "\n";
			}
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
		case 0x40:
			retString += "\t\tLD B, B\n";
			break;
		case 0x41:
			retString += "\t\tLD B, C\n";
			break;
		case 0x42:
			retString += "\t\tLD B, D\n";
			break;
		case 0x43:
			retString += "\t\tLD B, E\n";
			break;
		case 0x44:
			retString += "\t\tLD B, H\n";
			break;
		case 0x45:
			retString += "\t\tLD B, L\n";
			break;
		case 0x46:
			retString += "\t\tLD B, [HL]\n";
			break;
		case 0x47:
			retString += "\t\tLD B, A\n";
			break;
		case 0x48:
			retString += "\t\tLD C, B\n";
			break;
		case 0x49:
			retString += "\t\tLD C, C\n";
			break;
		case 0x4a:
			retString += "\t\tLD C, D\n";
			break;
		case 0x4b:
			retString += "\t\tLD C, E\n";
			break;
		case 0x4c:
			retString += "\t\tLD C, H\n";
			break;
		case 0x4d:
			retString += "\t\tLD C, L\n";
			break;
		case 0x4e:
			retString += "\t\tLD C, [HL]\n";
			break;
		case 0x4f:
			retString += "\t\tLD C, A\n";
			break;
		case 0x50:
			retString += "\t\tLD D, B\n";
			break;
		case 0x51:
			retString += "\t\tLD D, C\n";
			break;
		case 0x52:
			retString += "\t\tLD D, D\n";
			break;
		case 0x53:
			retString += "\t\tLD D, E\n";
			break;
		case 0x54:
			retString += "\t\tLD D, H\n";
			break;
		case 0x55:
			retString += "\t\tLD D, L\n";
			break;
		case 0x56:
			retString += "\t\tLD D, [HL]\n";
			break;
		case 0x57:
			retString += "\t\tLD D, A\n";
			break;
		case 0x58:
			retString += "\t\tLD E, B\n";
			break;
		case 0x59:
			retString += "\t\tLD E, B\n";
			break;
		case 0x5a:
			retString += "\t\tLD E, B\n";
			break;
		case 0x5b:
			retString += "\t\tLD E, B\n";
			break;
		case 0x5c:
			retString += "\t\tLD E, B\n";
			break;
		case 0x5d:
			retString += "\t\tLD E, B\n";
			break;
		case 0x5e:
			retString += "\t\tLD E, [HL]\n";
			break;
		case 0x5f:
			retString += "\t\tLD E, A\n";
			break;
		case 0x60:
			retString += "\t\tLD H, B\n";
			break;
		case 0x61:
			retString += "\t\tLD H, C\n";
			break;
		case 0x62:
			retString += "\t\tLD H, D\n";
			break;
		case 0x63:
			retString += "\t\tLD H, E\n";
			break;
		case 0x64:
			retString += "\t\tLD H, H\n";
			break;
		case 0x65:
			retString += "\t\tLD H, L\n";
			break;
		case 0x66:
			retString += "\t\tLD H, [HL]\n";
			break;
		case 0x67:
			retString += "\t\tLD H, A\n";
			break;
		case 0x68:
			retString += "\t\tLD L, B\n";
			break;
		case 0x69:
			retString += "\t\tLD L, C\n";
			break;
		case 0x6a:
			retString += "\t\tLD L, D\n";
			break;
		case 0x6b:
			retString += "\t\tLD L, E\n";
			break;
		case 0x6c:
			retString += "\t\tLD L, H\n";
			break;
		case 0x6d:
			retString += "\t\tLD L, L\n";
			break;
		case 0x6e:
			retString += "\t\tLD L, [HL]\n";
			break;
		case 0x6f:
			retString += "\t\tLD L, A\n";
			break;
		case 0x70:
			retString += "\t\tLD [HL], B\n";
			break;
		case 0x71:
			retString += "\t\tLD [HL], C\n";
			break;
		case 0x72:
			retString += "\t\tLD [HL], D\n";
			break;
		case 0x73:
			retString += "\t\tLD [HL], E\n";
			break;
		case 0x74:
			retString += "\t\tLD [HL], H\n";
			break;
		case 0x75:
			retString += "\t\tLD [HL], L\n";
			break;
		case 0x76:
			retString += "\t\tHALT\n";
			break;
		case 0x77:
			retString += "\t\tLD [HL], A\n";
			break;
		case 0x78:
			retString += "\t\tLD A, B\n";
			break;
		case 0x79:
			retString += "\t\tLD A, C\n";
			break;
		case 0x7a:
			retString += "\t\tLD A, D\n";
			break;
		case 0x7b:
			retString += "\t\tLD A, E\n";
			break;
		case 0x7c:
			retString += "\t\tLD A, H\n";
			break;
		case 0x7d:
			retString += "\t\tLD A, L\n";
			break;
		case 0x7e:
			retString += "\t\tLD A, [HL]\n";
			break;
		case 0x7f:
			retString += "\t\tLD A, A\n";
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
		case 0xb0:
			retString += "\t\tOR A, B\n";
			break;
		case 0xb1:
			retString += "\t\tOR A, C\n";
			break;
		case 0xb2:
			retString += "\t\tOR A, D\n";
			break;
		case 0xb3:
			retString += "\t\tOR A, E\n";
			break;
		case 0xb4:
			retString += "\t\tOR A, H\n";
			break;
		case 0xb5:
			retString += "\t\tOR A, L\n";
			break;
		case 0xb6:
			retString += "\t\tOR A, [HL]\n";
			break;
		case 0xb7:
			retString += "\t\tOR A, A\n";
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
		case 0xc0:
			retString += "\t\tRET NZ\n";
			break;
		case 0xc1:
			retString += "\t\tPOP BC\n";
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
					temp2 = convertHex(value);
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
					temp2 = convertHex(value);
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
					temp2 = convertHex(value);
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
		case 0xc5:
			retString += "\t\tPUSH BC\n";
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
		case 0xc8:
			retString += "\t\tRET Z\n";
			break;
		case 0xc9:
			retString += "\t\tRET\n";
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
					temp2 = convertHex(value);
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
				retString += " ";
				retString += convertHex(value);
				address++;
				switch((unsigned char)value) {
					case 0x10:
						retString += "\t\tRL B\n";
						break;
					case 0x11:
						retString += "\t\tRL C\n";
						break;
					case 0x12:
						retString += "\t\tRL D\n";
						break;
					case 0x13:
						retString += "\t\tRL E\n";
						break;
					case 0x14:
						retString += "\t\tRL H\n";
						break;
					case 0x15:
						retString += "\t\tRL L\n";
						break;
					case 0x16:
						retString += "\t\tRL [HL]\n";
						break;
					case 0x17:
						retString += "\t\tRL A\n";
						break;
					case 0x40:
						retString += "\t\tBIT 0, B\n";
						break;
					case 0x41:
						retString += "\t\tBIT 0, C\n";
						break;
					case 0x42:
						retString += "\t\tBIT 0, D\n";
						break;
					case 0x43:
						retString += "\t\tBIT 0, E\n";
						break;
					case 0x44:
						retString += "\t\tBIT 0, H\n";
						break;
					case 0x45:
						retString += "\t\tBIT 0, L\n";
						break;
					case 0x46:
						retString += "\t\tBIT 0, [HL]\n";
						break;
					case 0x47:
						retString += "\t\tBIT 0, A\n";
						break;
					case 0x48:
						retString += "\t\tBIT 1, B\n";
						break;
					case 0x49:
						retString += "\t\tBIT 1, C\n";
						break;
					case 0x4a:
						retString += "\t\tBIT 1, D\n";
						break;
					case 0x4b:
						retString += "\t\tBIT 1, E\n";
						break;
					case 0x4c:
						retString += "\t\tBIT 1, H\n";
						break;
					case 0x4d:
						retString += "\t\tBIT 1, L\n";
						break;
					case 0x4e:
						retString += "\t\tBIT 1, [HL]\n";
						break;
					case 0x4f:
						retString += "\t\tBIT 1, A\n";
						break;
					case 0x50:
						retString += "\t\tBIT 2, B\n";
						break;
					case 0x51:
						retString += "\t\tBIT 2, C\n";
						break;
					case 0x52:
						retString += "\t\tBIT 2, D\n";
						break;
					case 0x53:
						retString += "\t\tBIT 2, E\n";
						break;
					case 0x54:
						retString += "\t\tBIT 2, H\n";
						break;
					case 0x55:
						retString += "\t\tBIT 2, L\n";
						break;
					case 0x56:
						retString += "\t\tBIT 2, [HL]\n";
						break;
					case 0x57:
						retString += "\t\tBIT 2, A\n";
						break;
					case 0x58:
						retString += "\t\tBIT 3, B\n";
						break;
					case 0x59:
						retString += "\t\tBIT 3, C\n";
						break;
					case 0x5a:
						retString += "\t\tBIT 3, D\n";
						break;
					case 0x5b:
						retString += "\t\tBIT 3, E\n";
						break;
					case 0x5c:
						retString += "\t\tBIT 3, H\n";
						break;
					case 0x5d:
						retString += "\t\tBIT 3, L\n";
						break;
					case 0x5e:
						retString += "\t\tBIT 3, [HL]\n";
						break;
					case 0x5f:
						retString += "\t\tBIT 3, A\n";
						break;
					case 0x60:
						retString += "\t\tBIT 4, B\n";
						break;
					case 0x61:
						retString += "\t\tBIT 4, C\n";
						break;
					case 0x62:
						retString += "\t\tBIT 4, D\n";
						break;
					case 0x63:
						retString += "\t\tBIT 4, E\n";
						break;
					case 0x64:
						retString += "\t\tBIT 4, H\n";
						break;
					case 0x65:
						retString += "\t\tBIT 4, L\n";
						break;
					case 0x66:
						retString += "\t\tBIT 4, [HL]\n";
						break;
					case 0x67:
						retString += "\t\tBIT 4, A\n";
						break;
					case 0x68:
						retString += "\t\tBIT 5, B\n";
						break;
					case 0x69:
						retString += "\t\tBIT 5, C\n";
						break;
					case 0x6a:
						retString += "\t\tBIT 5, D\n";
						break;
					case 0x6b:
						retString += "\t\tBIT 5, E\n";
						break;
					case 0x6c:
						retString += "\t\tBIT 5, H\n";
						break;
					case 0x6d:
						retString += "\t\tBIT 5, L\n";
						break;
					case 0x6e:
						retString += "\t\tBIT 5, [HL]\n";
						break;
					case 0x6f:
						retString += "\t\tBIT 5, A\n";
						break;
					case 0x70:
						retString += "\t\tBIT 6, B\n";
						break;
					case 0x71:
						retString += "\t\tBIT 6, C\n";
						break;
					case 0x72:
						retString += "\t\tBIT 6, D\n";
						break;
					case 0x73:
						retString += "\t\tBIT 6, E\n";
						break;
					case 0x74:
						retString += "\t\tBIT 6, H\n";
						break;
					case 0x75:
						retString += "\t\tBIT 6, L\n";
						break;
					case 0x76:
						retString += "\t\tBIT 6, [HL]\n";
						break;
					case 0x77:
						retString += "\t\tBIT 6, A\n";
						break;
					case 0x78:
						retString += "\t\tBIT 7, B\n";
						break;
					case 0x79:
						retString += "\t\tBIT 7, C\n";
						break;
					case 0x7a:
						retString += "\t\tBIT 7, D\n";
						break;
					case 0x7b:
						retString += "\t\tBIT 7, E\n";
						break;
					case 0x7c:
						retString += "\t\tBIT 7, H\n";
						break;
					case 0x7d:
						retString += "\t\tBIT 7, L\n";
						break;
					case 0x7e:
						retString += "\t\tBIT 7, [HL]\n";
						break;
					case 0x7f:
						retString += "\t\tBIT 7, A\n";
						break;
					case 0x80:
						retString += "\t\tRES 0, B\n";
						break;
					case 0x81:
						retString += "\t\tRES 0, C\n";
						break;
					case 0x82:
						retString += "\t\tRES 0, D\n";
						break;
					case 0x83:
						retString += "\t\tRES 0, E\n";
						break;
					case 0x84:
						retString += "\t\tRES 0, H\n";
						break;
					case 0x85:
						retString += "\t\tRES 0, L\n";
						break;
					case 0x86:
						retString += "\t\tRES 0, [HL]\n";
						break;
					case 0x87:
						retString += "\t\tRES 0, A\n";
						break;
					case 0x88:
						retString += "\t\tRES 1, B\n";
						break;
					case 0x89:
						retString += "\t\tRES 1, C\n";
						break;
					case 0x8a:
						retString += "\t\tRES 1, D\n";
						break;
					case 0x8b:
						retString += "\t\tRES 1, E\n";
						break;
					case 0x8c:
						retString += "\t\tRES 1, H\n";
						break;
					case 0x8d:
						retString += "\t\tRES 1, L\n";
						break;
					case 0x8e:
						retString += "\t\tRES 1, [HL]\n";
						break;
					case 0x8f:
						retString += "\t\tRES 1, A\n";
						break;
					case 0x90:
						retString += "\t\tRES 2, B\n";
						break;
					case 0x91:
						retString += "\t\tRES 2, C\n";
						break;
					case 0x92:
						retString += "\t\tRES 2, D\n";
						break;
					case 0x93:
						retString += "\t\tRES 2, E\n";
						break;
					case 0x94:
						retString += "\t\tRES 2, H\n";
						break;
					case 0x95:
						retString += "\t\tRES 2, L\n";
						break;
					case 0x96:
						retString += "\t\tRES 2, [HL]\n";
						break;
					case 0x97:
						retString += "\t\tRES 2, A\n";
						break;
					case 0x98:
						retString += "\t\tRES 3, B\n";
						break;
					case 0x99:
						retString += "\t\tRES 3, C\n";
						break;
					case 0x9a:
						retString += "\t\tRES 3, D\n";
						break;
					case 0x9b:
						retString += "\t\tRES 3, E\n";
						break;
					case 0x9c:
						retString += "\t\tRES 3, H\n";
						break;
					case 0x9d:
						retString += "\t\tRES 3, L\n";
						break;
					case 0x9e:
						retString += "\t\tRES 3, [HL]\n";
						break;
					case 0x9f:
						retString += "\t\tRES 3, A\n";
						break;
					case 0xa0:
						retString += "\t\tRES 4, B\n";
						break;
					case 0xa1:
						retString += "\t\tRES 4, C\n";
						break;
					case 0xa2:
						retString += "\t\tRES 4, D\n";
						break;
					case 0xa3:
						retString += "\t\tRES 4 E\n";
						break;
					case 0xa4:
						retString += "\t\tRES 4, H\n";
						break;
					case 0xa5:
						retString += "\t\tRES 4, L\n";
						break;
					case 0xa6:
						retString += "\t\tRES 4, [HL]\n";
						break;
					case 0xa7:
						retString += "\t\tRES 4, A\n";
						break;
					case 0xa8:
						retString += "\t\tRES 5, B\n";
						break;
					case 0xa9:
						retString += "\t\tRES 5, C\n";
						break;
					case 0xaa:
						retString += "\t\tRES 5, D\n";
						break;
					case 0xab:
						retString += "\t\tRES 5, E\n";
						break;
					case 0xac:
						retString += "\t\tRES 5, H\n";
						break;
					case 0xad:
						retString += "\t\tRES 5, L\n";
						break;
					case 0xae:
						retString += "\t\tRES 5, [HL]\n";
						break;
					case 0xaf:
						retString += "\t\tRES 5, A\n";
						break;
					case 0xb0:
						retString += "\t\tRES 6, B\n";
						break;
					case 0xb1:
						retString += "\t\tRES 6, C\n";
						break;
					case 0xb2:
						retString += "\t\tRES 6, D\n";
						break;
					case 0xb3:
						retString += "\t\tRES 6, E\n";
						break;
					case 0xb4:
						retString += "\t\tRES 6, H\n";
						break;
					case 0xb5:
						retString += "\t\tRES 6, L\n";
						break;
					case 0xb6:
						retString += "\t\tRES 6, [HL]\n";
						break;
					case 0xb7:
						retString += "\t\tRES 6, A\n";
						break;
					case 0xb8:
						retString += "\t\tRES 7, B\n";
						break;
					case 0xb9:
						retString += "\t\tRES 7, C\n";
						break;
					case 0xba:
						retString += "\t\tRES 7, D\n";
						break;
					case 0xbb:
						retString += "\t\tRES 7, E\n";
						break;
					case 0xbc:
						retString += "\t\tRES 7, H\n";
						break;
					case 0xbd:
						retString += "\t\tRES 7, L\n";
						break;
					case 0xbe:
						retString += "\t\tRES 7, [HL]\n";
						break;
					case 0xbf:
						retString += "\t\tRES 7, A\n";
						break;
					default:
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
					temp2 = convertHex(value);
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
					temp2 = convertHex(value);
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
		case 0xd0:
			retString += "\t\tRET NC\n";
			break;
		case 0xd1:
			retString += "\t\tPOP DE\n";
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
					temp2 = convertHex(value);
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
		case 0xd3:
			if (!obj.isEmpty()) {
				value = obj.pop();
				retString += " ";
				retString += convertHex(value);
				retString += "\t\tOUT [";
				retString += convertHex(value);
				retString += "H], A\n";
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
					convertHex(value);
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
		case 0xd5:
			retString += "\t\tPUSH DE\n";
			break;
		case 0xd8:
			retString += "\t\tRET C\n";
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
					convertHex(value);
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
				retString += "H]\n";
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
					temp2 = convertHex(value);
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
				retString += convertHex(value);
				address++;
				switch ((unsigned char)value) {
					case 0x09:
						retString += "\t\tADD IX, BC\n";
						break;
					case 0x19:
						retString += "\t\tADD IX, DE\n";
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
								temp2 = convertHex(value);
								retString += " ";
								retString += temp2;
								retString += "\tLD IX, ";
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
					case 0x22:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							address++;
							if (!obj.isEmpty()) {
								address++;
								value = obj.pop();
								temp2 = convertHex(value);
								retString += " ";
								retString += temp2;
								retString += "\tLD [";
								retString += temp2;
								retString += temp;
								retString += "H], IX\n";
							} else {
								retString += "\n";
							}
						} else {
							retString += "\n";
						}
						break;
					case 0x23:
						retString += "\t\tINC IX\n";
						break;
					case 0x29:
						retString += "\t\tADD IX, IX\n";
						break;
					case 0x2a:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							address++;
							if (!obj.isEmpty()) {
								address++;
								value = obj.pop();
								temp2 = convertHex(value);
								retString += " ";
								retString += temp2;
								retString += "\tLD IX, [";
								retString += temp2;
								retString += temp;
								retString += "H]\n";
							} else {
								retString += "\n";
							}
						} else {
							retString += "\n";
						}
						break;
					case 0x2b:
						retString += "\t\tDEC IX\n";
						break;
					case 0x34:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tINC [IX + ";
							retString += temp;
							retString += "H]\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0x35:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tDEC [IX + ";
							retString += temp;
							retString += "H]\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0x36:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							address++;
							if (!obj.isEmpty()) {
								address++;
								value = obj.pop();
								temp2 = convertHex(value);
								retString += " ";
								retString += temp2;
								retString += "\t\tLD [IX + ";
								retString += temp;
								retString += "H], ";
								retString += temp2;
								retString += "H\n";
							} else {
								retString += "\n";
							}
						} else {
							retString += "\n";
						}
						break;
					case 0x39:
						retString += "\t\tADD IX, SP\n";
						break;
					case 0x46:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD B, [IX + ";
							retString += temp;
							retString += "H]\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0x4e:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD C, [IX + ";
							retString += temp;
							retString += "H]\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0x56:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD D, [IX + ";
							retString += temp;
							retString += "H]\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0x5e:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD E, [IX + ";
							retString += temp;
							retString += "H]\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0x66:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD H, [IX + ";
							retString += temp;
							retString += "H]\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0x6e:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD L, [IX + ";
							retString += temp;
							retString += "H]\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0x70:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD [IX + ";
							retString += temp;
							retString += "H], B\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0x71:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD [IX + ";
							retString += temp;
							retString += "H], C\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0x72:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD [IX + ";
							retString += temp;
							retString += "H], D\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0x73:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD [IX + ";
							retString += temp;
							retString += "H], E\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0x74:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD [IX + ";
							retString += temp;
							retString += "H], H\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0x75:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD [IX + ";
							retString += temp;
							retString += "H], L\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0x77:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD [IX + ";
							retString += temp;
							retString += "H], A\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0x7e:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD A, [IX + ";
							retString += temp;
							retString += "H]\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0x86:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += "86";
							retString += temp;
							retString += "\t\tADD A, [IX + ";
							retString += temp;
							retString += "H]\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0x8e:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += "8E";
							retString += temp;
							retString += "\t\tADC A, [IX + ";
							retString += temp;
							retString += "H]\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0xa6:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += "A6";
							retString += temp;
							retString += "\t\tAND A, [IX + ";
							retString += temp;
							retString += "H]\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0xb6:
						if (!obj.isEmpty()) {
							value = obj.pop();
							retString += " ";
							retString += convertHex(value);
							retString += "\t\tOR A, [IX + ";
							retString += convertHex(value);
							retString += "H]\n";
						} else {
							retString += "\n";
						}
						break;
					case 0xcb:
						if (!obj.isEmpty()) {
							value = obj.pop();
							retString += " ";
							retString += convertHex(value);
							address++;
							switch ((unsigned char)value) {
								case 0x46:
									if (!obj.isEmpty()) {
										value = obj.pop();
										retString += " ";
										retString += convertHex(value);
										retString += "\t\tBIT 0, [IX + ";
										retString += convertHex(value);
										retString += "H]\n";
										address++;
									} else {
										retString += "\n";
									}
									break;
								case 0x4e:
									if (!obj.isEmpty()) {
										value = obj.pop();
										retString += " ";
										retString += convertHex(value);
										retString += "\t\tBIT 1, [IX + ";
										retString += convertHex(value);
										retString += "H]\n";
										address++;
									} else {
										retString += "\n";
									}
									break;
								case 0x56:
									if (!obj.isEmpty()) {
										value = obj.pop();
										retString += " ";
										retString += convertHex(value);
										retString += "\t\tBIT 2, [IX + ";
										retString += convertHex(value);
										retString += "H]\n";
										address++;
									} else {
										retString += "\n";
									}
									break;
								case 0x5e:
									if (!obj.isEmpty()) {
										value = obj.pop();
										retString += " ";
										retString += convertHex(value);
										retString += "\t\tBIT 3, [IX + ";
										retString += convertHex(value);
										retString += "H]\n";
										address++;
									} else {
										retString += "\n";
									}
									break;
								case 0x66:
									if (!obj.isEmpty()) {
										value = obj.pop();
										retString += " ";
										retString += convertHex(value);
										retString += "\t\tBIT 4, [IX + ";
										retString += convertHex(value);
										retString += "H]\n";
										address++;
									} else {
										retString += "\n";
									}
									break;
								case 0x6e:
									if (!obj.isEmpty()) {
										value = obj.pop();
										retString += " ";
										retString += convertHex(value);
										retString += "\t\tBIT 5, [IX + ";
										retString += convertHex(value);
										retString += "H]\n";
										address++;
									} else {
										retString += "\n";
									}
									break;
								case 0x76:
									if (!obj.isEmpty()) {
										value = obj.pop();
										retString += " ";
										retString += convertHex(value);
										retString += "\t\tBIT 6, [IX + ";
										retString += convertHex(value);
										retString += "H]\n";
										address++;
									} else {
										retString += "\n";
									}
									break;
								case 0x7e:
									if (!obj.isEmpty()) {
										value = obj.pop();
										retString += " ";
										retString += convertHex(value);
										retString += "\t\tBIT 7, [IX + ";
										retString += convertHex(value);
										retString += "H]\n";
										address++;
									} else {
										retString += "\n";
									}
									break;
								default:
									retString += " ";
									retString += convertHex(value);
							}
						} else {
							retString += "\n";
						}
						break;
					case 0xbe:
						if (!obj.isEmpty()) {
							retString += " ";
							value = obj.pop();
							retString += convertHex(value);
							retString += "\t\tCP [IX + ";
							retString += convertHex(value);
							retString += "H]\n";
							address++;
						} else {
							retString += "\n";
						}
						break;
					case 0xe1:
						retString += "\t\tPOP IX\n";
						break;
					case 0xe3:
						retString += "\t\tEX [SP], IX\n";
						break;
					case 0xe5:
						retString += "\t\tPUSH IX\n";
						break;
					case 0xe9:
						retString += "\t\tJP [IX]\n";
						break;
					case 0xf9:
						retString += "\t\tLD SP, IX\n";
						break;
					default:
						retString += "\n";
				}
			} else {
				retString += '\n';
			}
			break;
		case 0xe0:
			retString += "\t\tRET P0\n";
			break;
		case 0xe1:
			retString += "\t\tPOP HL\n";
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
					temp2 = convertHex(value);
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
					temp2 = convertHex(value);
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
		case 0xe5:
			retString += "\t\tPUSH HL\n";
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
		case 0xe8:
			retString += "\t\tRET PE\n";
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
					temp2 = convertHex(value);
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
					temp2 = convertHex(value);
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
				retString += " ";
				retString += convertHex(value);
				switch ((unsigned char)value) {
					case 0x40:
						retString += "\t\tIN B, [C]\n";
						break;
					case 0x41:
						retString += "\t\tOUT [C], B\n";
						break;
					case 0x43:
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
								retString += "\t\tLD [";
								retString += temp2;
								retString += temp;
								retString += "H], BC\n";
							} else {
								retString += "\n";
							}
						} else {
							retString += "\n";
						}
					case 0x44:
						retString += "\t\tNEG\n";
						break;
					case 0x45:
						retString += "\t\tRETN\n";
						break;
					case 0x46:
						retString += "\t\tIM 0\n";
						break;
					case 0x47:
						retString += "\t\tLD I, A\n";
						break;
					case 0x48:
						retString += "\t\tIN C, [C]\n";
						break;
					case 0x49:
						retString += "\t\tOUT [C], C\n";
						break;
					case 0x4a:
						retString += "\t\tADC HL, BC\n";
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
								temp2 = convertHex(value);
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
						break;
					case 0x4d:
						retString += "\t\tRETI\n";
						break;
					case 0x4f:
						retString += "\t\tLD R, A\n";
						break;
					case 0x50:
						retString += "\t\tIN D, [C]\n";
						break;
					case 0x51:
						retString += "\t\tOUT [C], D\n";
						break;
					case 0x53:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							address++;
							if (!obj.isEmpty()) {
								address++;
								value = obj.pop();
								temp2 = convertHex(value);
								retString += " ";
								retString += temp2;
								retString += "\t\tLD [";
								retString += temp2;
								retString += temp;
								retString += "H], DE\n";
							} else {
								retString += "\n";
							}
						} else {
							retString += "\n";
						}
						break;
					case 0x56:
						retString += "\t\tIM 1\n";
						break;
					case 0x57:
						retString += "\t\tLD A, I\n";
						break;
					case 0x58:
						retString += "\t\tIN E, [C]\n";
						break;
					case 0x59:
						retString += "\t\tOUT [C], E\n";
						break;
					case 0x5a:
						retString += "\t\tADC HL, DE\n";
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
								temp2 = convertHex(value);
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
						break;
					case 0x5e:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tIM 2\n";
						break;
					case 0x5f:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tLD A, R\n";
						break;
					case 0x60:
						retString += " ";
						retString += convertHex(value);
						retString += "\t\tIN H, [C]\n";
						break;
					case 0x61:
						retString += "\t\tOUT [C], H\n";
						break;
					case 0x63:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							address++;
							if (!obj.isEmpty()) {
								address++;
								value = obj.pop();
								temp2 = convertHex(value);
								retString += " ";
								retString += temp2;
								retString += "\t\tLD [";
								retString += temp2;
								retString += temp;
								retString += "H], HL\n";
							} else {
								retString += "\n";
							}
						} else {
							retString += "\n";
						}
						break;
					case 0x68:
						retString += "\t\tIN L, [C]\n";
						break;
					case 0x69:
						retString += "\t\tOUT [C], L";
						break;
					case 0x6a:
						retString += "\t\tADC HL, HL\n";
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
								temp2 = convertHex(value);
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
					case 0x73:
						if (!obj.isEmpty()) {
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							address++;
							if (!obj.isEmpty()) {
								address++;
								value = obj.pop();
								temp2 = convertHex(value);
								retString += " ";
								retString += temp2;
								retString += "\t\tLD [";
								retString += temp2;
								retString += temp;
								retString += "H], SP\n";
							} else {
								retString += "\n";
							}
						} else {
							retString += "\n";
						}
					case 0x78:
						retString += "\t\tIN A, [C]\n";
						break;
					case 0x79:
						retString += "\t\tOUT [C], A\n";
						break;
					case 0x7a:
						retString += "\t\tADC HL, SP\n";
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
								temp2 = convertHex(value);
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
					case 0xa0:
						retString += "\t\tLDDI\n";
						break;
					case 0xa1:
						retString += "\t\tCPI\n";
						break;
					case 0xa2:
						retString += "\t\tINI\n";
						break;
					case 0xa3:
						retString += "\t\tOUTI\n";
						break;
					case 0xa8:
						retString += "\t\tLDD\n";
						break;
					case 0xa9:
						retString += "\t\tCPD\n";
						break;
					case 0xaa:
						retString += "\t\tIND\n";
						break;
					case 0xab:
						retString += "\t\tOUTD\n";
						break;
					case 0xb0:
						retString += "\t\tLDIR\n";
						break;
					case 0xb1:
						retString += "\t\tCPIR\n";
						break;
					case 0xb2:
						retString += "\t\tINIR\n";
						break;
					case 0xb3:
						retString += "\t\tOTIR\n";
						break;
					case 0xb8:
						retString += "\t\tLDDR\n";
						break;
					case 0xb9:
						retString += "\t\tCPDR\n";
						break;
					case 0xba:
						retString += "\t\tINDR\n";
						break;
					case 0xbb:
						retString += "\t\tOTDR\n";
						break;
					default:
						retString += "\n";
				}
				address++;
			} else {
				retString += "\n";
			}
			break;
		case 0xf0:
			retString += "\t\tRET P\n";
			break;
		case 0xf1:
			retString += "\t\tPOP AF\n";
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
					temp2 = convertHex(value);
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
					temp2 = convertHex(value);
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
		case 0xf5:
			retString += "\t\tPUSH AF\n";
			break;
		case 0xf6:
			if (!obj.isEmpty()) {
				value = obj.pop();
				retString += " ";
				retString += convertHex(value);
				retString += "\t\tOR A, ";
				retString += convertHex(value);
				retString += "H\n";
			} else {
				retString += "\n";
			}
			break;
		case 0xf8:
			retString += "\t\tRET M\n";
			break;
		case 0xf9:
			retString += "\t\tLD SP, HL\n";
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
					temp2 = convertHex(value);
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
					temp2 = convertHex(value);
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
				retString += convertHex(value);
				if (!obj.isEmpty()) {
					switch ((unsigned char)value) {
						case 0x09:
							retString += "\t\tADD IY, BC\n";
							break;
						case 0x19:
							retString += "\t\tADD IY, DE\n";
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
									temp2 = convertHex(value);
									retString += " ";
									retString += temp2;
									retString += "\t\tLD IY, ";
									retString += temp2;
									retString += temp;
									retString += "H\n";
								} else {
									retString += "\n";
								}
							} else {
								retString += "\n";
							}
						case 0x22:
							if (!obj.isEmpty()) {
								value = obj.pop();
								temp = convertHex(value);
								retString += " ";
								retString += temp;
								address++;
								if (!obj.isEmpty()) {
									address++;
									value = obj.pop();
									temp2 = convertHex(value);
									retString += " ";
									retString += temp2;
									retString += "\t\tLD [";
									retString += temp2;
									retString += temp;
									retString += "H], IY\n";
								} else {
									retString += "\n";
								}
							} else {
								retString += "\n";
							}
						case 0x23:
							retString += "\t\tINC IY\n";
							break;
						case 0x29:
							retString += "\t\tADD IY, IY\n";
							break;
						case 0x2a:
							if (!obj.isEmpty()) {
								value = obj.pop();
								temp = convertHex(value);
								retString += " ";
								retString += temp;
								address++;
								if (!obj.isEmpty()) {
									address++;
									value = obj.pop();
									temp2 = convertHex(value);
									retString += " ";
									retString += temp2;
									retString += "\t\tLD IY, [";
									retString += temp2;
									retString += temp;
									retString += "H]\n";
								} else {
									retString += "\n";
								}
							} else {
								retString += "\n";
							}
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
							break;
						case 0x35:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tDEC [IY + ";
							retString += temp;
							retString += "H]\n";
							address += 2;
							break;
						case 0x36:
							if (!obj.isEmpty()) {
								value = obj.pop();
								temp = convertHex(value);
								retString += " ";
								retString += temp;
								address++;
								if (!obj.isEmpty()) {
									address++;
									value = obj.pop();
									temp2 = convertHex(value);
									retString += " ";
									retString += temp2;
									retString += "\t\tLD [IY + ";
									retString += temp;
									retString += "H], ";
									retString += temp2;
									retString += "H\n";
								} else {
									retString += "\n";
								}
							} else {
								retString += "\n";
							}
							break;
						case 0x39:
							retString += "\t\tADD IY, SP\n";
							break;
						case 0x46:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD B, [IY + ";
							retString += temp;
							retString += "H]\n";
							address += 2;
							break;
						case 0x4e:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD C, [IY + ";
							retString += temp;
							retString += "H]\n";
							address += 2;
							break;
						case 0x56:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD D, [IY + ";
							retString += temp;
							retString += "H]\n";
							address += 2;
							break;
						case 0x5e:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD E, [IY + ";
							retString += temp;
							retString += "H]\n";
							address += 2;
							break;
						case 0x66:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD H, [IY + ";
							retString += temp;
							retString += "H]\n";
							address += 2;
							break;
						case 0x6e:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD L, [IY + ";
							retString += temp;
							retString += "H]\n";
							address += 2;
							break;
						case 0x70:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD [IY + ";
							retString += temp;
							retString += "H], B\n";
							address += 2;
							break;
						case 0x71:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD [IY + ";
							retString += temp;
							retString += "H], C\n";
							address += 2;
							break;
						case 0x72:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD [IY + ";
							retString += temp;
							retString += "H], D\n";
							address += 2;
							break;
						case 0x73:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD [IY + ";
							retString += temp;
							retString += "H], E\n";
							address += 2;
							break;
						case 0x74:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD [IY + ";
							retString += temp;
							retString += "H], H\n";
							address += 2;
							break;
						case 0x75:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD [IY + ";
							retString += temp;
							retString += "H], L\n";
							address += 2;
							break;
						case 0x77:
							value = obj.pop();
							temp = convertHex(value);
							retString += " ";
							retString += temp;
							retString += "\t\tLD [IY + ";
							retString += temp;
							retString += "H], A\n";
							address += 2;
							break;
						case 0x7e:
							if (!obj.isEmpty()) {
								value = obj.pop();
								temp = convertHex(value);
								retString += " ";
								retString += temp;
								retString += "\t\tLD A, [IY + ";
								retString += temp;
								retString += "H]\n";
								address += 2;
							}
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
							retString += "H]\n";
							break;
						case 0xb6:
							if (!obj.isEmpty()) {
								value = obj.pop();
								retString += " ";
								retString += convertHex(value);
								retString += "\t\tOR A, [IY + ";
								retString += convertHex(value);
								retString += "H]\n";
							} else {
								retString += "\n";
							}
							break;
						case 0xbe:
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
						case 0xe1:
							retString += "\t\tPOP IY\n";
							break;
						case 0xe3:
							retString += "\t\tEX [SP], IY\n";
							break;
						case 0xe5:
							retString += "\t\tPUSH IY\n";
							break;
						case 0xe9:
							retString += "\t\tJP [IY]\n";
							break;
						case 0xf9:
							retString += "\t\tLD SP, IY\n";
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

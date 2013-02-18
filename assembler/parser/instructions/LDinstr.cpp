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
	file name: LDinstr.cpp
	date created: 14/02/2013
	date updated: 17/02/2013
	author: Gareth Richardson
	description: This is the method to process an LD instruction.
*/

#include <string>

using namespace std;

#include "../../lex/tokenlist.hpp"
#include "../bytecode.hpp"
#include "../foundlist.hpp"
#include "../addresslist.hpp"
#include "../parser.hpp"

void Z80Parser::processLD() {
	unsigned char num8;
	unsigned char num8Two;
	unsigned short num16;
	string atom;
	/*
		Make sure that you HAVE checked that the beginning IS an LD instruction before calling this method.
	*/
	if (Z80Parser::checkToken(A)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(A)) {
				Z80Parser::addCode((unsigned char) 0x7f);
			} else if (Z80Parser::checkToken(B)) {
				Z80Parser::addCode((unsigned char) 0x78);
			} else if (Z80Parser::checkToken(C)) {
				Z80Parser::addCode((unsigned char) 0x79);
			} else if (Z80Parser::checkToken(D)) {
				Z80Parser::addCode((unsigned char) 0x7a);
			} else if (Z80Parser::checkToken(E)) {
				Z80Parser::addCode((unsigned char) 0x7b);
			} else if (Z80Parser::checkToken(H)) {
				Z80Parser::addCode((unsigned char) 0x7c);
			} else if (Z80Parser::checkToken(L)) {
				Z80Parser::addCode((unsigned char) 0x7d);
			} else if (Z80Parser::checkToken(I)) {
				Z80Parser::addCode((unsigned char) 0xed, (unsigned char) 0x57);
			} else if (Z80Parser::checkToken(R)) {
				Z80Parser::addCode((unsigned char) 0xed, (unsigned char) 0x5f);
			}else if (Z80Parser::checkEightBitNumber(num8)) {
				Z80Parser::addCode((unsigned char) 0x3e, num8);
			} else if (Z80Parser::checkToken(LEFT_BRACKET)) {
				if (Z80Parser::checkToken(BC)) {
					if (Z80Parser::checkToken(RIGHT_BRACKET)) {
						Z80Parser::addCode((unsigned char) 0x0a);
					} else {
						Z80Parser::error("An LD instruction must used Registers, immediate values OR addresses.");
					}
				} else if (Z80Parser::checkToken(DE)) {
					if (Z80Parser::checkToken(RIGHT_BRACKET)) {
						Z80Parser::addCode((unsigned char) 0x1a);
					} else {
						Z80Parser::error("An LD instruction must used Registers, immediate values OR addresses.");
					}
				}else if (Z80Parser::checkToken(HL)) {
					if (Z80Parser::checkToken(RIGHT_BRACKET)) {
						Z80Parser::addCode((unsigned char) 0x7e);
					} else {
						Z80Parser::error("An LD instruction must used Registers, immediate values OR addresses.");
					}
				} else if (Z80Parser::checkToken(IX)) {
					if (Z80Parser::checkToken(PLUS)) {
						if (Z80Parser::checkEightBitNumber(num8)) {
							Z80Parser::addCode((unsigned char) 0xdd, (unsigned char) 0x7e, num8);
							if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
								Z80Parser::error("The LD reg8, [IX + imm8] instruction must use brackets [].");
							}
						} else {
							Z80Parser::error("The LD reg8, [IX + imm8] requires a byte number.");
						}
					} else {
						Z80Parser::error("The LD reg8, [IX + imm8] requires an addition.");
					}
				} else if (Z80Parser::checkToken(IY)) {
					if (Z80Parser::checkToken(PLUS)) {
						if (Z80Parser::checkEightBitNumber(num8)) {
							Z80Parser::addCode((unsigned char) 0xfd, (unsigned char) 0x7e, num8);
							if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
								Z80Parser::error("The LD reg8, [IX + imm8] instruction must use brackets [].");
							}
						} else {
							Z80Parser::error("The LD reg8, [IX + imm8] requires a byte number.");
						}
					} else {
						Z80Parser::error("The LD reg8, [IX + imm8] requires an addition.");
					}
				} else if (Z80Parser::checkSixteenBitNumber(num16)) {
					if (Z80Parser::checkToken(RIGHT_BRACKET)) {
						Z80Parser::addCode((unsigned char) 0x3a, (unsigned char) num16, (unsigned char) (num16 >> 8));
					} else {
						Z80Parser::error("Missing bracket.");
					}
				} else if (Z80Parser::checkAtom(atom)) {
					Z80Parser::addCode((unsigned char) 0x3a);
					if (Z80Parser::fList.doesNameExist(atom)) {
						int index = 0;
						while (index < Z80Parser::fList.getSize()) {
							if (Z80Parser::fList.getName(index).compare(atom) == 0) {
								break;
							}
							index++;
						}
						num16 = Z80Parser::fList.getAddress(index);
						Z80Parser::addCode((unsigned char) num16, (unsigned char) (num16 >> 8));
					} else {
						Z80Parser::aList.addAddress(atom, Z80Parser::address + 1);
						Z80Parser::addCode(0x00, 0x00);
					}
					/*
						Now for the rest of the checking:
					*/
					if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
						Z80Parser::error("Missing Bracket");
					}
				} else {
					Z80Parser::error("An LD instruction must used Registers, immediate values OR addresses.");
				}
			} else {
				Z80Parser::error("An LD instruction must used Registers, immediate values OR addresses.");
			}
		} else {
			Z80Parser::error("An LD instruction must use a COMMA between declared registers.");
		}
	} else if (Z80Parser::checkToken(B)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(A)) {
				Z80Parser::addCode((unsigned char) 0x47);
			} else if (Z80Parser::checkToken(B)) {
				Z80Parser::addCode((unsigned char) 0x40);
			} else if (Z80Parser::checkToken(C)) {
				Z80Parser::addCode((unsigned char) 0x41);
			} else if (Z80Parser::checkToken(D)) {
				Z80Parser::addCode((unsigned char) 0x42);
			} else if (Z80Parser::checkToken(E)) {
				Z80Parser::addCode((unsigned char) 0x43);
			} else if (Z80Parser::checkToken(H)) {
				Z80Parser::addCode((unsigned char) 0x44);
			} else if (Z80Parser::checkToken(L)) {
				Z80Parser::addCode((unsigned char) 0x45);
			} else if (Z80Parser::checkEightBitNumber(num8)) {
				Z80Parser::addCode((unsigned char) 0x06, num8);
			} else if (Z80Parser::checkToken(LEFT_BRACKET)) {
				if (Z80Parser::checkToken(HL)) {
					if (Z80Parser::checkToken(RIGHT_BRACKET)) {
						Z80Parser::addCode((unsigned char) 0x46);
					} else {
						Z80Parser::error("An LD instruction must used Registers, immediate values OR addresses.");
					}
				} else if (Z80Parser::checkToken(IX)) {
					if (Z80Parser::checkToken(PLUS)) {
						if (Z80Parser::checkEightBitNumber(num8)) {
							Z80Parser::addCode((unsigned char) 0xdd, (unsigned char) 0x46, num8);
							if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
								Z80Parser::error("The LD reg8, [IX + imm8] instruction must use brackets [].");
							}
						} else {
							Z80Parser::error("The LD reg8, [IX + imm8] requires a byte number.");
						}
					} else {
						Z80Parser::error("The LD reg8, [IX + imm8] requires an addition.");
					}
				} else if (Z80Parser::checkToken(IY)) {
					if (Z80Parser::checkToken(PLUS)) {
						if (Z80Parser::checkEightBitNumber(num8)) {
							Z80Parser::addCode((unsigned char) 0xfd, (unsigned char) 0x46, num8);
							if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
								Z80Parser::errorState = true;
								Z80Parser::errorString = "The LD reg8, [IX + imm8] instruction must use brackets [].";
							}
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "The LD reg8, [IX + imm8] requires a byte number.";
						}
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "The LD reg8, [IX + imm8] requires an addition.";
					}
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
				}
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
			}
		} else {
			Z80Parser::errorState = true;
			Z80Parser::errorString = "An LD instruction must use a COMMA between declared registers.";
		}
	} else if (Z80Parser::checkToken(C)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(A)) {
				Z80Parser::addCode((unsigned char) 0x4f);
			} else if (Z80Parser::checkToken(B)) {
				Z80Parser::addCode((unsigned char) 0x48);
			} else if (Z80Parser::checkToken(C)) {
				Z80Parser::addCode((unsigned char) 0x49);
			} else if (Z80Parser::checkToken(D)) {
				Z80Parser::addCode((unsigned char) 0x4a);
			} else if (Z80Parser::checkToken(E)) {
				Z80Parser::addCode((unsigned char) 0x4b);
			} else if (Z80Parser::checkToken(H)) {
				Z80Parser::addCode((unsigned char) 0x4c);
			} else if (Z80Parser::checkToken(L)) {
				Z80Parser::addCode((unsigned char) 0x4d);
			} else if (Z80Parser::checkEightBitNumber(num8)) {
				Z80Parser::addCode((unsigned char) 0x0e, num8);
			} else if (Z80Parser::checkToken(LEFT_BRACKET)) {
				if (Z80Parser::checkToken(HL)) {
					if (Z80Parser::checkToken(RIGHT_BRACKET)) {
						Z80Parser::addCode((unsigned char) 0x4e);
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
					}
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
				}
			} else if (Z80Parser::checkToken(IX)) {
				if (Z80Parser::checkToken(PLUS)) {
					if (Z80Parser::checkEightBitNumber(num8)) {
						Z80Parser::addCode((unsigned char) 0xdd, (unsigned char) 0x4e, num8);
						if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "The LD reg8, [IX + imm8] instruction must use brackets [].";
						}
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "The LD reg8, [IX + imm8] requires a byte number.";
					}
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "The LD reg8, [IX + imm8] requires an addition.";
				}
			} else if (Z80Parser::checkToken(IY)) {
					if (Z80Parser::checkToken(PLUS)) {
						if (Z80Parser::checkEightBitNumber(num8)) {
							Z80Parser::addCode((unsigned char) 0xfd, (unsigned char) 0x4e, num8);
							if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
								Z80Parser::errorState = true;
								Z80Parser::errorString = "The LD reg8, [IX + imm8] instruction must use brackets [].";
							}
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "The LD reg8, [IX + imm8] requires a byte number.";
						}
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "The LD reg8, [IX + imm8] requires an addition.";
					}
				} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "An LD instruction must use Registers, immediate values OR addresses.";
			}
		} else {
			Z80Parser::errorState = true;
			Z80Parser::errorString = "An LD instruction must use a COMMA between declared registers.";
		}
	} else if (Z80Parser::checkToken(D)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(A)) {
				Z80Parser::addCode((unsigned char) 0x57);
			} else if (Z80Parser::checkToken(B)) {
				Z80Parser::addCode((unsigned char) 0x50);
			} else if (Z80Parser::checkToken(C)) {
				Z80Parser::addCode((unsigned char) 0x51);
			} else if (Z80Parser::checkToken(D)) {
				Z80Parser::addCode((unsigned char) 0x52);
			} else if (Z80Parser::checkToken(E)) {
				Z80Parser::addCode((unsigned char) 0x53);
			} else if (Z80Parser::checkToken(H)) {
				Z80Parser::addCode((unsigned char) 0x54);
			} else if (Z80Parser::checkToken(L)) {
				Z80Parser::addCode((unsigned char) 0x55);
			} else if (Z80Parser::checkEightBitNumber(num8)) {
				Z80Parser::addCode((unsigned char) 0x16, num8);
			} else if (Z80Parser::checkToken(LEFT_BRACKET)) {
				if (Z80Parser::checkToken(HL)) {
					if (Z80Parser::checkToken(RIGHT_BRACKET)) {
						Z80Parser::addCode((unsigned char) 0x56);
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
					}
				} else if (Z80Parser::checkToken(IX)) {
					if (Z80Parser::checkToken(PLUS)) {
						if (Z80Parser::checkEightBitNumber(num8)) {
							Z80Parser::addCode((unsigned char) 0xdd, (unsigned char) 0x56, num8);
							if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
								Z80Parser::errorState = true;
								Z80Parser::errorString = "The LD reg8, [IX + imm8] instruction must use brackets [].";
							}
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "The LD reg8, [IX + imm8] requires a byte number.";
						}
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "The LD reg8, [IX + imm8] requires an addition.";
					}
				} else if (Z80Parser::checkToken(IY)) {
					if (Z80Parser::checkToken(PLUS)) {
						if (Z80Parser::checkEightBitNumber(num8)) {
							Z80Parser::addCode((unsigned char) 0xfd, (unsigned char) 0x56, num8);
							if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
								Z80Parser::errorState = true;
								Z80Parser::errorString = "The LD reg8, [IX + imm8] instruction must use brackets [].";
							}
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "The LD reg8, [IX + imm8] requires a byte number.";
						}
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "The LD reg8, [IX + imm8] requires an addition.";
					}
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
				}
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
			}
		} else {
			Z80Parser::errorState = true;
			Z80Parser::errorString = "An LD instruction must use a COMMA between declared registers.";
		}
	} else if (Z80Parser::checkToken(E)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(A)) {
				Z80Parser::addCode((unsigned char) 0x5f);
			} else if (Z80Parser::checkToken(B)) {
				Z80Parser::addCode((unsigned char) 0x58);
			} else if (Z80Parser::checkToken(C)) {
				Z80Parser::addCode((unsigned char) 0x59);
			} else if (Z80Parser::checkToken(D)) {
				Z80Parser::addCode((unsigned char) 0x5a);
			} else if (Z80Parser::checkToken(E)) {
				Z80Parser::addCode((unsigned char) 0x5b);
			} else if (Z80Parser::checkToken(H)) {
				Z80Parser::addCode((unsigned char) 0x5c);
			} else if (Z80Parser::checkToken(L)) {
				Z80Parser::addCode((unsigned char) 0x5d);
			} else if (Z80Parser::checkEightBitNumber(num8)) {
				Z80Parser::addCode((unsigned char) 0x1e, num8);
			} else if (Z80Parser::checkToken(LEFT_BRACKET)) {
				if (Z80Parser::checkToken(HL)) {
					if (Z80Parser::checkToken(RIGHT_BRACKET)) {
						Z80Parser::addCode((unsigned char) 0x5e);
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
					}
				} else if (Z80Parser::checkToken(IX)) {
					if (Z80Parser::checkToken(PLUS)) {
						if (Z80Parser::checkEightBitNumber(num8)) {
							Z80Parser::addCode((unsigned char) 0xdd, (unsigned char) 0x5e, num8);
							if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
								Z80Parser::errorState = true;
								Z80Parser::errorString = "The LD reg8, [IX + imm8] instruction must use brackets [].";
							}
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "The LD reg8, [IX + imm8] requires a byte number.";
						}
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "The LD reg8, [IX + imm8] requires an addition.";
					}
				} else if (Z80Parser::checkToken(IY)) {
					if (Z80Parser::checkToken(PLUS)) {
						if (Z80Parser::checkEightBitNumber(num8)) {
							Z80Parser::addCode((unsigned char) 0xfd, (unsigned char) 0x5e, num8);
							if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
								Z80Parser::errorState = true;
								Z80Parser::errorString = "The LD reg8, [IX + imm8] instruction must use brackets [].";
							}
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "The LD reg8, [IX + imm8] requires a byte number.";
						}
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "The LD reg8, [IX + imm8] requires an addition.";
					}
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
				}
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
			}
		} else {
			Z80Parser::errorState = true;
			Z80Parser::errorString = "An LD instruction must use a COMMA between declared registers.";
		}
	} else if (Z80Parser::checkToken(H)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(A)) {
				Z80Parser::addCode((unsigned char) 0x67);
			} else if (Z80Parser::checkToken(B)) {
				Z80Parser::addCode((unsigned char) 0x60);
			} else if (Z80Parser::checkToken(C)) {
				Z80Parser::addCode((unsigned char) 0x61);
			} else if (Z80Parser::checkToken(D)) {
				Z80Parser::addCode((unsigned char) 0x62);
			} else if (Z80Parser::checkToken(E)) {
				Z80Parser::addCode((unsigned char) 0x63);
			} else if (Z80Parser::checkToken(H)) {
				Z80Parser::addCode((unsigned char) 0x64);
			} else if (Z80Parser::checkToken(L)) {
				Z80Parser::addCode((unsigned char) 0x65);
			} else if (Z80Parser::checkEightBitNumber(num8)) {
				Z80Parser::addCode((unsigned char) 0x26, num8);
			} else if (Z80Parser::checkToken(LEFT_BRACKET)) {
				if (Z80Parser::checkToken(HL)) {
					if (Z80Parser::checkToken(RIGHT_BRACKET)) {
						Z80Parser::addCode((unsigned char) 0x66);
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
					}
				} else if (Z80Parser::checkToken(IX)) {
					if (Z80Parser::checkToken(PLUS)) {
						if (Z80Parser::checkEightBitNumber(num8)) {
							Z80Parser::addCode((unsigned char) 0xdd, (unsigned char) 0x66, num8);
							if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
								Z80Parser::errorState = true;
								Z80Parser::errorString = "The LD reg8, [IX + imm8] instruction must use brackets [].";
							}
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "The LD reg8, [IX + imm8] requires a byte number.";
						}
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "The LD reg8, [IX + imm8] requires an addition.";
					}
				} else if (Z80Parser::checkToken(IY)) {
					if (Z80Parser::checkToken(PLUS)) {
						if (Z80Parser::checkEightBitNumber(num8)) {
							Z80Parser::addCode((unsigned char) 0xfd, (unsigned char) 0x66, num8);
							if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
								Z80Parser::errorState = true;
								Z80Parser::errorString = "The LD reg8, [IX + imm8] instruction must use brackets [].";
							}
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "The LD reg8, [IX + imm8] requires a byte number.";
						}
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "The LD reg8, [IX + imm8] requires an addition.";
					}
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
				}
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
			}
		} else {
			Z80Parser::errorState = true;
			Z80Parser::errorString = "An LD instruction must use a COMMA between declared registers.";
		}
	} else if (Z80Parser::checkToken(L)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(A)) {
				Z80Parser::addCode((unsigned char) 0x6f);
			} else if (Z80Parser::checkToken(B)) {
				Z80Parser::addCode((unsigned char) 0x68);
			} else if (Z80Parser::checkToken(C)) {
				Z80Parser::addCode((unsigned char) 0x69);
			} else if (Z80Parser::checkToken(D)) {
				Z80Parser::addCode((unsigned char) 0x6a);
			} else if (Z80Parser::checkToken(E)) {
				Z80Parser::addCode((unsigned char) 0x6b);
			} else if (Z80Parser::checkToken(H)) {
				Z80Parser::addCode((unsigned char) 0x6c);
			} else if (Z80Parser::checkToken(L)) {
				Z80Parser::addCode((unsigned char) 0x6d);
			} else if (Z80Parser::checkEightBitNumber(num8)) {
				Z80Parser::addCode((unsigned char) 0x2e, num8);
			} else if (Z80Parser::checkToken(LEFT_BRACKET)) {
				if (Z80Parser::checkToken(HL)) {
					if (Z80Parser::checkToken(RIGHT_BRACKET)) {
						Z80Parser::addCode((unsigned char) 0x6e);
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
					}
				} else if (Z80Parser::checkToken(IX)) {
					if (Z80Parser::checkToken(PLUS)) {
						if (Z80Parser::checkEightBitNumber(num8)) {
							Z80Parser::addCode((unsigned char) 0xdd, (unsigned char) 0x6e, num8);
							if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
								Z80Parser::errorState = true;
								Z80Parser::errorString = "The LD reg8, [IX + imm8] instruction must use brackets [].";
							}
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "The LD reg8, [IX + imm8] requires a byte number.";
						}
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "The LD reg8, [IX + imm8] requires an addition.";
					}
				} else if (Z80Parser::checkToken(IY)) {
					if (Z80Parser::checkToken(PLUS)) {
						if (Z80Parser::checkEightBitNumber(num8)) {
							Z80Parser::addCode((unsigned char) 0xfd, (unsigned char) 0x6e, num8);
							if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
								Z80Parser::errorState = true;
								Z80Parser::errorString = "The LD reg8, [IX + imm8] instruction must use brackets [].";
							}
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "The LD reg8, [IX + imm8] requires a byte number.";
						}
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "The LD reg8, [IX + imm8] requires an addition.";
					}
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
				}
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
			}
		} else {
			Z80Parser::errorState = true;
			Z80Parser::errorString = "An LD instruction must use a COMMA between declared registers.";
		}
	} else if (Z80Parser::checkToken(I)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(A)) {
				Z80Parser::addCode(0xed, 0x47);
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "Missing a register after the comma.";
			}
		} else {
			Z80Parser::errorState = true;
			Z80Parser::errorString = "Missing comma.";
		}
	} else if (Z80Parser::checkToken(R)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(A)) {
				Z80Parser::addCode(0xed, 0x4f);
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "Missing a register after the comma.";
			}
		} else {
			Z80Parser::errorState = true;
			Z80Parser::errorString = "Missing comma.";
		}
	} else if (Z80Parser::checkToken(BC)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkSixteenBitNumber(num16)) {
				Z80Parser::addCode(0x01, (unsigned char) num16, (unsigned char) (num16 >> 8));
			} else if (Z80Parser::checkAtom(atom)) {
				Z80Parser::addCode((unsigned char) 0x01);
				Z80Parser::addAddress(atom);
			} else if (Z80Parser::checkToken(LEFT_BRACKET)) {
				if (Z80Parser::checkSixteenBitNumber(num16)) {
					Z80Parser::addCode((unsigned char) 0xed, 0x4b);
					Z80Parser::addCode((unsigned char) num16, (unsigned char) (num16 >> 8));
				} else if (Z80Parser::checkAtom(atom)) {
					Z80Parser::addCode((unsigned char) 0xed, 0x4b);
					Z80Parser::addAddress(atom);
					
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "Incorrect usage of LD.";
				}
				if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "Missing bracket.";
				}
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "Missing 16-bit number.";
			}
		} else {
			Z80Parser::errorState = true;
			Z80Parser::errorString = "Missing comma.";
		}
	} else if (Z80Parser::checkToken(DE)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkSixteenBitNumber(num16)) {
				Z80Parser::addCode(0x11, (unsigned char) num16, (unsigned char) (num16 >> 8));
			} else if (Z80Parser::checkAtom(atom)) {
				Z80Parser::addCode((unsigned char) 0x11);
				Z80Parser::addAddress(atom);
			} else if (Z80Parser::checkToken(LEFT_BRACKET)) {
				if (Z80Parser::checkSixteenBitNumber(num16)) {
					Z80Parser::addCode((unsigned char) 0xed, 0x5b);
					Z80Parser::addCode((unsigned char) num16, (unsigned char) (num16 >> 8));
				} else if (Z80Parser::checkAtom(atom)) {
					Z80Parser::addCode((unsigned char) 0xed, 0x5b);
					Z80Parser::addAddress(atom);
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "Incorrect usage of LD.";
				}
				if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "Missing bracket.";
				}
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "Missing 16-bit number.";
			}
		} else {
			Z80Parser::errorState = true;
			Z80Parser::errorString = "Missing comma.";
		}
	} else if (Z80Parser::checkToken(HL)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkSixteenBitNumber(num16)) {
				Z80Parser::addCode(0x21, (unsigned char) num16, (unsigned char) (num16 >> 8));
			} else if (Z80Parser::checkAtom(atom)) {
				Z80Parser::addCode((unsigned char) 0x21);
				Z80Parser::addAddress(atom);
			} else if (Z80Parser::checkToken(LEFT_BRACKET)) {
				if (Z80Parser::checkSixteenBitNumber(num16)) {
					Z80Parser::addCode((unsigned char) 0xed, 0x6b);
					Z80Parser::addCode((unsigned char) num16, (unsigned char) (num16 >> 8));
				} else if (Z80Parser::checkAtom(atom)) {
					Z80Parser::addCode((unsigned char) 0xed, 0x6b);
					Z80Parser::addAddress(atom);
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "Incorrect usage of LD.";
				}
				if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "Missing bracket.";
				}
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "Missing 16-bit number.";
			}
		} else {
			Z80Parser::errorState = true;
			Z80Parser::errorString = "Missing comma.";
		}
	} else if (Z80Parser::checkToken(SP)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(HL)) {
				Z80Parser::addCode(0xf9);
			} else if (Z80Parser::checkToken(IX)) {
				Z80Parser::addCode(0xdd);
				Z80Parser::addCode(0xf9);
			} else if (Z80Parser::checkToken(IY)) {
				Z80Parser::addCode(0xfd);
				Z80Parser::addCode(0xf9);
			} else if (Z80Parser::checkSixteenBitNumber(num16)) {
				Z80Parser::addCode(0x31, (unsigned char) num16, (unsigned char) (num16 >> 8));
			} else if (Z80Parser::checkAtom(atom)) {
				Z80Parser::addCode((unsigned char) 0x31);
				Z80Parser::addAddress(atom);
			} else if (Z80Parser::checkToken(LEFT_BRACKET)) {
				if (Z80Parser::checkSixteenBitNumber(num16)) {
						Z80Parser::addCode((unsigned char) 0xed, 0x7b);
						Z80Parser::addCode((unsigned char) num16, (unsigned char) (num16 >> 8));
				} else if (Z80Parser::checkAtom(atom)) {
					Z80Parser::addCode((unsigned char) 0xed, 0x7b);
					Z80Parser::addAddress(atom);
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "Incorrect usage of LD.";
				}
				if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "Missing bracket.";
				}
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "Missing 16-bit number.";
			}
		} else {
			Z80Parser::errorState = true;
			Z80Parser::errorString = "Missing comma.";
		}
	} else if (Z80Parser::checkToken(HL)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkToken(LEFT_BRACKET)) {
				if (Z80Parser::checkSixteenBitNumber(num16)) {
					Z80Parser::addCode(0xdd, 0x21);
					Z80Parser::addCode((unsigned char) num16, (unsigned char) (num16 >> 8));
				} else if (Z80Parser::checkAtom(atom)) {
					Z80Parser::addCode((unsigned char) 0xdd, 0x21);
					Z80Parser::addAddress(atom);
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "Incorrect usage of LD.";
				}
				if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "Missing bracket.";
				}
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "Missing bracket.";
			}
		} else {
			Z80Parser::errorState = true;
			Z80Parser::errorString = "Missing comma.";
		}
	} else if (Z80Parser::checkToken(IX)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkSixteenBitNumber(num16)) {
				Z80Parser::addCode(0xdd, 0x21);
				Z80Parser::addCode((unsigned char) num16, (unsigned char) (num16 >> 8));
			} else if (Z80Parser::checkAtom(atom)) {
				Z80Parser::addCode((unsigned char) 0xdd, 0x21);
				Z80Parser::addAddress(atom);
			} else if (Z80Parser::checkToken(LEFT_BRACKET)) {
				Z80Parser::addCode(0xdd, 0x2a);
				if (Z80Parser::checkSixteenBitNumber(num16)) {
					Z80Parser::addCode((unsigned char) num16, (unsigned char) (num16 >> 8));
				} else if (Z80Parser::checkAtom(atom)) {
					Z80Parser::addAddress(atom);
				} else {
					Z80Parser::error("Value in second parameter has to be a 16-bit address.");
				}
				if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
					Z80Parser::error("Missing right bracket.");
				}
			} else {
				Z80Parser::error("Missing 16-bit number.");
			}
		} else {
			Z80Parser::error("Missing comma.");
		}
	} else if (Z80Parser::checkToken(IY)) {
		if (Z80Parser::checkToken(COMMA)) {
			if (Z80Parser::checkSixteenBitNumber(num16)) {
				Z80Parser::addCode(0xfd, 0x21);
				Z80Parser::addCode((unsigned char) num16, (unsigned char) (num16 >> 8));
			} else if (Z80Parser::checkAtom(atom)) {
				Z80Parser::addCode((unsigned char) 0xfd, 0x21);
				Z80Parser::addAddress(atom);
			} else if (Z80Parser::checkToken(LEFT_BRACKET)) {
				Z80Parser::addCode(0xfd, 0x2a);
				if (Z80Parser::checkSixteenBitNumber(num16)) {
					Z80Parser::addCode((unsigned char) num16, (unsigned char) (num16 >> 8));
				} else if (Z80Parser::checkAtom(atom)) {
					Z80Parser::addAddress(atom);
				} else {
					Z80Parser::error("Value in second parameter has to be a 16-bit address.");
				}
				if (!Z80Parser::checkToken(RIGHT_BRACKET)) {
					Z80Parser::error("Missing right bracket.");
				}
			} else {
				Z80Parser::error("Missing 16-bit number.");
			}
		} else {
			Z80Parser::error("Missing comma.");
		}
	} else if (Z80Parser::checkToken(LEFT_BRACKET)) {
		if (Z80Parser::checkToken(BC)) {
			if (Z80Parser::checkToken(RIGHT_BRACKET)) {
				if (Z80Parser::checkToken(COMMA)) {
					if (Z80Parser::checkToken(A)) {
						Z80Parser::addCode(0x02);
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "Missing Register.";
					}
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "Missing comma.";
				}
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "Missing bracket.";
			}
		} else if (Z80Parser::checkToken(DE)) {
			if (Z80Parser::checkToken(RIGHT_BRACKET)) {
				if (Z80Parser::checkToken(COMMA)) {
					if (Z80Parser::checkToken(A)) {
						Z80Parser::addCode(0x12);
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "Missing Register.";
					}
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "Missing comma.";
				}
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "Missing bracket.";
			}
		} else if (Z80Parser::checkToken(HL)) {
			if (Z80Parser::checkToken(RIGHT_BRACKET)) {
				if (Z80Parser::checkToken(COMMA)) {
					if (Z80Parser::checkToken(A)) {
						Z80Parser::addCode(0x77);
					} else if (Z80Parser::checkToken(B)) {
						Z80Parser::addCode(0x70);
					} else if (Z80Parser::checkToken(C)) {
						Z80Parser::addCode(0x71);
					} else if (Z80Parser::checkToken(D)) {
						Z80Parser::addCode(0x72);
					} else if (Z80Parser::checkToken(E)) {
						Z80Parser::addCode(0x73);
					} else if (Z80Parser::checkToken(H)) {
						Z80Parser::addCode(0x74);
					} else if (Z80Parser::checkToken(L)) {
						Z80Parser::addCode(0x75);
					} else if (Z80Parser::checkEightBitNumber(num8)) {
						Z80Parser::addCode(0x36, num8);
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "The LD [HL], reg8 instruction must only use an eight bit register.";
					}
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
				}
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
			}
		} else if (Z80Parser::checkToken(IX)) {
			if (Z80Parser::checkToken(PLUS)) {
				if (Z80Parser::checkEightBitNumber(num8)) {
					if (Z80Parser::checkToken(RIGHT_BRACKET)) {
						if (Z80Parser::checkToken(COMMA)) {
							Z80Parser::addCode(0xdd);
							if (Z80Parser::checkToken(A)) {
								Z80Parser::addCode(0x77);
							} else if (Z80Parser::checkToken(B)) {
								Z80Parser::addCode(0x70);
							} else if (Z80Parser::checkToken(C)) {
								Z80Parser::addCode(0x71);
							} else if (Z80Parser::checkToken(D)) {
								Z80Parser::addCode(0x72);
							} else if (Z80Parser::checkToken(E)) {
								Z80Parser::addCode(0x73);
							} else if (Z80Parser::checkToken(H)) {
								Z80Parser::addCode(0x74);
							} else if (Z80Parser::checkToken(L)) {
								Z80Parser::addCode(0x75);
							} else if (Z80Parser::checkEightBitNumber(num8Two)) {
								Z80Parser::addCode(0x36, num8, num8Two);
							} else {
								Z80Parser::errorState = true;
								Z80Parser::errorString = "LD [IX + imm], reg8 must end in an eight bit register.";
							}
							Z80Parser::addCode(num8);
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "Missing comma in LD instruction.";
						}
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "Missing right bracket.";
					}
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "The LD [IX + imm], reg8 has to have a byte.";
				}
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "The LD [IX + imm], reg8 instruction needs an addition sign.";
			}
		} else if (Z80Parser::checkToken(IY)) {
			if (Z80Parser::checkToken(PLUS)) {
				if (Z80Parser::checkEightBitNumber(num8)) {
					if (Z80Parser::checkToken(RIGHT_BRACKET)) {
						if (Z80Parser::checkToken(COMMA)) {
							Z80Parser::addCode(0xfd);
							if (Z80Parser::checkToken(A)) {
								Z80Parser::addCode(0x77);
							} else if (Z80Parser::checkToken(B)) {
								Z80Parser::addCode(0x70);
							} else if (Z80Parser::checkToken(C)) {
								Z80Parser::addCode(0x71);
							} else if (Z80Parser::checkToken(D)) {
								Z80Parser::addCode(0x72);
							} else if (Z80Parser::checkToken(E)) {
								Z80Parser::addCode(0x73);
							} else if (Z80Parser::checkToken(H)) {
								Z80Parser::addCode(0x74);
							} else if (Z80Parser::checkToken(L)) {
								Z80Parser::addCode(0x75);
							} else if (Z80Parser::checkEightBitNumber(num8Two)) {
								Z80Parser::addCode(0x36, num8, num8Two);
							} else {
								Z80Parser::errorState = true;
								Z80Parser::errorString = "LD [IY + imm], reg8 must end in an eight bit register.";
							}
							Z80Parser::addCode(num8);
						} else {
							Z80Parser::errorState = true;
							Z80Parser::errorString = "Missing comma in LD instruction.";
						}
					} else {
						Z80Parser::errorState = true;
						Z80Parser::errorString = "Missing right bracket.";
					}
				} else {
					Z80Parser::errorState = true;
					Z80Parser::errorString = "The LD [IX + imm], reg8 has to have a byte.";
				}
			} else {
				Z80Parser::errorState = true;
				Z80Parser::errorString = "The LD [IX + imm], reg8 instruction needs an addition sign.";
			}
		} else if (Z80Parser::checkSixteenBitNumber(num16)) {
			if (Z80Parser::checkToken(RIGHT_BRACKET)) {
				if (Z80Parser::checkToken(COMMA)) {
					if (Z80Parser::checkToken(A)) {
						Z80Parser::addCode(0x32, (unsigned short) num16, (unsigned short) (num16 >> 8));
					} else if (Z80Parser::checkToken(BC)) {
						Z80Parser::addCode(0xed, 0x43);
						Z80Parser::addCode((unsigned short) num16, (unsigned short) (num16 >> 8));
					} else if (Z80Parser::checkToken(DE)) {
						Z80Parser::addCode(0xed, 0x53);
						Z80Parser::addCode((unsigned short) num16, (unsigned short) (num16 >> 8));
					} else if (Z80Parser::checkToken(SP)) {
						Z80Parser::addCode(0xed, 0x73);
						Z80Parser::addCode((unsigned short) num16, (unsigned short) (num16 >> 8));
					} else if (Z80Parser::checkToken(HL)) {
						Z80Parser::addCode(0x22, (unsigned short) num16, (unsigned short) (num16 >> 8));
					} else if (Z80Parser::checkToken(IX)) {
						Z80Parser::addCode(0xdd, 0x22);
						Z80Parser::addCode((unsigned short) num16, (unsigned short) (num16 >> 8));
					} else if (Z80Parser::checkToken(IY)) {
						Z80Parser::addCode(0xfd, 0x22);
						Z80Parser::addCode((unsigned short) num16, (unsigned short) (num16 >> 8));
					} else {
						Z80Parser::error("Missing bracket.");
					}
				} else {
					Z80Parser::error( "Missing comma.");
				}
			} else {
				Z80Parser::error("Missing bracket.");
			}
		} else if (Z80Parser::checkAtom(atom)) {
			if (Z80Parser::checkToken(RIGHT_BRACKET)) {
				if (Z80Parser::checkToken(COMMA)) {
					if (Z80Parser::checkToken(A)) {
						Z80Parser::addCode(0x32);
						Z80Parser::addAddress(atom);
					} else if (Z80Parser::checkToken(BC)) {
						Z80Parser::addCode(0xed, 0x43);
						Z80Parser::addAddress(atom);
					} else if (Z80Parser::checkToken(DE)) {
						Z80Parser::addCode(0xed, 0x53);
						Z80Parser::addAddress(atom);
					} else if (Z80Parser::checkToken(SP)) {
						Z80Parser::addCode(0xed, 0x73);
						Z80Parser::addAddress(atom);
					} else if (Z80Parser::checkToken(HL)) {
						Z80Parser::addCode(0x22);
						Z80Parser::addAddress(atom);
					} else if (Z80Parser::checkToken(IX)) {
						Z80Parser::addCode(0xdd, 0x22);
						Z80Parser::addAddress(atom);
					} else if (Z80Parser::checkToken(IY)) {
						Z80Parser::addCode(0xfd, 0x22);
						Z80Parser::addAddress(atom);
					} else {
						Z80Parser::error("Missing bracket.");
					}
				} else {
					Z80Parser::error("Missing comma.");
				}
			} else {
				Z80Parser::error("Missing bracket.");
			}
		} else {
			Z80Parser::error( "An LD instruction must used Registers, immediate values OR addresses.");
		}
	} else {
		Z80Parser::errorState = true;
		Z80Parser::errorString = "An LD instruction must used Registers, immediate values OR addresses.";
	}
	
	if (!Z80Parser::checkToken(NEW_LINE) && !Z80Parser::errorState) {
		Z80Parser::errorState = true;
		Z80Parser::errorString = "An LD instruction must end in a new line.";
	}
	
	/*
	Template:
	if (Z80Parser::checkToken(A)) {
		
	} else if (Z80Parser::checkToken(B)) {
		
	} else if (Z80Parser::checkToken(C)) {
		
	} else if (Z80Parser::checkToken(D)) {
		
	} else if (Z80Parser::checkToken(E)) {
		
	} else if (Z80Parser::checkToken(H)) {
		
	} else if (Z80Parser::checkToken(L)) {
		
	} else {
		//ERROR HANDLER!!!!!!!!!!!!!!!
	}
	*/
}


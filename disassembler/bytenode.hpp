/*
	file name: bytenode.hpp
	date created: 3/8/2012
	date updated: 3/8/2012
	author: Gareth Richardson
	description: This is the header file for the data
	structure ByteNode. It is used with the ByteFile
	class to store the bytes of a file.
*/

typedef char BYTE;

struct ByteNode {
	BYTE value;
	ByteNode* next;
};

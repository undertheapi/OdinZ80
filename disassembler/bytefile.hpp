/*
	file name: bytefile.hpp
	date created: 3/8/2012
	date updated: 3/8/2012
	author: Gareth Richardson
	description: This is the class declaration of the
	ByteFile class. It is used to store the bytes of
	a binary file. Bytes can be pushed and popped onto
	it.
*/

#include "bytenode.hpp"

class ByteFile {
	private:
		ByteNode* head;
		ByteNode* tail;
	public:
		ByteFile();
		
		/*
			this is used to check if the queue is empty.
		*/
		bool isEmpty();
		
		/*
			pushes a byte to the back of the queue.
		*/
		void push(BYTE value);
		
		/*
			pops a byte from the front of a queue.
		*/
		BYTE pop();
};

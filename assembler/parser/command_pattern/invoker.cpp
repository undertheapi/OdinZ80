/*
	Copyright (c) 2015, Gareth Richardson
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
	file name: invoker.cpp
	date created: 05/12/2014
	date updated: 19/01/2015
	author: Gareth Richardson
	description: The object source code for the Invoker.
*/

#include "invoker.hpp"

#define NULL 0

void Invoker::init() {
	/*
		Defining the Single Linked List structure as well as setting it to empty.
	*/
	Invoker::head = NULL;
	Invoker::tail = NULL;
	
	Invoker::size = 0;
	
	/*
		Put all the ICommand Objects here that will go into the Invoker List;
	*/
}

void Invoker::populateCommands() {

}

void Invoker::setCommand(ICommand* command) {
	/*
		Initialise the Node here:
	*/
	InvokerNode* nodePointer = new InvokerNode;
	nodePointer->commandItem = command;
	nodePointer->next = NULL;
	
	/*
		The checks for an empty list or a size of 1 are done through the
		size attribute of the invoker.
	*/
	if (Invoker::size == 0) {
		Invoker::head = Invoker::tail = nodePointer;
	} else if (Invoker::size == 1) {
		Invoker::head->next = Invoker::tail = nodePointer;
	} else {
		Invoker::tail->next = nodePointer;
		Invoker::tail = nodePointer;
	}
	
	//Always increment the size of the Singly Linked List.
	++Invoker::size;
}

Invoker::Invoker() {
	Invoker::init();
	Invoker::populateCommands();
}

int Invoker::CommandCount() {
	return Invoker::size;
}

ICommand* Invoker::getCommand(int index) {
	if (Invoker::size != 0 && index < Invoker::size) {
		int accumulator = 0;
		InvokerNode pointer = Invoker::head;
		while (accumulator != index) {
			pointer = pointer->next;
			++accumulator;
		}
		return pointer->commandItem;
	}
	return NULL;
}

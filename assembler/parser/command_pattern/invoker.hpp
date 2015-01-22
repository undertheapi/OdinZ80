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
	file name: invoker.hpp
	date created: 04/12/2014
	date updated: 19/01/2015
	author: Gareth Richardson
	description: This is the Invoker for the Parser. All the Commands for the Parser are
	in here.
	It is a Singly Linked List of all the COmmands that we are going to need.
*/

#include "icommand.hpp"
#include "invokernode.hpp"

class Invoker {
	private:
		/*
			These two values are the head and tail for a Singly Linked List.
		*/
		InvokerNode* head;
		InvokerNode* tail;
		
		int size;
		
		Z80Parser* parserObj;
		
		void init();
		
		/*
			This method populates the Command List in the invoker.
			TO DO :: Can we use "Reflection" in this method.
		*/
		void populateCommands();
		
		void setCommand(ICommand command);
	public:
		Invoker(Z80Parser* obj);
		
		/*
			This gives you the amount of the commands in the Invoker.
		*/
		int commandCount();
		
		/*
			If this method returns a NULL reference, it means that the
			input index was out of range.
		*/
		ICommand* getCommand(int index);
};

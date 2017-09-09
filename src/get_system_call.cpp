/*
    HORSES - A High-Order Spectral Element Solver
    Copyright (C) 2017  Juan Manzanero (juan.manzanero@upm.es)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "get_system_call.h"
using namespace std;

/****************************************\
| 	SystemCall_t procedures 	 |
\****************************************/
SystemCall_t::SystemCall_t(const char *msg_in){
//	
//	Introuduce the requested message in this.message
//	------------------------------------------------
	strcpy( message, msg_in );
//
//	Reset no_of_outputLines
//	--------------------
	no_of_outputLines = 0;
//
//	Nullify the head
//	----------------
	head = NULL;

#ifdef _DEBUG
//
//	Print the message
//	-----------------
	Print_message();
#endif
//
//	Perform the call and get the output
//	-----------------------------------
	Perform_system_call();
} 

void SystemCall_t :: Perform_system_call(){

	FILE *stream = popen( message , "r" );

	char buffer[MAX_BUFFER_SIZE];
	
	SystemOutputLine_t *currentLine;
	currentLine = head;

	if ( stream ) {
		if ( fgets(buffer, sizeof(buffer), stream) != NULL){
//
//			popen buffers always end with \n
//			--------------------------------
			char* auxstr;
			auxstr = strstr(buffer,"\n");
			auxstr[0] = '\0';

			no_of_outputLines = 1;
			currentLine = new SystemOutputLine_t(buffer);
			head = currentLine;
		}

		while ( fgets(buffer, sizeof(buffer), stream) != NULL){
//
//			popen buffers always end with \n
//			--------------------------------
			char* auxstr;
			auxstr = strstr(buffer,"\n");
			auxstr[0] = '\0';

			no_of_outputLines++;
			currentLine->next = new SystemOutputLine_t(buffer);
			currentLine = currentLine->next;
		}
	}

#ifdef _DEBUG
	cout << "Number of messages after system call \"" << message ;
	cout <<  "\": " << no_of_outputLines << endl;
#endif

	pclose(stream);
}

char* SystemCall_t :: Get_output_line(const int i) const {

	if ( i > no_of_outputLines ) return NULL;

	char *output = new char[MAX_BUFFER_SIZE];

	SystemOutputLine_t *currentLine;
	currentLine = head;

	for (int j = 0; j < i; j++){
		currentLine = currentLine->next;		
	}

	strcpy( output, currentLine->msg );

	return output;
}

void SystemCall_t :: Print_message() const {
	cout << "Message introduced: " << message << endl;
}

void SystemCall_t :: Print_output() const {

	SystemOutputLine_t *currentLine;
	currentLine = head;

	for (int i = 0; i < no_of_outputLines; i++){
		currentLine->Print();
		currentLine = currentLine->next;
	}
}



/****************************************\
|	SystemOutputLine procedures 	 |
\****************************************/
SystemOutputLine_t::SystemOutputLine_t(char *msg_in){
	strcpy(msg, msg_in); 
	next = NULL;

}

void SystemOutputLine_t :: Print() const{
	cout << msg << endl;
}

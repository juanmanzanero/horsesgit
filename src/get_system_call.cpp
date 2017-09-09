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


/* 	SystemCall_t procedures 	*/

SystemCall_t::SystemCall_t(char *msg_in){

//	
//	Introuduce the requested message in this.message
//	------------------------------------------------
	strcpy( message, msg_in );
//
//	Reset no_of_messages
//	--------------------
	no_of_messages = 0;
//
//	Nullify the head
//	----------------
	head = NULL;
//
//	Print the message
//	-----------------
#ifdef _DEBUG
	print_message();
#endif

} 

void SystemCall_t::print_message(){
	cout << "Message introduced: " << message << endl;
}

void get_command_line(){

	const int MAX_BUFFER = 2048;
	char buffer[MAX_BUFFER];
	FILE *stream = popen("git status -uno", "r");

	if ( stream ) {
		while ( fgets(buffer, sizeof(buffer), stream) != NULL){
//			cout << buffer << endl;
		}
	}
	pclose(stream);

}

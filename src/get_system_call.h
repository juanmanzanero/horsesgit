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

#ifndef __GET_SYSTEM_CALL_H__
#define __GET_SYSTEM_CALL_H__


const int MAX_BUFFER_SIZE = 2048;
const int MAX_MESSAGE_SIZE = 2048;

class SystemCall_t;

class SystemOutputLine_t{
	friend class SystemCall_t;

	private:
		char msg[MAX_BUFFER_SIZE];
		SystemOutputLine_t  *next;
	public:
		SystemOutputLine_t(char *msg_in);
		void Print() const;	

};

class SystemCall_t {
	private:
		SystemOutputLine_t *head;
		void Perform_system_call();
		void Print_message() const;
	public:
		int no_of_outputLines;
		char message[MAX_MESSAGE_SIZE];
		SystemCall_t(const char *command);
		char* Get_output_line(const int) const;	
		void Print_output() const;
};


void get_command_line();


#endif  /*  __GET_SYSTEM_CALL_H__ */



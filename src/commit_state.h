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

#ifndef __COMMIT_STATE_H__
#define __COMMIT_STATE_H__

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "get_system_call.h"
#include "git_message_library.h"

using namespace std;

const int MAX_COMMITSTATE_LEN = 2048;

class CommitState_t{

	private:
		//File_t *changed_files;	
		int no_of_newfiles;
		int no_of_modifiedfiles;
		static char* getBranch(const SystemCall_t&);
//		void getFiles();
		void getFileNames(const SystemCall_t&, int *no_of_modified, char (*&modified)[MAX_BUFFER_SIZE], int *no_of_new, char (*&new_files)[MAX_BUFFER_SIZE]);

	public:
		CommitState_t();
		char *branch;


};


#endif 	/*  __COMMIT_STATE_H__  */

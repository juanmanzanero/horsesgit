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

#include "commit_state.h"
#include "string_utils.h"

CommitState_t :: CommitState_t(){

	SystemCall_t status( GIT_STATUS_MSG );

	branch = getBranch(status);

#ifdef _DEBUG	
	cout << "The branch is " << branch << "." << endl;
#endif
}

char* CommitState_t :: getBranch(const SystemCall_t& status){

	char *line;
	char *branchname = new char[MAX_COMMITSTATE_LEN];
	int on_branch_size = strlen("On branch ");
	
	for (int i = 0; i < status.no_of_outputLines; i++){
		line = status.Get_output_line(i);	
		if ( strstr(line,"On branch") != NULL ){
			strncpy(branchname, line + on_branch_size, strlen(line)+1-on_branch_size);
		}
	}

/*	Remove all trailing whitespaces     */
	return branchname;
}

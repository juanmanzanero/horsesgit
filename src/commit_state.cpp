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
#include "git_message_library.h"
#include "string_utils.h"

CommitState_t :: CommitState_t(){

	SystemCall_t status( GIT_STATUS_MSG );

	branch = getBranch(status);

#ifdef _DEBUG	
	cout << "The branch is " << branch << "." << endl;
#endif

	char (*modified)[MAX_BUFFER_SIZE], (*new_files)[MAX_BUFFER_SIZE];

	getFileNames(status, &no_of_modifiedfiles, modified, &no_of_newfiles, new_files );

#ifdef _DEBUG
	cout << "Number of new files: " << no_of_newfiles << endl;
	cout << "Number of modified files: " << no_of_modifiedfiles << endl;

	for ( int i = 0; i < no_of_newfiles;){
		cout << "New file " << ++i << ": " << new_files[i] << endl;
	}

	for ( int i = 0; i < no_of_modifiedfiles;){
		cout << "Modified file " << ++i << ": " << modified[i] << endl;
	}
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

	return branchname;
}

void CommitState_t :: getFileNames(const SystemCall_t& status,  	   \
				   int *no_of_modified, char (*&modified)[MAX_BUFFER_SIZE],   \
				   int *no_of_new     , char (*&new_files)[MAX_BUFFER_SIZE]){

	*no_of_modified = 0;
	*no_of_new = 0;
//
//	First loop: get how many new and modified files are staged
// 	----------------------------------------------------------
	char *line;
	bool insideStaged = false;

	for (int i = 0; i < status.no_of_outputLines; i++){
		line = status.Get_output_line(i);

		if ( strstr( line, GIT_START_STAGED ) != NULL ) {
			insideStaged = true;
			continue;
		}

		if ( strstr( line, GIT_END_STAGED ) != NULL ){
			insideStaged = false;
			continue;
		}

		if ( insideStaged ) {
	
			if ( strstr(line, GIT_MODIFIEDFILE_MSG ) != NULL ){
				(*no_of_modified)++;

			}else if ( strstr(line, GIT_NEWFILE_MSG ) != NULL ){
				(*no_of_new)++;
		
			}
		}
	}
//
//	Allocate memory
//	---------------
	modified = new char[*no_of_modified][MAX_BUFFER_SIZE];
	new_files = new char[*no_of_new][MAX_BUFFER_SIZE];
//
//	Second loop: assign the modified and new file names
//	---------------------------------------------------
	insideStaged = false;

	int currentNew = 0;
	int currentModified = 0;

	for ( int i = 0; i < status.no_of_outputLines; i++ ){
		line = status.Get_output_line(i);

		if ( strstr( line , GIT_START_STAGED ) != NULL ) {
			insideStaged = true;
			continue;
		} else if ( strstr(line, GIT_END_STAGED) != NULL ) {
			insideStaged = false;
			continue;
		}

		if ( insideStaged ) {

			if ( strstr(line, GIT_MODIFIEDFILE_MSG ) != NULL ) {
//
//				Current line is a modified file
//				-------------------------------
				strncpy(modified[currentModified++], line + strlen(GIT_MODIFIEDFILE_MSG) + 1, MAX_BUFFER_SIZE );
			} else if ( strstr(line, GIT_NEWFILE_MSG ) != NULL ) {
//
//				Current line is a new file
//				--------------------------
				strncpy(new_files[currentNew++], line + strlen(GIT_NEWFILE_MSG) + 1, MAX_BUFFER_SIZE );
         }
		}
	}
}

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
#include <stdlib.h>
#include <string.h>
#include "gitcommand.h"
#include "commit_state.h"
#include "file_class.h"

using namespace std;

const int MESSAGE_MAX_LENGTH = 512;

int git_command(int argc, const char* argv[]){

	if ( !IsCommitMessage(argc, argv) ){
		char message[MESSAGE_MAX_LENGTH];
		strcpy(message, "git");
		for ( int i = 1; i < argc; i++ ){
			strcat(message, " ");
			strcat(message, argv[i]);
		}
		return system(message);
	}

/*	Otherwise, get the status of the code     */
   int exit_code;
	CommitState_t commitState(exit_code);

   if ( exit_code == File_t :: CONTINUE ){   
      char commitmsg[512];
      strcpy(commitmsg,"git ");
      for (int i = 1; i < argc; i++){
         strcat(commitmsg," ");
         strcat(commitmsg,argv[i]);
      }

      system(commitmsg);
      return 0;

   }else if ( exit_code == File_t :: ABORT ){
      cout << "ABORTED." << endl;
      return 0;

   }

}


bool IsCommitMessage(const int argc, const char* argv[]){
   if ( strcmp(argv[1], "commit") == 0 ) return true;
   else return false;
}

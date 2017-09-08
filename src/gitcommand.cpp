#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "gitcommand.h"

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
		cout << message << endl;
		return system(message);
	}
}


bool IsCommitMessage(const int argc, const char* argv[]){

//	Check if the arguments number is 4: git commit -m "Message"
	if ( argc != 4 ) return false;
cout << "There are four arguments" << endl;

//	If does, check if the second argument is commit
	if ( strcmp(argv[1],"commit") ) return false;
cout << "The second is commit" << endl;

// 	If does, check if the third argument is "-m"
	if ( strcmp(argv[2], "-m") ) return false;
cout << "The third is -m" << endl;

//	If does, it is a commit message
	return true;
}

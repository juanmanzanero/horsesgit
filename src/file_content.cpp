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
#include <string.h>
#include "file_content.h"
using namespace std;



/*****************************************
   FileContent class procedures
*****************************************/
FileContent_t :: FileContent_t(const char *_file_name){
//
// Get the file name
// -----------------
   strcpy( name, _file_name );
//
// Reset the number of lines
// -------------------------
   no_of_lines = 0;
//
// Nullify the head
// ----------------
   firstLine = NULL;
//
// Read the file
// -------------
   Read();
}

void FileContent_t :: Read(){
//
// Open the file
// -------------
   FILE *fID;
   char currentLine[MAX_LINE_LEN];

   fID = fopen( name, "r" );
//
// Check if the opening is successful
// ----------------------------------
   if ( fID == NULL ) return;   
//
// Read the file
// -------------
   FileLine_t *current;
   if ( fgets(currentLine, MAX_LINE_LEN, fID) != NULL ){
//
//    Remove the \n terminator
//    ------------------------
      char* auxstr;
		auxstr = strstr(currentLine,"\n");
		auxstr[0] = '\0';
//
//    Add the first line
//    ------------------
      no_of_lines = 1;
      current = new FileLine_t(currentLine);
      firstLine = current;
   }


   while ( fgets(currentLine, MAX_LINE_LEN, fID ) != NULL ){
//
//    Remove the \n terminator
//    ------------------------
      char* auxstr;
		auxstr = strstr(currentLine,"\n");
		auxstr[0] = '\0';
//
//    Add the lines
//    -------------
      no_of_lines++;
      current->nextLine = new FileLine_t(currentLine);
      current = current -> nextLine;

   }

   current = firstLine;
   for ( int i = 0; i < no_of_lines; i++ ){
      cout << current->line << endl;
      current = current -> nextLine;
   }

}


/****************************************
   FileLine class procedures
****************************************/
FileLine_t :: FileLine_t(const char *_line){
//
// Get the file line
// -----------------
   strcpy( line, _line );
//
// Nullify the next link in the list
// ---------------------------------
   nextLine = NULL;

}

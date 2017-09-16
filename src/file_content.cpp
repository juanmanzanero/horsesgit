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
      current = current -> nextLine;
   }

}

void FileContent_t :: AddLine(const int pos, const char* text){
//
// Create the new line
// -------------------
   FileLine_t *line = new FileLine_t(text);
   FileLine_t *current;
   FileLine_t *prev;

   if ( pos == 0 ) {
      current = firstLine;
      firstLine = line;
      line -> nextLine = current;
      no_of_lines++;
  } else if ( pos == no_of_lines - 1 ){
      current = firstLine -> nextLine;
      prev = firstLine;

      for ( int i = 1; i < pos; i++ ){
         current = current -> nextLine;
         prev = prev -> nextLine;
      } 
      
      prev -> nextLine = line;
      line -> nextLine = NULL;
      no_of_lines++;

  } else {
      current = firstLine -> nextLine;
      prev = firstLine;

      for ( int i = 1; i < pos; i++ ){
         current = current -> nextLine;
         prev = prev -> nextLine;
      } 
      
      prev -> nextLine = line;
      line -> nextLine = current;
      no_of_lines++;
   }
}

void FileContent_t :: DeleteLine(const int line){

   FileLine_t *current = firstLine;
   FileLine_t *prev = firstLine;

   if ( line == 0 ){
//
//    Remove the head
//    ---------------
      firstLine = current -> nextLine;
      no_of_lines--;
      delete current;
   } else if ( line == no_of_lines - 1){
//
//    Advance to the final line
//    -------------------------
      current = firstLine -> nextLine;
      for ( int i = 1; i < no_of_lines-1; i++ ){
         current = current -> nextLine;
         prev = prev -> nextLine;
      }
//
//    Remove the line
//    ---------------
      no_of_lines--;
      prev -> nextLine = NULL;
      delete current; 

   } else {
//
//    Advance to the requested line
//    -----------------------------
      current = firstLine -> nextLine;
      for ( int i = 1; i < line; i++ ){
         current = current -> nextLine;
         prev = prev -> nextLine;
      }
//
//    Remove the line
//    ---------------
      prev -> nextLine = current -> nextLine;
      no_of_lines--;
      delete current;         
   }
}

void FileContent_t :: Dump(){
   
   FileLine_t *current;

   current = firstLine;
   for ( int i = 0; i < no_of_lines; i++){
      cout << current -> line << endl;
      current = current->nextLine;
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

FileLine_t :: ~FileLine_t(){
   line[0] = '\0';
   nextLine = NULL;
}

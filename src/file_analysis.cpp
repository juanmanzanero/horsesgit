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
#include <stdio.h>
#include "file_analysis.h"
#include "file_content.h"
using namespace std;

int* checkIfTagIsPresent( FileContent_t *file, const FileTag_t tagID ){
//
// Define the return value
// -----------------------
   int *position = NULL;
//
// Get the tag
// -----------
   const char *tag = getTagFromID(tagID);
//
// Loop the list until the tag is found
// ------------------------------------
   FileLine_t  *line = file -> firstLine;
   char        *uncommentedLine = NULL;
   for (int i = 0; i < file->no_of_lines; i++){
//
//    Get the commented part of the line
//    ----------------------------------
	   uncommentedLine = strstr(line->line,COMMENT_TAG);
//
//    Exit if the line is not commented
//    ---------------------------------
      if ( uncommentedLine == NULL ) {line = line->nextLine; continue; }
//
//    Look for the tag in the commented part
//    --------------------------------------
      if ( strstr(uncommentedLine, tag) == NULL ) { line = line->nextLine; continue; }
      else{
         position = new int;
         *position = i;     
         return position;
      }
//
//    Loop to the next link in the chain
//    ----------------------------------
      line = line -> nextLine;

   }

   return NULL;
} 

const char* getTagFromID(const FileTag_t tagID){

      const char *tag = NULL;

      switch ( tagID ){
         case(FILETAG):
            tag = FileTag;
            break;
      
         case(AUTHORTAG):
            tag = AuthorTag;
            break;

         case(CREATEDTAG):
            tag = CreatedTag;
            break;

         case(LASTREVISIONTAG):
            tag = LastRevisionTag;
            break;

         case(NUMBER_OF_TAGS):
            tag = NULL;
            break;

         default:
            tag = NULL;
            break;
      }
   
      return tag;
}

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


#include <string.h>
#include <iostream>
#include "file_content.h"
#include "file_analysis.h"
#include "file_class.h"
using namespace std;


const char* File_t :: file_formats[] = {".f90",".incf"};
const int   File_t :: no_of_file_formats = 2;

/**************************************************************
*  Default constructor: needed for dynamic memory allocation  *
**************************************************************/
File_t::File_t(){};

/**************************************************************
*  Real constructor: invoked once the instances are created   *
**************************************************************/
File_t::File_t(const char* _name, const Filetype_t _type){
//
// Get the file name
// -----------------
   strcpy( name, _name );
//
// Get the file type
// -----------------
   filetype = _type;
};

void File_t :: Describe(){
      cout << "File \"" ; 
      cout << name << "\"";
   
      switch (filetype) { 
         case NEWFILE: 
              cout << " is new file." << endl;
              break;

         case MODIFIEDFILE: 
              cout << " is modified file." << endl;
              break;
      }
}

void File_t :: WriteFile(){
   switch (filetype){
      case NEWFILE:
         WriteNewFile();
         break;

      case MODIFIEDFILE:
         WriteModifiedFile();
         break;
   }
}

void File_t :: WriteNewFile(){
   cout << "File " << name << " is being modified" << endl;

   FileContent_t  fileContent( name );

   int *tagPositions[NUMBER_OF_TAGS];

   for ( int i = 0; i < NUMBER_OF_TAGS; i++ ){
      
      tagPositions[i] = checkIfTagIsPresent( &fileContent, FileTag_t(i) );
      cout << tagPositions[i] << endl;
   }
   

}

void File_t :: WriteModifiedFile(){
   cout << "File " << name << " is being modified" << endl;
}
      

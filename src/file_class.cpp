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
#include <time.h>
#include "string_utils.h"
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
// Get the file name
// -----------------
   fileName = removePath(&name[0]);
//
// Get the file type
// -----------------
   filetype = _type;
};

void File_t :: Describe(){
      cout << "File \"" ; 
      cout << name << "\"";
//      cout << fileName ;
   
      switch (filetype) { 
         case NEWFILE: 
              cout << " is new file." << endl;
              break;

         case MODIFIEDFILE: 
              cout << " is modified file." << endl;
              break;
      }
}
/****************************************************************
*  Copy constructor
****************************************************************/
File_t& File_t :: operator=(const File_t& other)
{
/*  Copy the name   */
    strcpy(name, other.name);

/*  Point to the local file name */
    fileName = &name[0] + (other.fileName - &other.name[0]);

/*  Get the file type */
    filetype = other.filetype;

    return *this;
}

int File_t :: WriteFile(const char *username, const char *useremail, const char* commitsha){

   switch (filetype){
      case NEWFILE:
         return WriteNewFile(username, useremail);
         break;

      case MODIFIEDFILE:
         return WriteModifiedFile(username, useremail, commitsha);
         break;
   }
}

int File_t :: WriteNewFile(const char* username, const char* useremail){

   FileContent_t  fileContent( name );

   int *tagPosition;

   for ( int i = 0; i < NUMBER_OF_TAGS; i++ ){
//
//    If any tag is presented, delete their associated lines
//    ------------------------------------------------------
      tagPosition = checkIfTagIsPresent( &fileContent, FileTag_t(i) );
      if ( tagPosition != NULL) {
         fileContent.DeleteLine(*tagPosition);
      }
   }
//
// Introduce the labels at the beginning of the file
// -------------------------------------------------
   char auxstr[MAX_FILE_LEN];
   fileContent.AddLine(0,"!");
   fileContent.AddLine(1,"!//////////////////////////////////////////////////////");
   fileContent.AddLine(2,"!");

   strcpy(auxstr, "!   @File:    ");
   strcat(auxstr,fileName); 
   fileContent.AddLine(3,auxstr);

   strcpy(auxstr, "!   @Author:  ");
   strcat(auxstr,username);
   strcat(auxstr," (");
   strcat(auxstr,useremail);
   strcat(auxstr,")");
   fileContent.AddLine(4,auxstr);

   time_t now;
   time(&now);
   strcpy(auxstr,"!   @Created: ");
   strcat(auxstr,ctime(&now));
   char* auxauxstr = strstr(auxstr,"\n");    /* ctime adds a newline */
   auxauxstr[0] = '\0';
   fileContent.AddLine(5,auxstr);
   fileContent.AddLine(6,"!   @Last revision date:");
   fileContent.AddLine(7,"!   @Last revision author:");
   fileContent.AddLine(8,"!   @Last revision commit:");
   fileContent.AddLine(9,"!");
   fileContent.AddLine(10,"!//////////////////////////////////////////////////////");
   fileContent.AddLine(11,"!");

   fileContent.Dump();

#ifdef SECURE_MODE
   return AskConfirmation();
#else
   return CONTINUE;
#endif
   
}

int File_t :: WriteModifiedFile(const char* username, const char* useremail, const char* commitsha){

   
   FileContent_t fileContent( name );

   int *lastRevisionDateTagPosition;

   lastRevisionDateTagPosition = checkIfTagIsPresent( &fileContent, LASTREVISIONDATETAG );

   if ( lastRevisionDateTagPosition != NULL ){
//   
//    Remove the last revision current line
//    -------------------------------------
      fileContent.DeleteLine(*lastRevisionDateTagPosition);
//   
//    Create the new last revision line content
//    -----------------------------------------
      char auxstr[MAX_FILE_LEN];
      strcpy(auxstr,"!   @Last revision date: ");
//   
//    Append the date
//    ---------------
      time_t now;
      time(&now);
      strcat(auxstr,ctime(&now));
      char* auxauxstr = strstr(auxstr,"\n");
      auxauxstr[0] = '\0';
//
//    Insert the line
//    ---------------
      fileContent.AddLine(*lastRevisionDateTagPosition,auxstr);
   }

   int *lastRevisionAuthorTagPosition;

   lastRevisionAuthorTagPosition = checkIfTagIsPresent( &fileContent, LASTREVISIONAUTHORTAG);

   if ( lastRevisionAuthorTagPosition != NULL ){
//
//    Remove last revision author line
//    --------------------------------
      fileContent.DeleteLine(*lastRevisionAuthorTagPosition);
//
//    Create the new last revision author content
//    -------------------------------------------
      char auxstr[MAX_FILE_LEN];
      strcpy( auxstr, "!   @Last revision author: ");
//
//    Append author data
//    ------------------
      strcat(auxstr,username);
      strcat(auxstr," (");
      strcat(auxstr,useremail);
      strcat(auxstr,")");
//
//    Insert the line
//    ---------------
      fileContent.AddLine(*lastRevisionAuthorTagPosition, auxstr);
   }

   int *lastRevisionCommitTagPosition;

   lastRevisionCommitTagPosition = checkIfTagIsPresent( &fileContent, LASTREVISIONCOMMITTAG);

   if ( lastRevisionCommitTagPosition != NULL ){
//
//    Remove last revision commit line
//    --------------------------------
      fileContent.DeleteLine(*lastRevisionCommitTagPosition);
//
//    Create the last revision commit content
//    ---------------------------------------
      char auxstr[MAX_LINE_LEN];
      strcpy(auxstr,"!   @Last revision commit: ");
//
//    Append commit info
//    ------------------
      strcat(auxstr, commitsha);
//
//    Insert the line
//    ---------------
      fileContent.AddLine(*lastRevisionCommitTagPosition, auxstr);
   }

   fileContent.Dump();

#ifdef SECURE_MODE
   return AskConfirmation();
#else
   return CONTINUE;
#endif


}

int File_t :: AskConfirmation(){

   cout << "Showing modifications for file " << name << ":" << endl << endl;
   
   char command[MAX_LINE_LEN];
   strcpy(command, "git diff ./");
   strcat(command, name);

   system(command);

// Prompt for confirmation
// -----------------------
   cout << "Choose yes/no to confirm changes: ";
   string confirm;
   cin >> confirm;

   if ( strcmp(confirm.c_str(),"yes") == 0 ){
      strcpy(command, "git add ./");
      strcat(command, name);
      system(command);
      return CONTINUE;

   }else{
      return ABORT;

   }

}
      

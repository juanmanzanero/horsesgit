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

#ifndef __FILE_CLASS_H__
#define __FILE_CLASS_H__

const int MAX_FILE_LEN = 2048;

class File_t{

/* Properties */
   public:
      enum Filetype_t{ NEWFILE, MODIFIEDFILE };
      enum Action_t{CONTINUE, ABORT};
      const static char* file_formats[]; //= {".f90",".incf"};
      const static int no_of_file_formats;
      char *fileName;

   private:
      char name[MAX_FILE_LEN];
      Filetype_t filetype;
       
/* Methods */
   public:
      File_t();
      File_t(const char*, const Filetype_t);
      File_t& operator=(const File_t& other);
      void Describe();
      int WriteFile(const char*, const char*, const char*);
      int WriteNewFile(const char*, const char*);
      int WriteModifiedFile(const char*, const char*, const char*);
      int AskConfirmation();

};



#endif /* __FILE_CLASS_H__ */

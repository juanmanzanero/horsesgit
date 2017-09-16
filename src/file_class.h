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

   public:
      enum Filetype_t{ NEWFILE, MODIFIEDFILE };
      const static char* file_formats[]; //= {".f90",".incf"};
      const static int no_of_file_formats;

   private:
      char name[MAX_FILE_LEN];
      Filetype_t filetype;
       
   public:
      File_t();
      File_t(const char*, const Filetype_t);
      void Describe();
      void WriteFile(const char*, const char*);
      void WriteNewFile(const char*, const char*);
      void WriteModifiedFile();

};



#endif /* __FILE_CLASS_H__ */

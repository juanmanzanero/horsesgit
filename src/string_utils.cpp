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
#include "string_utils.h"
using namespace std;


void string_trim(char* str){

	char* aux;

	std:: cout << "La string es " << str << std :: endl;
	aux = strstr(str, " ");
	std :: cout << aux << std :: endl;
	aux[0] = '\0';

}


char* removePath( char *name ){
//
// Create variables
// ----------------
   char *fileName;
//
// Find the last forward slash entry
// ---------------------------------
   fileName = strrchr(name, '/');

   if ( fileName == NULL ) fileName = name;
   else fileName = fileName + 1 ;
   

   return fileName;

}

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

#ifndef __FILE_CONTENT_H__
#define __FILE_CONTENT_H__

const int MAX_LINE_LEN = 2048;

class FileContent_t;

class FileLine_t{

	friend class FileContent_t;

	private:

	public:
		char line[MAX_LINE_LEN];
		FileLine_t *nextLine;

	public:
		FileLine_t(const char *_line);
       ~FileLine_t();

};


class FileContent_t{


	private:

	public: 
		int no_of_lines;
		char name[MAX_LINE_LEN];
		FileLine_t *firstLine;

	private: 
		void Read();

	public:
		FileContent_t(const char*);
		void AddLine(const int, const char*);
		void DeleteLine(const int);
		void Dump();

};

#endif /* __FILE_CONTENT_H__ */

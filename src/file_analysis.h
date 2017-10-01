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

#ifndef __FILE_ANALYSIS_H__
#define __FILE_ANALYSIS_H__

#include "file_content.h"

enum FileTag_t { FILETAG, AUTHORTAG, CREATEDTAG, \
                LASTREVISIONDATETAG, LASTREVISIONAUTHORTAG, \
                LASTREVISIONCOMMITTAG, NUMBER_OF_TAGS };

const static char FileTag[]="@File:";
const static char AuthorTag[]="@Author:";
const static char CreatedTag[]="@Created:";
const static char LastRevisionDateTag[]="@Last revision date:";
const static char LastRevisionAuthorTag[]="@Last revision author:";
const static char LastRevisionCommitTag[]="@Last revision commit:";
const static char COMMENT_TAG[] = "!";

int* checkIfTagIsPresent(FileContent_t*, const FileTag_t);
const char* getTagFromID(const FileTag_t);

#endif

/* Copyright 2017 The serverX Authors. All Rights Reserved.
 * Maintainer: Bytes Club (https://bytesclub.github.io)<bytes-club@googlegroups.com>

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
==============================================================================*/

// Library Source File
// serverXL.c

// include header
#include <serverXL.h>

// global variables

extern char* root;
extern int cfd, sfd;
extern bool signaled;

/**
 * Checks, in order, whether index.php or index.html exists inside of path.
 * Returns path to first match if so, else NULL.
 */
char* indexes(const char* path)
{
    char *file = malloc(strlen(path) + 10);
    strcpy(file, path);
    strcat(file, "index.php");

    if (! access(file, F_OK)) {
        return file;
    } else if (strcpy(strstr(file, ".php"), ".html") && ! access(file, F_OK)) {
        return file;
    }
    //default return
    return NULL;
}
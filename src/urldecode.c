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
 * URL-decodes string, returning dynamically allocated memory for decoded string
 * that must be deallocated by caller.
 */
char* urldecode(const char* s)
{
    // check whether s is NULL
    if (s == NULL)    return NULL;

    // allocate enough (zeroed) memory for an undecoded copy of s
    char* t = calloc(strlen(s) + 1, 1);
    if (t == NULL)    return NULL;

    // iterate over characters in s, decoding percent-encoded octets, per
    // https://www.ietf.org/rfc/rfc3986.txt
    for (int i = 0, j = 0, n = strlen(s); i < n; i++, j++) {
        if (i < n - 2 && s[i] == '%') {
            char octet[3];
            octet[0] = s[i + 1];
            octet[1] = s[i + 2];
            octet[2] = '\0';
            t[j] = (char) strtol(octet, NULL, 16);
            i += 2;
        } else if (s[i] == '+') {
            t[j] = ' ';
        } else {
            t[j] = s[i];
        }
    }

    // escaped string
    return t;
}
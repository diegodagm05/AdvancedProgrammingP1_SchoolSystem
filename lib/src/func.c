/*
*   Diego Guerrero - A01625199
*   Tecnologico de Monterrey | Advanced Programming - Project 1
*   Functions Definition
*/

#include "func.h"
#include <stdio.h>

//implementation of functions goes here

int fileLines(FILE* fp)
{
    int flines = 0;
    int ch;
    while (!feof(fp)){
        ch = fgetc(fp);
        if (ch == '\n') {
            flines++;
        }
    }

    fseek(fp, 0, SEEK_SET);
    return flines;
}
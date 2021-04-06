/*
*   Diego Guerrero - A01625199
*   Tecnologico de Monterrey | Advanced Programming - Project 1
*   Functions Declaration
*/

//Functions and struct Declaration goes here

#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>

typedef struct{
  int id;
  char name[40];
  char major[4];
  char city[15];
  char graduation[10];
} student;

typedef struct{
  int id;
  int a;
  int b;
  int c;
  int d;
} sgrades;

int fileLines(FILE* fp);

#endif

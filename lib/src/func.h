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
  int a,b,c,d;
} sgrades;

int fileLines(FILE* fp);

sgrades kardex(sgrades *grade[], int n, int id);

char* graduationDate(student *stud[], int n, int id);

int studentsNumMajorCity(student *stud[], int n, char major[], char city[]);

int studentsNumMajor(student *stud[], int n, char major[]);

int studentsNumHandler(student *stud[], int n, char buff[]);

void studentsNameMajorCity(student *stud[], int n, char major[], char city[],char *names[]);

void studentsNameMajor(student *stud[], int n, char major[], char *names[]);

void studentsNameHandler(student *stud[], int n, char buff[], char *names[]);

int studentsNameOperatorNum(sgrades *grades[], int n, char *operator, int value);

void studentsNameOperator(sgrades *grades[], int n, char *operator, int value, int *ids);

#endif

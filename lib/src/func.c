/*
*   Diego Guerrero - A01625199
*   Tecnologico de Monterrey | Advanced Programming - Project 1
*   Functions Definition
*/

#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//implementation of functions goes here

int fileLines(FILE* fp){
    
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

sgrades kardex(sgrades *grade[], int n, int id){
  sgrades ans;
  ans.id = -1;
  for (int i=0; i<n; i++){
    if( (*grade+i)->id == id){
      ans.id = (*grade+i)->id;
      ans.a = (*grade+i)->a; ans.b = (*grade+i)->b;
      ans.c = (*grade+i)->c; ans.d = (*grade+i)->d;
      break;
    }
  }
  return ans;
}

char* graduationDate(student *stud[], int n, int id){
  for (int i=0; i<n; i++){
    if((*stud+i)->id == id){
      return (*stud+i)->graduation;
    }
  }
  return "/";
}

int studentsNumMajorCity(student *stud[], int n, char major[], char city[]){
  int studentCount = 0;
  for (int i=0; i<n; i++){
    if(!strcmp((*stud+i)->major,major) && !strcmp((*stud+i)->city, city)){
      studentCount++;
    }
  }
  return studentCount;
}

int studentsNumMajor(student *stud[], int n, char major[]){
  int studentCount = 0;
  for (int i=0; i<n; i++){
    if(!strcmp((*stud+i)->major, major)){
      studentCount++;
    }
  }
  return studentCount;
}

int studentsNumHandler(student *stud[], int n, char buff[]){
  
  int argsc = 0;
  char *token = strtok(buff, " ");
  char *argsv[2];

  while (token != NULL){
    argsv[argsc++] = token;
    token = strtok(NULL, " ");
  }
  if( !strcmp(argsv[0],"*") && argsc==1)
    argsc = 0;
  switch (argsc){
    case 0:
      return n;
    case 1:
      return studentsNumMajor(stud, n, argsv[0]);
    case 2:
      return studentsNumMajorCity(stud, n, argsv[0], argsv[1]);
  }
}

void studentsNameMajorCity(student *stud[], int n, char major[], char city[],char *names[]){
  int j=0;
  for (int i=0; i<n; i++){
    if(!strcmp((*stud+i)->major,major) && !strcmp((*stud+i)->city, city)){
      names[j++] = (*stud+i)->name;
    }
  }
}

void studentsNameMajor(student *stud[], int n, char major[], char *names[]){
  int j=0;
  for (int i=0; i<n; i++){
    if(!strcmp((*stud+i)->major, major)){
      names[j++] = (*stud+i)->name;
    }
  }
}

void studentsNameHandler(student *stud[], int n, char buff[], char *names[]){
  int argsc = 0;
  char *token = strtok(buff, " ");
  char *argsv[2];

  while (token != NULL){
    argsv[argsc++] = token;
    token = strtok(NULL, " ");
  }
  if( !strcmp(argsv[0],"*") && argsc==1)
    argsc = 0;
  switch (argsc){
    case 0:
      for(int i=0; i<n;i++){
        names[i] = (*stud+i)->name;
      }
      break;
    case 1:
      studentsNameMajor(stud, n, argsv[0], names);
      break;
    case 2:
      studentsNameMajorCity(stud, n, argsv[0], argsv[1], names);
      break;
  }
}

int studentsNameOperatorNum(sgrades *grades[], int n, char *operator, int value){
  int total=0, avgs[n];
  for(int i=0; i<n; i++){
    avgs[i] = ( (*grades+i)->a + (*grades+i)->b + (*grades+i)->c + (*grades+i)->d ) /4;
  }
  
  if(!strcmp(operator, "<")){
    for(int i=0; i<n; i++){
      if( avgs[i] < value){
        total++;
      }
    }
  }
  else if(!strcmp(operator, ">")){
    for(int i=0; i<n; i++){
      if( avgs[i] > value){
        total++;
      }
    }
  }
  else if(!strcmp(operator, "==")){
    for(int i=0; i<n; i++){
      if( avgs[i] == value){
        total++;
      }
    }
  }
  else if(!strcmp(operator, "!=")){
    for(int i=0; i<n; i++){
      if( avgs[i] != value){
        total++;
      }
    }
  }
  return total;
}

void studentsNameOperator(sgrades *grades[], int n, char *operator, int value, int *ids){
  int avgs[n], j=0;
  for(int i=0; i<n; i++){
    avgs[i] = ( (*grades+i)->a + (*grades+i)->b + (*grades+i)->c + (*grades+i)->d ) /4;
  }
  if(!strcmp(operator, "<")){
    for(int i=0; i<n; i++){
      if( avgs[i] < value){
        ids[j++] = (*grades+i)->id;
      }
    }
  }
  else if(!strcmp(operator, ">")){
    for(int i=0; i<n; i++){
      if( avgs[i] > value){
        ids[j++] = (*grades+i)->id;
      }
    }
  }
  else if(!strcmp(operator, "==")){
    for(int i=0; i<n; i++){
      if( avgs[i] == value){
        ids[j++] = (*grades+i)->id;
      }
    }
  }
  else if(!strcmp(operator, "!=")){
    for(int i=0; i<n; i++){
      if( avgs[i] != value){
        ids[j++] = (*grades+i)->id;
      }
    }
  }
  // return ids;
}
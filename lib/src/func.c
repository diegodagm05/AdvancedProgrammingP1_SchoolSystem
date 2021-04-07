/*
*   Diego Guerrero - A01625199
*   Tecnologico de Monterrey | Advanced Programming - Project 1
*   Functions Definition
*/

#include "func.h"
#include <stdio.h>

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

void kardex(sgrades grade[], int n, int id){
  for (int i=0; i<n; i++){
    if(grade[i].id == id){
      printf("ID: %d A:%d B:%d C:%d D:%d\n", grade[i].id, grade[i].a, grade[i].b, grade[i].c, grade[i].d);
      return;
    }
  }
  printf("Estudiante con id [%d] no encontrado\n",id);
}

void graduationDate(student stud[], int n, int id){
  for (int i=0; i<n; i++){
    if(stud[i].id == id){
      printf("Fecha: %s\n", stud[i].graduation);
      return;
    }
  }
  printf("Estudiante con id [%d] no encontrado\n",id);
}

int studentsNumMajorCity(student stud[], int n, char major[], char city[]){
  int studentCount = 0;
  for (int i=0; i<n; i++){
    if(stud[i].major == major && stud[i].city == city){
      studentCount++;
    }
  }
  return studentCount;
}

int studentsNumMajor(student stud[], int n, char major[]){
  int studentCount = 0;
  for (int i=0; i<n; i++){
    if(stud[i].major == major){
      studentCount++;
    }
  }
  return studentCount;
}
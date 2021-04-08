/*
*   Diego Guerrero - A01625199
*   Tecnologico de Monterrey
*   Advanced Programming - Project 1
*/

// #include "../lib/src/func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  for (int i=0; i<n; i++){
    if( (*grade+i)->id == id){
      // printf("ID: %d A:%d B:%d C:%d D:%d\n", grade[i].id, grade[i].a, grade[i].b, grade[i].c, grade[i].d);
      sgrades ans;
      ans.id = (*grade+i)->id;
      ans.a = (*grade+i)->a; ans.b = (*grade+i)->b;
      ans.c = (*grade+i)->c; ans.d = (*grade+i)->d;
      return ans;
    }
  }
  sgrades notfound;
  notfound.id = -1;
  // printf("Estudiante con id [%d] no encontrado\n",id);
  return notfound;
}

char* graduationDate(student stud[], int n, int id){
  for (int i=0; i<n; i++){
    if(stud[i].id == id){
      // printf("Fecha: %s\n", stud[i].graduation);
      return stud[i].graduation;
    }
  }
  // printf("Estudiante con id [%d] no encontrado\n",id);
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

int main(int argc, char *argv[]){
    
    // printf ("argv[1]: %s\n", argv[1]);
    // printf ("argv[2]: %s\n", argv[2]);

  //Variables of type file
  FILE *file1, *file2;

  //Opening files
  file1 = fopen(argv[1], "r");
  file2 = fopen(argv[2], "r");

  if(file1 == NULL) //If NULL returned opening file 1 EXIT
  {
    printf("Error opening file1!\n");   
    exit(1);             
  }
  if(file2 == NULL) //If NULL returned opening file 2 EXIT
  {
    printf("Error opening file2!\n");   
    exit(1);             
  }
  //variables to know the amount of lines of each file
  int size1 = fileLines(file1);
  int size2 = fileLines(file2);
  // printf("from file 1: %d\n", size1);
  // printf("from file 2: %d\n", size2);

  //Dynamically stored data in arrays
  student *students = malloc(size1*sizeof(student));
  sgrades *grades = malloc(size2*sizeof(sgrades));
  //To store first line of files (header)
  char sHeader[80];
  char gHeader[60];
  
  int count = 0;
  char name2[20];
  fgets(sHeader, 80, file1);
  while (!feof(file1))  //storing data of file 1
  {
    fscanf(file1, "%d", &students[count].id);
    fscanf(file1, "%s", students[count].name);
      fscanf(file1, "%s", name2);
      strcat(students[count].name, " ");
      strcat(students[count].name, name2);
    fscanf(file1, "%s", students[count].major);
    fscanf(file1, "%s", students[count].city);
    fscanf(file1, "%s", students[count].graduation);
    count++;
  }
  fclose(file1);

  int count2 = 0;
  fgets(gHeader, 60, file2);
  while (!feof(file2))  //storing data of file 2
  {
    fscanf(file2, "%d", &grades[count2].id);
    fscanf(file2, "%d", &grades[count2].a);
    fscanf(file2, "%d", &grades[count2].b);
    fscanf(file2, "%d", &grades[count2].c);
    fscanf(file2, "%d", &grades[count2].d);
    count2++;
  }
  fclose(file2);  

  // for(int i=0; i<count; i++){
  //   printf("%d\t%s\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].major, students[i].city, students[i].graduation);
  // }
  // printf("\n");
  // for(int j=0; j<count2; j++){
  //   printf("%d\t%d\t%d\t%d\t%d\n", grades[j].id, grades[j].a, grades[j].b, grades[j].c, grades[j].d);
  // }

  printf(" ------------------------\n");
  printf("|         [MENU]         |\n");
  printf("| 1) Mostrar Estudiantes |\n");
  printf("| 2) Realizar consulta   |\n");
  printf("| 3) Terminar programa   |\n");
  printf(" ------------------------\n\n");

  // sgrades x;
  // x = kardex(&grades, count2, 987);
  // printf("ID: %d A:%d B:%d C:%d D:%d\n", x.id, x.a, x.b, x.c, x.d);

  // char *x[2];
  // *x = graduationDate(students, count, 0);
  // printf("%s\n", *x);

  // int x;
  // x = studentsNumMajorCity(&students, count, "ITC", "Merida");
  // printf("Students: %d\n", x);

  // int x;
  // x = studentsNumMajor(&students, count, "ITC");
  // printf("Students: %d\n", x);

  // int x;
  // char str[] = "*";
  // x = studentsNumHandler(&students, count, str);
  // printf("Students: %d\n", x);

  // int size=1;
  // char *namesToPrint[size];
  // studentsNameMajor(&students, count, "IIS", namesToPrint);
  // for(int i=0; i<size; i++){
  //   printf("%s\n", namesToPrint[i]);
  // }

  // int size=1;
  // char *namesToPrint[size];
  // studentsNameMajorCity(&students, count, "ITC", "Merida", namesToPrint);
  // for(int i=0; i<size; i++){
  //   printf("%s\n", namesToPrint[i]);
  // }

  // int size=9;
  // char *namesToPrint[size];
  // char str[] = "*";
  // studentsNameHandler(&students, count, str, namesToPrint);
  // for(int i=0; i<size; i++){
  //   printf("%s\n", namesToPrint[i]);
  // }

  free(students);
  free(grades);
  return 0;
}
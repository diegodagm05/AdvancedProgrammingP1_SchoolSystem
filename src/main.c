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
  int a;
  int b;
  int c;
  int d;
} sgrades;

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

int main(int argc, char *argv[]){

    //string to store file names
      
    // char file1[] = "../inputfiles/";
    // char file2[] = "../inputfiles/";
      
    // strcat(file1,argv[1]);
    // strcat(file2,argv[2]);

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

  int size1 = fileLines(file1);
  int size2 = fileLines(file2);
  // printf("from file 1: %d\n", size1);
  // printf("from file 2: %d\n", size2);
  // printf ("argv[1]: %s\n", argv[1]);
  // printf ("argv[2]: %s\n", argv[2]);

  student *students = malloc(size1*sizeof(student));
  char sHeader[80];
  sgrades *grades = malloc(size2*sizeof(sgrades));
  char gHeader[60];
  
  int count = 0;
  char name2[20];
  fgets(sHeader, 80, file1);
  while (!feof(file1))
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
  while (!feof(file2))
  {
    fscanf(file2, "%d", &grades[count2].id);
    fscanf(file2, "%d", &grades[count2].a);
    fscanf(file2, "%d", &grades[count2].b);
    fscanf(file2, "%d", &grades[count2].c);
    fscanf(file2, "%d", &grades[count2].d);
    count2++;
  }
  fclose(file2);  

  for(int i=0; i<count; i++){
    printf("%d\t%s\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].major, students[i].city, students[i].graduation);
  }
  printf("\n");
  for(int j=0; j<count2; j++){
    printf("%d\t%d\t%d\t%d\t%d\n", grades[j].id, grades[j].a, grades[j].b, grades[j].c, grades[j].d);
  }


  free(students);
  free(grades);
  return 0;
}
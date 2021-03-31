/*
*   Diego Guerrero - A01625199
*   Tecnologico de Monterrey
*   Advanced Programming - Project 1
*/

#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

  //main source code goes here

    //string to store file names
      
    // char file1[] = "../inputfiles/";
    // char file2[] = "../inputfiles/";
      
    // strcat(file1,argv[1]);
    // strcat(file2,argv[2]);

  //Variables of type file
  FILE *ptrf1, *ptrf2;

  //Opening files
  ptrf1 = fopen(argv[1], "r");
  ptrf2 = fopen(argv[2], "r");

  if(ptrf1 == NULL) //If NULL returned opening file 1 EXIT
  {
    printf("Error opening file1!\n");   
    exit(1);             
  }
  if(ptrf2 == NULL) //If NULL returned opening file 2 EXIT
  {
    printf("Error opening file2!\n");   
    exit(1);             
  }

  int n, m;
  fscanf(ptrf1, "%d", &n);
  fscanf(ptrf2, "%d", &m);

  printf("from file 1: %d\n", n);
  printf("from file 2: %d\n", m);

  // printf ("argv[1]: %s\n", argv[1]);
  // printf ("argv[2]: %s\n", argv[2]);

  fclose(ptrf1);
  fclose(ptrf2);


  return 0;
}
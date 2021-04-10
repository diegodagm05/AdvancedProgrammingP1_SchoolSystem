/*
*   Diego Guerrero - A01625199
*   Tecnologico de Monterrey
*   Advanced Programming - Project 1
*/

#include "../lib/src/func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #ifdef _WIN32
// #include <Windows.h>
// #else
#include <unistd.h>
// #endif


#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]){
    
  // printf ("argv[1]: %s\n", argv[1]);
  // printf ("argv[2]: %s\n", argv[2]);

  //variables to execute flags;
  int HELP = FALSE, VERBOSE = FALSE, TOFILE = FALSE;
    TOFILE = FALSE;
    VERBOSE = FALSE;

  //Variables of type file
  FILE *file1, *file2, *outFile;
  char fileName[20] = "out.txt";
  
  //Opening files
  file1 = fopen(argv[1], "r");
  file2 = fopen(argv[2], "r");
  
  if(TOFILE && VERBOSE){
    printf("-v [Abriendo archivo de salida]\n");
    sleep(1);
  }

  if(TOFILE) //openning output file
    outFile = fopen(fileName, "w");

  if(outFile == NULL){
    printf("Error opening output file!\n");   
    exit(1);
  }
  if(TOFILE && VERBOSE){
    printf("-v [Archivo de salida abierto]\n");
    sleep(1);
  }

  if(VERBOSE){
    printf("-v [Abriendo archivos]\n");
    sleep(1);
  }

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
  if(VERBOSE){
    printf("-v [Archivos abiertos]\n");
    sleep(1);
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
  
  int countS = 0;
  char name2[20];
  fgets(sHeader, 80, file1);
  while (!feof(file1))  //storing data of file 1
  {
    fscanf(file1, "%d", &students[countS].id);
    fscanf(file1, "%s", students[countS].name);
      fscanf(file1, "%s", name2);
      strcat(students[countS].name, " ");
      strcat(students[countS].name, name2);
    fscanf(file1, "%s", students[countS].major);
    fscanf(file1, "%s", students[countS].city);
    fscanf(file1, "%s", students[countS].graduation);
    countS++;
  }
  if(VERBOSE){
    printf("-v [Informacion Archivo 1 almacenada]\n");
    sleep(1);
  }

  fclose(file1);

  if(VERBOSE){
    printf("-v [Archivo 1 cerrado]\n");
    sleep(1);
  }
  
  int countG = 0;
  fgets(gHeader, 60, file2);
  while (!feof(file2))  //storing data of file 2
  {
    fscanf(file2, "%d", &grades[countG].id);
    fscanf(file2, "%d", &grades[countG].a);
    fscanf(file2, "%d", &grades[countG].b);
    fscanf(file2, "%d", &grades[countG].c);
    fscanf(file2, "%d", &grades[countG].d);
    countG++;
  }
  if(VERBOSE){
    printf("-v [Informacion Archivo 2 almacenada]\n");
    sleep(1);
  }

  fclose(file2);  

  if(VERBOSE){
    printf("-v [Archivo 2 cerrado]\n");
    sleep(1);
  }

  // for(int i=0; i<countS; i++){
  //   printf("%d\t%s\t%s\t%s\t%s\n", students[i].id, students[i].name, students[i].major, students[i].city, students[i].graduation);
  // }
  // printf("\n");
  // for(int j=0; j<countG; j++){
  //   printf("%d\t%d\t%d\t%d\t%d\n", grades[j].id, grades[j].a, grades[j].b, grades[j].c, grades[j].d);
  // }

  int opt=0;
  while(opt != 3){
    
    printf(" ------------------------\n");
    printf("|         [MENU]         |\n");
    printf("| 1) Mostrar Estudiantes |\n");
    printf("| 2) Realizar consulta   |\n");
    printf("| 3) Terminar programa   |\n");
    printf(" ------------------------\n\n");
    printf("Opcion: ");
    scanf("%d",&opt);

    if( opt == 1 ){ //option 1, print all students data
      for(int i=0; i<countS; i++){
        for(int j=0; j<countG; j++){
          if( students[i].id == grades[j].id)
            printf("%d\t%s\t%s %s\t%s\t%d %d %d %d\n", 
            students[i].id, students[i].name, students[i].major, students[i].city, 
            students[i].graduation, grades[j].a, grades[j].b, grades[j].c, grades[j].d);
        }
      }
    }
    else if( opt == 2 ){ //option 2, do a query
      
      // char *input = NULL;
      // size_t len = 0;
      // ssize_t size = 0;
      
      // input = malloc(32*sizeof(char));

      // if( input == NULL){
      //   perror("Unable to allocate buffer");
      //   exit(1);
      // }
      // size = getline(&input, &len, stdin);

      char input[] = "Numero_alumnos *";
      char fullQuery[20];
      strcpy(fullQuery, input);

      //separate the query and its arguments into different strings
      int argsc = 0;
      char *argsv[3];
      char *token = strtok(input, " ");
      while (token != NULL){
        argsv[argsc++] = token;
        token = strtok(NULL, " ");
      }
      
      char *query = argsv[0]; //query stored in first position

      if(VERBOSE){
        printf("-v [Ejecutando consulta]\n");
        sleep(1);
      }

      if(!strcmp(query, "Kardex")){

        if(argsc == 1){
          printf("Missing arguments\n");
          if(VERBOSE){
            printf("-v [Consulta fallida]\n");
            sleep(1);
          }
        }
        else{
          int idToFind = atoi(argsv[1]);
          sgrades kardexObtained;
          kardexObtained = kardex(&grades, countG, idToFind);
          if(TOFILE){
            if(kardexObtained.id != -1)
              fprintf(outFile,"%s: ID: %d A:%d B:%d C:%d D:%d\n", fullQuery, kardexObtained.id, kardexObtained.a, kardexObtained.b, kardexObtained.c, kardexObtained.d);
            else
              fprintf(outFile,"%s: Estudiante con id [%d] no encontrado\n", fullQuery,idToFind);
            if(VERBOSE){
              printf("-v [Consulta insertada en archivo]\n");
              sleep(1);
            }
          }else{
            if(kardexObtained.id != -1)
              printf("ID: %d A:%d B:%d C:%d D:%d\n", kardexObtained.id, kardexObtained.a, kardexObtained.b, kardexObtained.c, kardexObtained.d);
            else
              printf("Estudiante con id [%d] no encontrado\n",idToFind);
          }
          if(VERBOSE){
            printf("-v [Consulta ejecutada exitosamente]\n");
            sleep(1);
          }
        }

      }
      else if(!strcmp(query, "Fecha_estimada_graduacion")){

        if(argsc == 1){
          printf("Missing arguments\n");
          if(VERBOSE){
            printf("-v [Consulta fallida]\n");
            sleep(1);
          }
        }
        else{
          int idToFind = atoi(argsv[1]);
          char *dateObtained[1];
          *dateObtained = graduationDate(&students, countS, idToFind);
          if(TOFILE){
            if( strcmp(*dateObtained, "/"))
              fprintf(outFile,"%s: %s\n",fullQuery, *dateObtained);
            else
              fprintf(outFile,"%s: Estudiante con id [%d] no encontrado\n", fullQuery,idToFind);
            if(VERBOSE){
              printf("-v [Consulta insertada en archivo]\n");
              sleep(1);
            }
          }else{
            if( strcmp(*dateObtained, "/"))
              printf("%s\n", *dateObtained);
            else
              printf("Estudiante con id [%d] no encontrado\n",idToFind);
          }
            if(VERBOSE){
              printf("-v [Consulta ejecutada exitosamente]\n");
              sleep(1);
            }
        }

      }
      else if(!strcmp(query, "Numero_alumnos")){
        
        if(argsc == 1){
          printf("Missing arguments\n");
          if(VERBOSE){
            printf("-v [Consulta fallida]\n");
            sleep(1);
          }
        }
        else{
          int sNum;
          char buffer[] ="";
          for(int i=1; i<argsc; i++){ //concatenate arguments into buffer
            strcat(buffer, argsv[i]);
            strcat(buffer, " ");
          }
          sNum = studentsNumHandler(&students, countS, buffer);
          if(TOFILE){
            fprintf(outFile,"%s: %d\n", fullQuery,sNum);
            if(VERBOSE){
              printf("-v [Consulta insertada en archivo]\n");
              sleep(1);
            }
          }else{
            printf("Estudiantes: %d\n", sNum);
          }
          if(VERBOSE){
            printf("-v [Consulta ejecutada exitosamente]\n");
            sleep(1);
          }
        } 

      }
      else if(!strcmp(query, "Nombre_alumnos")){
        
        if(argsc == 1){
          printf("Missing arguments\n");
          if(VERBOSE){
            printf("-v [Consulta fallida]\n");
            sleep(1);
          }
        }
        else{
          //if query has any operator as parameter executes the query with operators
          if( !strcmp(argsv[1], "<") || !strcmp(argsv[1], ">") || !strcmp(argsv[1], "==") || !strcmp(argsv[1], "!=")){
            int valueComp = atoi(argsv[2]);
            int size = studentsNameOperatorNum(&grades, countG, argsv[1], valueComp);
            int idsObtained[size];
            studentsNameOperator(&grades, countG, argsv[1], valueComp, idsObtained);
            if(TOFILE){
              fprintf(outFile,"%s: \n",fullQuery);
              for(int i=0; i<size; i++){
                for(int j=0; j<countS; j++){
                  if( *(idsObtained + i) == students[j].id){
                    fprintf(outFile,"%s\n", students[j].name);
                    break;
                  }
                }
              }
              if(VERBOSE){
                printf("-v [Consulta insertada en archivo]\n");
                sleep(1);
              }
            }else{
              for(int i=0; i<size; i++){
                for(int j=0; j<countS; j++){
                  if( *(idsObtained + i) == students[j].id){
                    printf("%s\n", students[j].name);
                    break;
                  }
                }
              }
            }
            if(VERBOSE){
              printf("-v [Consulta ejecutada exitosamente]\n");
              sleep(1);
            }
          }
          else{ //if query does not have an operator, executes the other queries
            int sNum;
            char buffer[] ="";
            for(int i=1; i<argsc; i++){ //concatenate arguments into buffer
              strcat(buffer, argsv[i]);
              strcat(buffer, " ");
            }
            sNum = studentsNumHandler(&students, countS, buffer);
            char *namesObtained[sNum];
            studentsNameHandler(&students, countS, buffer, namesObtained);
            if(TOFILE){
              fprintf(outFile,"%s:\n", fullQuery);
              for(int i=0; i<sNum; i++){
                fprintf(outFile,"%s\n", namesObtained[i]);
              }
              if(VERBOSE){
                printf("-v [Consulta insertada en archivo]\n");
                sleep(1);
              }
            }else{
              for(int i=0; i<sNum; i++){
                printf("%s\n", namesObtained[i]);
              }
            }
            if(VERBOSE){
              printf("-v [Consulta ejecutada exitosamente]\n");
              sleep(1);
            }
          }
        }

      }
      else{
        printf("Invalid query\n");
        if(VERBOSE){
          printf("-v [Consulta fallida]\n");
          sleep(1);
        }
      }
    }
    else if( opt == 3 ){

      if(VERBOSE){
        printf("-v [Terminando programa]\n");
        sleep(1);
        printf("-v [Liberando memoria dinamica]\n");
        sleep(1);
      }
      free(students);
      free(grades);
      if(VERBOSE){
        printf("-v [Memoria dinamica liberada]\n");
      }
      if(VERBOSE && TOFILE){
        fclose(outFile);
        printf("-v [Archivo de salida cerrado]\n");
        sleep(1);
      }
      return 0;
    }
    else
      printf("Invalid option\n");
  }

  // sgrades x;
  // x = kardex(&grades, countG, 987);
  // printf("ID: %d A:%d B:%d C:%d D:%d\n", x.id, x.a, x.b, x.c, x.d);

  // char *x[2];
  // *x = graduationDate(students, countS, 0);
  // printf("%s\n", *x);

  // int x;
  // x = studentsNumMajorCity(&students, countS, "ITC", "Merida");
  // printf("Students: %d\n", x);

  // int x;
  // x = studentsNumMajor(&students, countS, "ITC");
  // printf("Students: %d\n", x);

  // int x;
  // char str[] = "*";
  // x = studentsNumHandler(&students, countS, str);
  // printf("Students: %d\n", x);

  // int size=1;
  // char *namesToPrint[size];
  // studentsNameMajor(&students, countS, "IIS", namesToPrint);
  // for(int i=0; i<size; i++){
  //   printf("%s\n", namesToPrint[i]);
  // }

  // int size=1;
  // char *namesToPrint[size];
  // studentsNameMajorCity(&students, countS, "ITC", "Merida", namesToPrint);
  // for(int i=0; i<size; i++){
  //   printf("%s\n", namesToPrint[i]);
  // }

  // int size=9;
  // char *namesToPrint[size];
  // char str[] = "*";
  // studentsNameHandler(&students, countS, str, namesToPrint);
  // for(int i=0; i<size; i++){
  //   printf("%s\n", namesToPrint[i]);
  // }

  // int x = studentsNameOperatorNum(&grades, countG, "!=", 90);

  // int *ptr, idsToPrint[x];
  // studentsNameOperator(&grades, countG, "!=", 90, idsToPrint);
  // for(int i=0; i<x; i++){
  //   for(int j=0; j<countS; j++){
  //     if( *(idsToPrint + i) == students[j].id){
  //       printf("%s\n", students[j].name);
  //       break;
  //     }
  //   }
  // }

  return 0;
}
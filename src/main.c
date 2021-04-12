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

  //variables to execute flags;
  int HELP = FALSE, VERBOSE = FALSE, TOFILE = FALSE;
  int flag;
  char fileName[] = "";

  while ((flag = getopt(argc, argv, "hvo:")) != -1){
    switch (flag){
    case 'h':
      HELP = TRUE;
      break;
    case 'v':
      VERBOSE = TRUE;
      break;
    case 'o':
      TOFILE = TRUE;
      strcpy(fileName,optarg);
      break;
    case '?':
      if(optopt == 'o')
        fprintf(stderr,"[ERROR]: Bandera -c requiere argumento nombre de archivo\n");
      else
        fprintf(stderr,"[ERROR]: Bandera -%c desconocida\n", optopt);
      break;
    default :
      break;
    }
  }
  
  if(HELP){

    printf("\nPROYECTO\n\n");
      printf("\tSimulacion de un DBMS escolar\n\n");
    printf("DESCRIPCION\n\n");
      printf("\tSistema que simula un DBMS, donde se almacena la informacion de una lista de estudiantes obtenida de archivos que el usario debe proveer, con sus respectivos datos.\n");
      printf("\tRealizacion de consultas con la informacion almacenada. \n\n");
    printf("QUERIES\n\n");
      printf("\tKardex <id_estudiante>\n\t\tMuestra las calificaciones del estudiante con el id provisto.\n\n");
      printf("\tFecha_estimada_graduacion <estudiante_id>\n\t\tMuestra la fecha de graduacion del estudiante con el id provisto.\n\n");
      printf("\tNumero_alumnos <nombre_carrera> <ciudad_origen>\n\t\tMuestra el numero de alumnos que cumplen con la carrera y ciudad provista.\n\n");
      printf("\tNumero_alumnos <nombre_carrera>\n\t\tMuestra el numero de alumnos que cumplen con la carrera provista.\n\n");
      printf("\tNumero_alumnos *\n\t\tMuestra el numero total de alumnos.\n\n");
      printf("\tNombre_alumnos <nombre_carrera> <ciudad_origen>\n\t\tMuestra la lista de nombres de alumnos que cumplen con la carrera y ciudad provista.\n\n");
      printf("\tNombre_alumnos <nombre_carrera>\n\t\tMuestra la lista de nombres de alumnos que cumplen con la carrera provista.\n\n");
      printf("\tNombre_alumnos *\n\t\tMuestra la lista total de nombres de alumnos.\n\n");
      printf("\tNombre_alumnos <operador> <numero>\n\t\tMuestra la lista de nombres de alumnos cuyo promedio cumpla con la condicion del operador y numero.\n\n");
        printf("\t\tOperadores:\n");
        printf("\t\t   [<] Menor que\n");
        printf("\t\t   [>] Mayor que\n");
        printf("\t\t   [==] Igual a\n");
        printf("\t\t   [!=] Diferente de\n\n");
    
  }
  else{

    //Variables of type file
    FILE *file1, *file2, *outFile;
    
    if(TOFILE && VERBOSE){
      printf("[INFO:] [Abriendo archivo de salida]\n");
      sleep(1);
    }

    if(TOFILE) //openning output file
      outFile = fopen(fileName, "w");

    if(TOFILE && outFile == NULL){
      printf("[ERROR]: Error opening output file!\n");   
      exit(1);
    }
    if(TOFILE && VERBOSE){
      printf("[INFO:] [Archivo de salida abierto]\n");
      sleep(1);
    }

    if(VERBOSE){
      printf("[INFO:] [Abriendo archivos]\n");
      sleep(1);
    }

    //Opening files
    file1 = fopen(argv[argc-2], "r");
    file2 = fopen(argv[argc-1], "r");

    if(file1 == NULL) //If NULL returned opening file 1 EXIT
    {
      printf("[ERROR]: Error opening file1!\n");
      exit(1);             
    }
    if(file2 == NULL) //If NULL returned opening file 2 EXIT
    {
      printf("[ERROR]: Error opening file2!\n");   
      exit(1);             
    }
    if(VERBOSE){
      printf("[INFO:] [Archivos abiertos]\n");
      sleep(1);
    }
    //variables to know the amount of lines of each file
    int size1 = fileLines(file1);
    int size2 = fileLines(file2);

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
      printf("[INFO:] [Informacion Archivo 1 almacenada]\n");
      sleep(1);
    }

    fclose(file1);

    if(VERBOSE){
      printf("[INFO:] [Archivo 1 cerrado]\n");
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
      printf("[INFO:] [Informacion Archivo 2 almacenada]\n");
      sleep(1);
    }

    fclose(file2);  

    if(VERBOSE){
      printf("[INFO:] [Archivo 2 cerrado]\n");
      sleep(1);
    }

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
        
        while ( (getchar()) != '\n'); //clean the buffer
        
        char *inputQuery = NULL;
        size_t len = 60;

        getline(&inputQuery, &len, stdin); //store the query from the user
        inputQuery[strlen(inputQuery)-1] = '\0'; //add the end character to the query
        
        char fullQuery[20];
        strcpy(fullQuery, inputQuery);

        //separate the query and its arguments into different strings
        int argsc = 0;
        char *argsv[3];
        char *token = strtok(inputQuery, " ");
        while (token != NULL){
          argsv[argsc++] = token;
          token = strtok(NULL, " ");
        }
        
        char *query = argsv[0]; //query stored in first position

        if(VERBOSE){
          printf("[INFO:] [Ejecutando consulta]\n");
          sleep(1);
        }

        if(!strcmp(query, "Kardex")){

          if(argsc == 1){
            printf("Missing arguments\n");
            if(VERBOSE){
              printf("[INFO:] [Consulta fallida]\n");
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
                printf("[INFO:] [Consulta insertada en archivo]\n");
                sleep(1);
              }
            }else{
              if(kardexObtained.id != -1)
                printf("ID: %d A:%d B:%d C:%d D:%d\n", kardexObtained.id, kardexObtained.a, kardexObtained.b, kardexObtained.c, kardexObtained.d);
              else
                printf("Estudiante con id [%d] no encontrado\n",idToFind);
            }
            if(VERBOSE){
              printf("[INFO:] [Consulta ejecutada exitosamente]\n");
              sleep(1);
            }
          }

        }
        else if(!strcmp(query, "Fecha_estimada_graduacion")){

          if(argsc == 1){
            printf("Missing arguments\n");
            if(VERBOSE){
              printf("[INFO:] [Consulta fallida]\n");
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
                printf("[INFO:] [Consulta insertada en archivo]\n");
                sleep(1);
              }
            }else{
              if( strcmp(*dateObtained, "/"))
                printf("%s\n", *dateObtained);
              else
                printf("Estudiante con id [%d] no encontrado\n",idToFind);
            }
              if(VERBOSE){
                printf("[INFO:] [Consulta ejecutada exitosamente]\n");
                sleep(1);
              }
          }

        }
        else if(!strcmp(query, "Numero_alumnos")){
          
          if(argsc == 1){
            printf("Missing arguments\n");
            if(VERBOSE){
              printf("[INFO:] [Consulta fallida]\n");
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
                printf("[INFO:] [Consulta insertada en archivo]\n");
                sleep(1);
              }
            }else{
              printf("Estudiantes: %d\n", sNum);
            }
            if(VERBOSE){
              printf("[INFO:] [Consulta ejecutada exitosamente]\n");
              sleep(1);
            }
          } 

        }
        else if(!strcmp(query, "Nombre_alumnos")){
          
          if(argsc == 1){
            printf("Missing arguments\n");
            if(VERBOSE){
              printf("[INFO:] [Consulta fallida]\n");
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
                  printf("[INFO:] [Consulta insertada en archivo]\n");
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
                printf("[INFO:] [Consulta ejecutada exitosamente]\n");
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
                  printf("[INFO:] [Consulta insertada en archivo]\n");
                  sleep(1);
                }
              }else{
                for(int i=0; i<sNum; i++){
                  printf("%s\n", namesObtained[i]);
                }
              }
              if(VERBOSE){
                printf("[INFO:] [Consulta ejecutada exitosamente]\n");
                sleep(1);
              }
            }
          }

        }
        else{
          printf("Invalid query\n");
          if(VERBOSE){
            printf("[INFO:] [Consulta fallida]\n");
            sleep(1);
          }
        }
        free(inputQuery);
      }
      else if( opt == 3 ){

        if(VERBOSE){
          printf("[INFO:] [Terminando programa]\n");
          sleep(1);
          printf("[INFO:] [Liberando memoria dinamica]\n");
          sleep(1);
        }
        free(students);
        free(grades);
        if(VERBOSE){
          printf("[INFO:] [Memoria dinamica liberada]\n");
        }
        if(VERBOSE && TOFILE){
          fclose(outFile);
          printf("[INFO:] [Archivo de salida cerrado]\n");
          sleep(1);
        }
        return 0;
      }
      else
        printf("Invalid option\n");
    }
  }
  return 0;
}
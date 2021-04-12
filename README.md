# AdvancedProgrammingP1_SchoolSystem{

School system that simulates a DBMS. Storing students data such as id, name, major, city and expected graduation year.
The queries to use are the following:

*******************
Kardex <student_id>
Fecha_estimada_graduacion <student_id>
Numero_alumnos <major_name> <city>
Numero_alumnos <major_name>
Numero_alumnos *
Nombre_alumnos <major_name> <city>
Nombre_alumnos <major_name>
Nombre_alumnos *
Nombre_alumnos <operator> <number_value>
  Uses an operator to check if the average of the students grades meets the condition with the given value number.
    OPERATORS:
    <, >, ==, !=

******************
In order to use the program you have to place two required files in the "src" folder that will contain the students information.
The files structure has to be as follows:
  
  [FILE 1]
    "ID"          "NAME"  "MAJOR"   "CITY"  "GRADUATION YEAR"
    <student_id>  <name>  <major>   <city>  <expected_graduation>
  
  [FILE 2]
    "ID"          "SUBJECT A"   "SUBJECT B"   "SUBJECT C"   "SUBJECT D"
    <student_id>  <number>      <number>      <number>      <number>
  

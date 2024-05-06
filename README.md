En este *repl* puedes encontrar varios ejemplos que te pueden ayudar con las tareas de estructura.

## Código de Ejemplo (tarea2)
Para ejecutar el ejemplo tarea2 primero debemos compilar (en la carpeta raíz)
````
gcc tdas/*.c tarea2.c -Wno-unused-result -o tarea2
````
Luego para ejecutarlo, debe ingresar el siguiente comando:
````
./tarea2
````

## Menu de funcionalidades
Al ejecutarlo se deberia de abrir el siguiente menu:
````
========================================
     Base de Datos de Películas
========================================
1) Cargar Películas
2) Buscar por id
3) Buscar por director
4) Buscar por género
5) Buscar por década
6) Buscar por rango de calificaciones
7) Buscar por década y género
8) Salir
Ingrese su opción:
````
## 1) Cargar Películas
Al seleccionar esta opcion, se empiezan a cargar todas las peliculas y automaticamente empezara a mostrar todas las peliculas que se estan cargando exitosamente. Es necesario seleccionar esta opcion al principio para que las otras funciones  <br>
Ahora si puede empezar a buscar las peliculas

## 2) Buscar por ID
Esta opcion permite al usuario buscar la pelicula mediante el ID de esta, ingresa el id y se busca
````
Ingrese su opción: 2
Ingrese el id de la película: tt0119567
Título: The Lost World: Jurassic Park, Año: 1997
Presione una tecla para continuar...
````
## 3) Buscar por Director
Esta Opcion permite buscar peliculas por su director. En el mapa de los directores, se usa el nombre del director como llave para encontrar la lista de peliculas del director ingresado. <br>
Por razones que desconozco, esta opcion no funciono y es debido a que al buscar el director ingresado en los mapas, no lo encuentra, no supe encontrar la razon.

## 4) Buscar por Genero
Esta funcion permite buscar por genero, al seleccionarla te saldra una lista de todos los generos disponibles, uno ingresa escribiendo exactamente, uno de los de la lista, y el programa te muestra todas las peliculas que sean de ese genero. (Es sensible a mayusculas)
````
32)  Action
33) Musical
34) Thriller
35) Romance
36) Fantasy
...)

Ingrese el genero: Comedy

Peliculas del genero Comedy
1) Título: The Graduate,Año: 1967, Genero: Comedy 
2) Título: Annie Hall,Año: 1977, Genero: Comedy 
3) Título: City Lights,Año: 1931, Genero: Comedy 
4) Título: Some Like It Hot,Año: 1959, Genero: Comedy 
5) Título: Singin' in the Rain,Año: 1952, Genero: Comedy 
6) Título: Mr. Smith Goes to Washington,Año: 1939, Genero: Comedy 
...)
````
## 5) Buscar por Decada
Esta opcion lo que permite es buscar una pelicula por la decada, el usuario ingresa un año de la decada que desea, y salen todas las peliculas de esa decada.
````
Ingrese su opción: 5
ingrese la decada:
1960
Se han encontrado 174 peliculas de la decada de los 1960
Titulo: The Entertainer, Año: 1960
Titulo: Boy, Did I Get a Wrong Number!, Año: 1966
Titulo: The Patsy, Año: 1964
Titulo: Divorce American Style, Año: 1967
Titulo: The Disorderly Orderly, Año: 1964
Titulo: Batman: The Movie, Año: 1966
Titulo: Born Free, Año: 1966
Titulo: The Rare Breed, Año: 1966
Titulo: Sex and the Single Girl, Año: 1964
Titulo: Cash McCall, Año: 1960
Titulo: Cat Ballou, Año: 1965
Titulo: The Bellboy, Año: 1960
...
````
## 6) Buscar por Decada
Esta opcion permite al usuario ingresar una calificacion del 1 al 10 y saldran todas las peliculas registradas que tengan esa calificacion, si el usuario ingresa un decimal por ejemplo 2.5, saldran todas las peliculas desde 2.0 a 2.9.
````
Ingrese su opción: 6
Ingrese el rango de calificaciones (ejemplo 9.2): 8.3
Título: Casablanca, Año: 1942, Rating: 8.5
Título: Citizen Kane, Año: 1941, Rating: 8.3
Título: Shichinin no samurai, Año: 1954, Rating: 8.6
Título: C'era una volta il West, Año: 1968, Rating: 8.5
Título: Star Wars: Episode V - The Empire Strikes Back, Año: 1980, Rating: 8.7
Título: Double Indemnity, Año: 1944, Rating: 8.3
Título: Lawrence of Arabia, Año: 1962, Rating: 8.3
Título: It's a Wonderful Life, Año: 1946, Rating: 8.6
Título: North by Northwest, Año: 1959, Rating: 8.3
Título: Star Wars, Año: 1977, Rating: 8.6
Título: A Clockwork Orange, Año: 1971, Rating: 8.3
Título: Vertigo, Año: 1958, Rating: 8.3
...
````
## Problemas conocidos y a mejorar:
- Las impresiones no son constantes ni comodas.
- Los inputs no son intuitivos ni comodos, no deberian ser sensibles a mayusculas
- Errores de validacion

###### Realizado por Diego Rivera y Javiera Muñoz

#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
  char id[100];
  char title[100];
  List *genres;
  List *director;
  float rating;
  int year;
} Film;

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Base de Datos de Películas");
  puts("========================================");

  puts("1) Cargar Películas");
  puts("2) Buscar por id");
  puts("3) Buscar por director");
  puts("4) Buscar por género");
  puts("5) Buscar por década");
  puts("6) Buscar por rango de calificaciones");
  puts("7) Buscar por década y género");
  puts("8) Salir");
}

/**
 * Compara dos claves de tipo string para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo string.
 *
 * @param key1 Primer puntero a la clave string.
 * @param key2 Segundo puntero a la clave string.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */

void borrarComillas(char *str) { 
  int len = strlen(str); //Obtenemos la longitud de la cadena
  if (str[0] == '"') { //SI el primer carácter es una comilla:
    memmove(str, str + 1, len); //Movemos el inicio de la cadena a un espacio a la derecha
    len--; } //Bajamos en 1 el tamaño de la cadena
  
  if (len > 0 && str[len - 1] == '"') { //Si el último carácter es una comilla
  	str[len - 1] = '\0'; //Lo cambiamos al carácter nulo para que ahí termine la cadena.
  }
}

char *espacioInicial(char *str) {

		while (isspace((unsigned char)*str)) str++; // Mientras el primer carácter es un espacio, 
																								// avanzamos el puntero del inicio de la cadena

		return str; //Retornamos la cadena cambiada

}

int is_equal_str(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2) == 0;
}

void strMay(char *cadena) {
	int i = 0;
	while (cadena[i] != '\0') {
		cadena[i] = toupper(cadena[i]);
		i++;
	}
}

/**
 * Compara dos claves de tipo entero para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo entero.
 *
 * @param key1 Primer puntero a la clave entera.
 * @param key2 Segundo puntero a la clave entera.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
int is_equal_int(void *key1, void *key2) {
  return *(int *)key1 == *(int *)key2; // Compara valores enteros directamente
}

void limpiarBuffer() {
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Carga películas desde un archivo CSV y las almacena en un mapa por ID.
 */
void cargar_peliculas(Map *pelis_byid, Map *pelis_bydirector, Map *pelis_bygenero) {
	// Intenta abrir el archivo CSV que contiene datos de películas
	FILE *archivo = fopen("data/Top1500.csv", "r");
	if (archivo == NULL) {
		perror(
				"Error al abrir el archivo"); // Informa si el archivo no puede abrirse
		return;
	}

	char **campos;
	// Leer y parsear una línea del archivo CSV. La función devuelve un array de
	// strings, donde cada elemento representa un campo de la línea CSV procesada.
	campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV

	// Lee cada línea del archivo CSV hasta el final
	while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
		
		// Crea una nueva estructura Film y almacena los datos de cada película
		Film *peli = (Film *)malloc(sizeof(Film));
		strcpy(peli->id, campos[1]);        // Asigna ID
		strcpy(peli->title, campos[5]);     // Asigna título
		peli->director = list_create(); // Asigna director
		peli->genres = list_create();       // Inicializa la lista de géneros
		peli->year = atoi(campos[10]); // Asigna año, convirtiendo de cadena a entero
    peli->rating = atof(campos[8]);

		// Inserta la película en el mapa usando el ID como clave
		map_insert(pelis_byid, peli->id, peli); //
		
		//GENEROS
    char *generos = strdup(campos[11]);
    char *genero = strtok(generos, ",");
    while(genero != NULL)
      {
        MapPair *generoPair = map_search(pelis_bygenero, genero);
        List *listaGeneros;
        if(generoPair == NULL)
        {
          listaGeneros = list_create();
          map_insert(pelis_bygenero, strdup(genero),listaGeneros);
        }else{
          listaGeneros = (List *)generoPair ->value;
        }
        list_pushBack(listaGeneros , peli);
        genero = strtok(NULL, ",");
      }
    free(generos);
    
		borrarComillas(campos[11]); //Borramos las comillas en caso de que haya

		char *token = strtok(campos[11], ","); //Cortamos el campo de géneros hasta una coma

		while (token != NULL) { //Mientras token no sea NULL

				char *clean_token = espacioInicial(token); //Limpiaremos el género en caso de que tenga espacios al principio

				list_pushBack(peli->genres, strdup(clean_token)); //Ahora agregamos el género a la lista de géneros de la película

				token = strtok(NULL, ","); //Volvemos a cortar la siguiente parte de la cadena hasta la coma

		}

	
		//DIRECTORES
		peli->director = list_create(); //Creamos la lista de directores de la película

		borrarComillas(campos[14]); //Borramos las comillas en caso de que haya
		char *token2 = strtok(campos[14], ","); //Cortamos el campo de directores hasta una coma
		while (token2 != NULL) { //Mientras token2 no sea NULL
				char *clean_token2 = espacioInicial(token2); //Limpiaremos el director en caso de que tenga espacios al principio
				list_pushBack(peli->director, strdup(clean_token2)); //Ahora agregamos el director a la lista de directores de la película
				token2 = strtok(NULL, ","); //Volvemos a cortar la siguiente parte de la cadena hasta la coma
		}
	}
	fclose(archivo); // Cierra el archivo después de leer todas las líneas


	// Itera sobre el mapa para mostrar las películas cargadas
	
	MapPair *pair = map_first(pelis_byid);
	while (pair != NULL) {
		Film *peli = pair->value;
		printf("ID: %s, Título: %s, Director:", peli->id, peli->title);
		for (char *director = list_first(peli->director) ; director != NULL ; director = list_next(peli->director)) { 
			printf(" %s ", director);
			
		} 
		printf(", Año: %i\n", peli->year);
		
		pair = map_next(pelis_byid); // Avanza al siguiente par en el mapa
	}
	
	/*
	MapPair *pair = map_first(pelis_bydirector);
	while (pair != NULL) {
		List *peli = pair->value;
		printf("director = %s|\n", (char *)pair->key);
		pair = map_next(pelis_bydirector); // Avanza al siguiente par en el mapa
	}
	*/
}

/**
 * Busca y muestra la información de una película por su ID en un mapa.
 */
void buscar_por_id(Map *pelis_byid) {
  char id[10]; // Buffer para almacenar el ID de la película
	

  // Solicita al usuario el ID de la película
  printf("Ingrese el id de la película: ");
  scanf("%s", id); // Lee el ID del teclado

  // Busca el par clave-valor en el mapa usando el ID proporcionado
  MapPair *pair = map_search(pelis_byid, id);

  // Si se encontró el par clave-valor, se extrae y muestra la información de la
  // película
  if (pair != NULL) {
    Film *peli =
        pair->value; // Obtiene el puntero a la estructura de la película
    // Muestra el título y el año de la película
    printf("Título: %s, Año: %d\n", peli->title, peli->year);
  } else {
    // Si no se encuentra la película, informa al usuario
    printf("La película con id %s no existe\n", id);
  }
} //hecha

void buscar_por_director(Map *pelis_bydirector){
	int cont = 0;
	MapPair *temp_pair = map_first(pelis_bydirector);
	char directores[300];
	
	printf("Ingrese el nombre del director: ");
	getchar();
	scanf(" %[^\n]", directores);
	MapPair *pair = map_search(pelis_bydirector, directores);

	
	
	if (pair != NULL)
	{
		List *peliculas = (List *)pair->value;
		Film *peli;
		printf("Peliculas del director '%s'\n", directores);
		for (peli = list_first(peliculas) ; peli != NULL ; peli = list_next(peliculas)){
			printf("ID = %s, Titulo: %s, Año: %i\n", peli->id, peli->title, peli->year);
		}
	}
	else printf("No se encontraron peliculas\n");
	
} //en proceso

void buscar_por_genero(Map *pelis_bygenero){
  int cont = 0;
  MapPair *opcionPair = map_first(pelis_bygenero);
  printf("\nGeneros disponibles:\n");
  while(opcionPair != NULL)
    {
			cont++;
      printf("%i) %s\n",cont , (char *)opcionPair->key);//mostrar opciones de generos
      opcionPair = map_next(pelis_bygenero);
    }
  char genero[100];
  printf("\nIngrese el genero: ");
  getchar();
  scanf("%[^\n]",genero);
  MapPair *pair = map_search(pelis_bygenero, genero);
  if(pair != NULL)
  {
    List *pelis = (List *)pair->value;
    Film *peli;
		int contDos = 0;
    printf("\nPeliculas del genero %s\n",genero);
    for (peli = list_first(pelis); peli != NULL; peli = list_next(pelis)){
			contDos ++;
      printf("%i) Título: %s,Año: %d, Genero: %s \n", contDos, peli->title,peli->year,genero); }
  }
  else
    printf("No se encontraron películas del género '%s'\n", genero);
    
} //hecha :D 

void mostrar_por_decada(List *listaPelicula, int cont, int decadaIng){ 
  Film *peli = list_first(listaPelicula);
	
  if(cont > 1)
  {
    printf("Se han encontrado %i peliculas de la decada de los %i\n",cont,decadaIng);
    while(peli != NULL)
      {
        printf("Titulo: %s, Año: %i\n", peli->title, peli->year);
        peli = list_next(listaPelicula);
      }
  }else if(cont==1){
    printf("Solo se ha encontrado una pelicula de la decada de los %i\n",decadaIng);
    printf("Titulo: %s, Año: %i\n", peli->title, peli->year);
  }else{
    printf("No se han encontrado pelicula de la decada de los %i\n",decadaIng);
  }
} //hecha

void buscar_por_decada(Map *pelis_byid){
  int decadaIngresada;
  puts("ingrese la decada:");
  scanf("%i", &decadaIngresada);

  decadaIngresada = decadaIngresada - (decadaIngresada % 10);
  
  List *listaPeliculas;
  listaPeliculas = list_create();
  int cont = 0;
  MapPair *pair = map_first(pelis_byid);
  while(pair != NULL)
    {
      Film *pelicula = pair->value;
      if(pelicula->year >= decadaIngresada && pelicula->year < decadaIngresada + 10)
      {
        list_pushFront(listaPeliculas, pelicula);
        cont += 1;
      }
      pair = map_next(pelis_byid);
    }
  mostrar_por_decada(listaPeliculas,cont,decadaIngresada);
} //hecha

void buscar_por_rango(Map *pelis_byid) {
  float rating;
  printf("Ingrese el rango de calificaciones (ejemplo 9.2): ");
  scanf("%f", &rating);

  MapPair *pair = map_first(pelis_byid);
  int cont = 0;

  float maxRating = rating + 0.4;
  if(maxRating > 10.0)
    maxRating = 10.0;
  
  while (pair != NULL) {
      Film *peli = pair->value;
      if (peli->rating >= rating && peli->rating <= maxRating) {
          cont++;
          printf("Título: %s, Año: %d, Rating: %.1f\n",peli->title,peli->year, peli->rating);
      }
      pair = map_next(pelis_byid);
  }
  if(cont > 0)
  {
    printf("Se han encontrado %i peliculas con el rango %.1f-%.1f",cont,rating,maxRating);
  }else if (cont == 0) {
      printf("No se encontraron películas en ese el rango %.1f-%.1f\n",rating,maxRating);
  }
} //hecha!!!

void buscar_por_decada_genero(Map *pelis_byid, Map *pelis_bygenero){
  
  int cont = 0;
  
  MapPair *opcionPair = map_first(pelis_bygenero);
  printf("\nGeneros disponibles:\n");
  while(opcionPair != NULL)
    {
      printf("%s",(char *)opcionPair->key);//mostrar opciones de generos
      opcionPair = map_next(pelis_bygenero);
      cont++;
    }

  int decadaIngresada;
  char genero[100];

  printf("\nIngrese el genero: ");
  getchar();
  scanf("%[^\n]",genero);
  printf("\nIngrese la decada deseada:");
  scanf("%i",&decadaIngresada);
  
  decadaIngresada = decadaIngresada - (decadaIngresada % 10);
  List *listaPeliculas;
  listaPeliculas = list_create();
  
  MapPair *pairDecada = map_first(pelis_byid);
  MapPair *pairGen = map_search(pelis_bygenero, genero);
  if(pairGen != NULL && pairDecada != NULL)
  {
    Film *decadaPeli = pairDecada->value;
    List *generoPeli = (List *)pairGen->value;
    Film *peli;
    
  }
    
  
	return;
}

int main() {
  char opcion; // Variable para almacenar una opción ingresada por el usuario
               // (sin uso en este fragmento)

  // Crea un mapa para almacenar películas, utilizando una función de
  // comparación que trabaja con claves de tipo string.
  Map *pelis_byid = map_create(is_equal_str);
	Map *pelis_bydirector = map_create(is_equal_str);
  Map *pelis_bygenero = map_create(is_equal_str);
  // Recuerda usar un mapa por criterio de búsqueda

  do 
	{
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      cargar_peliculas(pelis_byid, pelis_bydirector, pelis_bygenero); // Hecha
      break;
    case '2':
      buscar_por_id(pelis_byid); // Hecha
      break;
    case '3':
			buscar_por_director(pelis_bydirector); // En proceso...
      break;
    case '4':
			buscar_por_genero(pelis_bygenero); // Hecha
      break;
    case '5':
			buscar_por_decada(pelis_byid); // Hecha
      break;
    case '6':
			buscar_por_rango(pelis_byid); // Hecha
      break;
    case '7':
		  buscar_por_decada_genero(pelis_byid, pelis_bygenero); // En proceso...
      break;
		default:
      puts("Opcion no valida");
		}
    presioneTeclaParaContinuar();
  } while (opcion != '8');

  return 0;
}

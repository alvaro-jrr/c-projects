#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ----- Estructura de la Encuesta -----

typedef struct Encuesta {
	char name[50];
	char lastname[50];
	char birth_date[15];
	int  popularity;
} Encuestado;

// ----- Declaracion de Funciones -----

float get_n();
int   get_option(int min, int max, char *str);
void  clear();
void  display_stgs(int n, int m, char arr[n][m]);
void  get_birth(char *str);
void  bubble_order(Encuestado *ptr, int size);
void  get_information(Encuestado *ptr, int n, int size[]);
void  display(Encuestado *ptr, int n, char *str);

// ----- Main -----

int main() {
	// Variables para poder limpiar pantalla
	char clear_str[10];
	
	#ifdef _WIN32
		// Limpiar pantalla en Windows
		strcpy(clear_str, "cls");
	#else
		//Limpiar pantalla en la mayoria de los SO Linux
		strcpy(clear_str, "clear");
	#endif
	
	// Declaracion de Variables
	Encuestado *male, *female;
	
	char options[][60] = {"Registrar Encuestado",
		"Mostrar Masculinos",
		"Mostrar Femeninos",
		"Finalizar"};
		
	int n = 0, male_size[] = {0}, female_size[] = {0}, 
		max_size = 100, opt, n_opt = 4, true = 1,
		sex;
		
	// Asignando memoria con valor max_size de la estructura Encuestado
	male = (Encuestado*) malloc(max_size * sizeof(Encuestado));
	female = (Encuestado*) malloc(max_size * sizeof(Encuestado));
	
	if (male != NULL && female != NULL) {
		
		do {
			printf("----- Programa de Encuestas -----\n\n");
			
			// Mostrar Opciones
			display_stgs(n_opt, 60, options); printf("\n");
			
			// Elegir Opcion
			opt = get_option(1, n_opt, "Opcion");
			
			printf("\n---\n\n");
			
			// Acciones
			switch(opt) {
				
				// Agregar encuestado
				case 1:
					// Verificar si uno de los registros esta lleno
					if ((male_size[0] == max_size) || (female_size[0] == max_size)) {
						printf("El Espacio Asignado se ha llenado\nAsignando mas memoria...\n");
						max_size += 50;
						male = realloc(male, max_size * sizeof(Encuestado));
						female = realloc(female, max_size * sizeof(Encuestado));
						
						if ((male == NULL) || (female == NULL)) {
							printf("=> Error: La Memoria no fue Asignada");
							exit(0);
						} else {
							printf("Memoria asignada exitosamente!\n\n");
						}
					}
					
					sex = (int) get_option(0, 1, "Sexo (M = 1 | F = 0)");
					
					if (sex) {
						n = (int) get_option(1, max_size - male_size[0], "Numero de Masculinos a Registrar");
						get_information(male, n, male_size);
						
						if (male_size[0] > 1) {
							bubble_order(male, male_size[0]);
						}
						
					} else {
						n = (int) get_option(1, max_size - female_size[0], "Numero de Femeninas a Registrar");
						get_information(female, n, female_size);
						
						if (female_size[0] > 1) {
							bubble_order(female, female_size[0]);
						}
					}
				
					clear();
					
					break;
					
				// Mostrar Masculinos
				case 2:
					display(male, male_size[0], "Encuestados Masculinos");
					printf("\n");
					clear();
					break;
					
				case 3:
					display(female, female_size[0], "Encuestadas Femeninas");
					printf("\n");
					clear();
					break;
					
				case 4:
				default:
					true = 0;
					break;
			}
			
			// Limpiar Pantalla
			printf("\nPresione Enter para Continuar\n");
			getchar();
			system(clear_str);
		} while (true);
		
	} else {
		printf("No se pudo asignar el espacio en memoria\n\n----- Finalizado -----");
		exit(0);
	}
	
	// Libera espacio en memoria
	free(male);
	free(female);
	
	printf("----- Finalizado -----");
	
	printf("\n\nCoded with <3 by Alvaro\n\n");
	
	return 0;
}

// ----- Definicion de Funciones -----

// Funcion que limpia el bufer
void clear() {
	int c;
	
	while ((c = getchar()) != '\n' && c != EOF); 
}

// Funcion que Muestra Opciones
void display_stgs(int n, int m, char arr[n][m]) {
	int i;
		
	for (i = 0; i < n; i++) {
		printf("%d) %s\n", i + 1, arr[i]);
	}	
}

// Funcion que maneja la entrada de numeros
float get_n() {
	float n = -1;
	
	/*
	 * Al introducir un valor no numerico
	 * descarta la nueva linea
	 * y luego hace una limpieza del bufer.
	 * Retornando -1.
	 * 
	 * Sino, retorna el valor numerico
	 * que ha sido introducido.
	*/
	
	if (!scanf("%f", &n)) {
		scanf("%*[^\n]"); clear();
	}
	
	return n;
}

// Funcion que Toma la Opcion
int get_option(int min, int max, char *str) {
	int true = 1;
	float n;
	
	do {
		printf("%s: ", str); n = get_n();
		
		/*
		 *	Si el numero introducido
		 * 	es mayor o igual que el valor
		 *  minimo y menor o igual que el
		 * 	valor maximo de opciones. 
		 * 	
		 * 	Entonces, true = 0 y finaliza
		 * 	el bucle. Sino, continuara
		 * 	preguntando hasta recibir
		 * 	una entrada valida
		 *  
		*/
		
		if (((int) n >= min) && ((int) n <= max)) {
			true = 0;
		} else {
			printf("\n=> Error: Introduzca un valor n, tal que %d <= n <= %d\n\n", min, max);
		}
		
	} while (true);
		
	return (int) n;
}

// Funcion que obtiene la fecha de nacimiento
void get_birth(char *str) {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int day, month, year, min, max;
	
	// Obtener el Anio
	min = 1875;
	max = tm.tm_year + 1900;
	year = get_option(min, max, "Anio");
	
	// Obtener el Mes
	min = 1;
	
	if (year == max) {
		max = tm.tm_mon+ 1;
	} else {
		max = 12;
	}
	
	month = get_option(min, max, "Mes");
	
	// Obtener el Dia
	min = 1;
	
	if (month == 2) {
		max = 29;
	} else if (month == 4 || month == 6 || month == 9 || month == 11) {
		max = 30;
	} else {
		max = 31;
	}
	
	day = get_option(min, max, "Dia");
	
	// Convertir a String
	sprintf(str, "%02d/%02d/%d", day, month, year);
}

// Funcion que ordena
void bubble_order(Encuestado *ptr, int size) {
	// Declaracion de Variables
	Encuestado *temp;
	
	int i, j, k;
	
	// Asigna espacio en la memoria
	temp = (Encuestado*) malloc(1 * sizeof(Encuestado));
	
	// Realizada las pasadas
	for (i = 0; i < size; i++) {
		// Reordenamiento
		for (j = 0, k = 1; j < size && k < size; j++, k++) {
			if ((ptr + j)->popularity > (ptr + k)->popularity) {
				memmove(temp, (ptr + k), sizeof(Encuestado));
				memmove((ptr + k), (ptr + j), sizeof(Encuestado));
				memmove((ptr + j), temp, sizeof(Encuestado));
			}
		}
	}
	
	// Libera la memoria asignada
	free(temp);
}

// Funcion que toma la informacion
void  get_information(Encuestado *ptr, int n, int size[]) {
	int i, size_b = size[0];
	
	char str[15];
	
	for (i = size_b; i < (n + size_b); i++) {

		// Obtencion de la informacion
		printf("\nNombre: "); scanf("%s", (ptr + i)->name); clear();
		
		printf("Apellido: "); scanf("%s", (ptr + i)->lastname); clear();
		
		printf("\n--- Fecha de Nacimiento ---\n\n");
		
		get_birth(str);
		
		strcpy((ptr + i)->birth_date, str);
		
		printf("\n");
		
		(ptr + i)->popularity = (int) get_option(1, 10, "Popularidad");
		
		size[0]++;
	}
}

// Funcion que muestra la informacion
void display(Encuestado *ptr, int n, char *str) {
	int i;
	
	printf("----- %s -----", str);
	
	if (n <= 0) {
		printf("\n\nNo hay Registros\n\n");
	} else {
		for (i = 0; i < n; i++) {
			printf("\n\n--- %03d ---\n\n", i + 1);
			
			printf("Nombre: %s\nApellido: %s\nFecha de Nacimiento: %s\nPopularidad: %d",
				(ptr + i)->name, (ptr + i)->lastname,
				(ptr + i)->birth_date, (ptr + i)->popularity
			);
		}
	}
}

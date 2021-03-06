#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ----- Estructura de la Encuesta -----

typedef struct Encuesta {
	char name[50];
	char lastname[50];
	char sex[5];
	char songs[5][50];
	int age;
	int id;
} Encuestado;

// ----- Declaracion de Funciones -----

int get_option(int min, int max, char *str);

float get_n();

void organize(
	Encuestado *ptr, Encuestado *male_younger, Encuestado *female_younger,
	Encuestado *male_older, Encuestado *female_older, int size_organized,
	int size, int male_younger_size[0], int female_younger_size[0],
	int male_older_size[0], int female_older_size[0]
);

void display_stgs(int n, int m, char arr[n][m]);
void get_information(Encuestado *ptr, int n, int size[]);
void display(Encuestado *ptr, int n, char *str);
void clear();

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
	Encuestado *ptr, *male_younger, *male_older, *female_younger, *female_older;
	
	char options[][60] = {"Agregar Encuestados", 
		"Imprimir Primeros 10 Encuestados",
		"Imprimir Todos los Encuestados",
		"Imprimir Encuestados (Por Clasificacion)",
		"Finalizar Encuesta"};
			
	int n = 0, size[] = {0}, max_size = 50, opt, n_opt = 5, true = 1,
		size_organized = 0, male_younger_size[] = {0}, male_older_size[] = {0}, 
		female_younger_size[] = {0}, female_older_size[] = {0},
		bool;
		
	// Asignando memoria con valor max_size de la estructura Encuestado
	ptr = (Encuestado*) malloc(max_size * sizeof(Encuestado));
	male_younger = (Encuestado*) malloc(max_size * sizeof(Encuestado));
	male_older = (Encuestado*) malloc(max_size * sizeof(Encuestado));
	female_younger = (Encuestado*) malloc(max_size * sizeof(Encuestado));
	female_older = (Encuestado*) malloc(max_size * sizeof(Encuestado));
	
	// Condicion que se cumple si se pudo asignar el espacio en memoria
	bool = (ptr != NULL && male_younger != NULL && male_older != NULL && 
		female_younger != NULL && female_older != NULL);
	
	/*
	 * Si se cumple la condicion
	 * que almacena bool.
	 * 
	 * Entonces, se pudo asignar el espacio
	 * en memoria y se procede a la ejecuci??n
	 * del programa.
	 * 
	 * Sino, mostrara en pantalla que no se pudo
	 * realizar la asignacion de espacio en memoria
	 * y finaliza el programa.
	*/
	
	if (bool) {
		do {
			printf("----- Programa de Encuestas -----\n\n");
			
			// Mostrar Opciones
			display_stgs(n_opt, 60, options); printf("\n");
			
			// Elegir Opcion
			opt = get_option(1, n_opt, "Opcion");
			
			printf("\n---\n\n");
			
			// Acciones
			switch(opt) {
				// Registro de Datos
				case 1:
				
					/*
					 * Si el espacio asignado en memoria
					 * se llena completamente. Entonces,
					 * se asigna mas memoria utilizando malloc.
					 * 
					 * Este paso se ejecuta para cada apuntador
					 * utilizado en el programa.
					*/
					
					if (max_size == size[0]) {
						printf("El Espacio Asignado se ha llenado\nAsignando mas memoria...\n");
						max_size += 50;
						ptr = realloc(ptr, max_size * sizeof(Encuestado));
						male_younger = realloc(male_younger, max_size * sizeof(Encuestado));
						male_older = realloc(male_older, max_size * sizeof(Encuestado));
						female_younger = realloc(female_younger, max_size * sizeof(Encuestado));
						female_older = realloc(female_older, max_size * sizeof(Encuestado));
						
						bool = ptr == NULL || male_younger == NULL || male_older == NULL || 
							female_younger == NULL || female_older == NULL;
											
						if (bool) {
							printf("=> Error: La Memoria no fue Asignada");
							exit(0);
						} else {
							printf("Memoria asignada exitosamente!\n\n");
						}
					}
					
					/*
					 * Si ninguno de los apuntadores es NULL,
					 * pide el numero de personas a
					 * encuestar.
					*/
									
					n = (int) get_option(1, max_size - size[0], "Numero de Personas a Encuestar");
					get_information(ptr, n, size);
					break;
					
				// Muestra los primeros 10 encuestados
				case 2:
				
					/*
					 * Si size > 10, entonces significa
					 * que ya se han registrado mas de 10
					 * personas. Por lo tanto, se indica
					 * que se muestren solo 10 registros.
					 * 
					 * Sino, muestra todos los valores que
					 * se tengan actualmente.
					*/
					
					if (size[0] > 10) {
						display(ptr, 10, "Primeros 10 Encuestados");
					} else {
						display(ptr, size[0], "Primeros 10 Encuestados");
					}
					
					clear();
					
					break;
					
				// Muestra todos los encuestados
				case 3:
					display(ptr, size[0], "Todos los Encuestados"); clear();
					break;
					
				// Separa los Datos por Categorias
				case 4:			
					if (size[0] <= 0) {
						printf("No hay registros\n");
					} else {
																		
						organize(ptr, male_younger, female_younger, 
							male_older, female_older, size_organized, size[0], 
							male_younger_size, female_younger_size, male_older_size, 
							female_older_size
						);
						
						/*
						 * La variable size_organized
						 * toma el valor de size.
						 * 
						 * Asi cuando se organice mas informacion
						 * el indice inicia desde el pasado valor de
						 * size, mientras i sea menor que el 
						 * valor actual de size.
						 * 
						 * De esta forma no se reorganiza informacion
						 * que anteriormente fue organizada. Y se evitan
						 * errores.
						*/
						
						size_organized = size[0];
						
						// Mostrar la informacion organizada										
						display(male_younger, male_younger_size[0], "Masculinos (Edad < 25)"); printf("\n");
						display(male_older, male_older_size[0], "Masculinos (Edad > 25)"); printf("\n");
						display(female_younger, female_younger_size[0], "Femeninos  (Edad < 25)"); printf("\n");
						display(female_older, female_older_size[0], "Femeninos  (Edad > 25)"); printf("\n");
					}

					clear();
					break;
				
				case 5:
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
	free(ptr);
	free(male_younger);
	free(male_older);
	free(female_younger);
	free(female_older);

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
		
	} while (true == 1);
		
	return (int) n;
}

// Funcion que Muestra Opciones
void display_stgs(int n, int m, char arr[n][m]) {
	int i;
		
	for (i = 0; i < n; i++) {
		printf("%d) %s\n", i + 1, arr[i]);
	}
	
}

// Funcion que toma la informacion
void get_information(Encuestado *ptr, int n, int size[]) {
	int i, j, aux, size_b = size[0], true = 1;
		
	for (i = size_b; i < (n + size_b); i++) {	
	
		// Obtencion de la informacion
		
		printf("\nNombre: "); scanf("%s", (ptr + i)->name); clear();
		
		printf("Apellido: "); scanf("%s", (ptr + i)->lastname); clear();
		
		(ptr + i)->age = get_option(1, 122, "Edad");
		
		(ptr + i)->id = get_option(1, 2147483647, "Cedula");
		
		// Verificar que sea unica la cedula
		for (j = 0; j < i; j++) {
			if ((ptr + i)->id == (ptr + j)->id) {
				true = 0;
				printf("\nYa existe un encuestado con la misma cedula\nEste no sera registrado\n");
				clear();
				break;
			} else if ((j + 1) == i){
				true = 1;
			}
		}
		
		/*
		 * Si la cedula es diferente
		 * a uno registrado anteriormente.
		 * Entonces continua el registro.
		*/
		
		if (true) {
			// Si aux == 1 es masculino, sino es femenino
			aux = (int) get_option(0, 1, "Sexo (M = 1 | F = 0)");
			
			if (aux) {
				strcpy((ptr + i)->sex, "M");
			} else {
				strcpy((ptr + i)->sex, "F");
			}
							
			printf("\nLista de Canciones Favs. (en orden de preferencia):\n\n"); clear();
			
			for (j = 0; j < 5; j++) {
				printf("   %d) ", j + 1);
				fgets((ptr + i)->songs[j], sizeof((ptr + i)->songs[j]), stdin);
				
				// Eliminando la \n al hacer enter
				
				/*
				 * Accedemos a la ultima letra de la
				 * cadena introducida y se cambia la 
				 * nueva linea \n, por \0 el cual
				 * indica que es el final de la cadena.
				*/
				
				(ptr + i)->songs[j][strlen((ptr + i)->songs[j]) - 1] = '\0';
				
				/*
				 * Si la cadena esta vacia, entonces
				 * reduce en 1 el valor de j. Para
				 * que vuelva a pedir la introduccion
				 * de la cancion en esa posicion.
				*/
				
				if (strlen((ptr + i)->songs[j]) == 0) {
					j--;
				}
			}
			
			size[0]++;
		} else {
			/*
			 * Si la cedula estaba anteriormente
			 * registrada. Entonces, resta en 1
			 * a i y a n.
			*/
			
			i--;
			n--;
		}
	}
}

// Funcion que Organiza los Datos
void organize(
	Encuestado *ptr, Encuestado *male_younger, Encuestado *female_younger,
	Encuestado *male_older, Encuestado *female_older, int size_organized,
	int size, int male_younger_size[0], int female_younger_size[0],
	int male_older_size[0], int female_older_size[0]
) {
		
	int i;
				
	for (i = size_organized; i < size; i++) {
		if (strcmp((ptr + i)->sex, "M") == 0) {
			if ((ptr + i)->age < 25) {
				// Mover masculino a male_younger
				memmove((male_younger + male_younger_size[0]), (ptr + i), sizeof(Encuestado));
				male_younger_size[0]++;
			} else {
				// Mover masculino a male_older 
				memmove((male_older + male_older_size[0]), (ptr + i), sizeof(Encuestado));
				male_older_size[0]++;
			}
		} else {
			if ((ptr + i)->age < 25) {
				// Mover femenina a female_younger
				memmove((female_younger + female_younger_size[0]), (ptr + i), sizeof(Encuestado));
				female_younger_size[0]++;
			} else {
				// Mover femenina a female_older
				memmove((female_older + female_older_size[0]), (ptr + i), sizeof(Encuestado));
				female_older_size[0]++;
			}
		}
	}
}

// Funcion que muestra la informacion
void display(Encuestado *ptr, int n, char *str) {
	int i, j;
	
	printf("----- %s -----", str);
	
	if (n <= 0) {
		printf("\n\nNo hay Registros\n\n");
	} else {
		for (i = 0; i < n; i++) {
			printf("\n\n--- %03d ---\n\n", i + 1);
			
			printf("Nombre: %s\nApellido: %s\nSexo: %s\nCedula: %d\nEdad: %d",
				(ptr + i)->name, (ptr + i)->lastname, (ptr + i)->sex,
				(ptr + i)->id, (ptr + i)->age
			);
					
			printf("\n\n- Canciones Favoritas -\n\n");
			
			for (j = 0; j < 5; j++) {
				printf("%d) %s\n", j + 1, (ptr + i)->songs[j]);
			}
		}
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----- Estructura de la Encuesta -----

typedef struct Resultados {
	char name[50];
	char lastname[50];
	char career[50];
	char objectives[5][20];
	int  approved;
	int  id;
} Resultado;

// ----- Declaracion de Funciones -----

float get_n();
int   get_option(int min, int max, char *str);
void  clear();
void  display_stgs(int n, int m, char arr[n][m]);
void  get_information(Resultado *ptr, int n, int size[]);
void  display(Resultado *ptr, int size, char *type, char *prompt);

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
	Resultado *ptr;
	
	char options[][60] = {"Registrar Resultado",
		"Mostrar Estudiantes Aprobados",
		"Mostrar Todos los Estudiantes",
		"Finalizar"};
		
	int n = 0, size[] = {0}, max_size = 100, 
		opt, n_opt = 4, true = 1;
		
	// Asignando memoria con valor max_size de la estructura Encuestado
	ptr = (Resultado*) malloc(max_size * sizeof(Resultado));
	
	if (ptr != NULL) {
		do {
			printf("----- Programa de Resultados de Evaluacion -----\n\n");
			
			// Mostrar Opciones
			display_stgs(n_opt, 60, options); printf("\n");
			
			// Elegir Opcion
			opt = get_option(1, n_opt, "Opcion");
			
			printf("\n---\n\n");
			
			// Acciones
			switch(opt) {
				
				// Agregar Resultado
				case 1:
					// Verificar si el registro esta lleno
					if (max_size == size[0]) {
						printf("El Espacio Asignado se ha llenado\nAsignando mas memoria...\n");
						max_size += 50;
						ptr = realloc(ptr, max_size * sizeof(Resultado));
						
						if (ptr == NULL) {
							printf("=> Error: La Memoria no fue Asignada");
							exit(0);
						} else {
							printf("Memoria asignada exitosamente!\n\n");
						}
					}
					
					n = (int) get_option(1, max_size - size[0], "Numero de Estudiantes a Registar");
					get_information(ptr, n, size);
					clear();
					break;
				
				// Mostrar Aprobados
				case 2:
					display(ptr, size[0], "approved", "Estudiantes Aprobados"); clear();
					break;
				
				// Mostrar Todos
				case 3:
					display(ptr, size[0], "all", "Todos los Estudiantes"); clear();
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
	free(ptr);
	
	printf("----- Finalizado -----");
	
	printf("\n\nCoded with \u2764 by Alvaro");
		
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

void get_information(Resultado *ptr, int n, int size[]) {
	int i, j, size_b = size[0], true = 1, count, note;
	char str[15];
	
	for (i = size_b; i < (n + size_b); i++) {
		
		// Obtencion de la informacion
		printf("\nNombre: "); scanf("%s", (ptr + i)->name); clear();
		
		printf("Apellido: "); scanf("%s", (ptr + i)->lastname); clear();
		
		for (j = 0; j < 1; j++) {
			printf("Carrera: "); 
			fgets((ptr + i)->career, sizeof((ptr + i)->career), stdin);
			
			/*
			 * Accedemos a la ultima letra de la
			 * cadena introducida y se cambia la 
			 * nueva linea \n, por \0 el cual
			 * indica que es el final de la cadena.
			*/
					
			(ptr + i)->career[strlen((ptr + i)->career) - 1] = '\0';
			
			/*
			 * Si la cadena esta vacia, entonces
			 * reduce en 1 el valor de j. Para
			 * que vuelva a pedir la introduccion
			 * de la cancion en esa posicion.
			*/
					
			if (strlen((ptr + i)->career) == 0) {
				j--;
			}			
		}
		
		(ptr + i)->id = get_option(1, 2147483647, "Cedula");
		
		// Verificar que sea unica la cedula
		for (j = 0; j < i; j++) {
			if ((ptr + i)->id == (ptr + j)->id) {
				true = 0;
				printf("\nYa existe un estudiante con la misma cedula\nEste no sera registrado\n");
				break;
			} else if ((j + 1) == i){
				true = 1;
			}
		}
		
		if (true) {	
			printf("\n\n- Objetivos (Aprovado = 1 | No Aprobado = 0) -\n\n");
			
			printf("Minimo para aprobar son 3 Objetivos\nNumero de Objetivos = 5\n\n");
								
			for (j = 0, count = 0; j < 5; j++) {
				sprintf(str, "Objetivo %d", j + 1);
				note = get_option(0, 1, str);
				
				if (note) {
					strcpy((ptr + i)->objectives[j], "Aprobado");
					count++;
				} else {
					strcpy((ptr + i)->objectives[j], "No Aprobado");
				}
			}
			
			if (count >= 3) {
				(ptr + i)->approved = 1;
			} else {
				(ptr + i)->approved = 0;
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

// Funcion que muestra la informacion
void display(Resultado *ptr, int size, char *type, char *prompt) {
	int i, true = 1;
	
	printf("----- %s -----", prompt);
	
	// Funcion que despliega la informacion de la posicion i
	void show(int i) {
		int j;
		
		printf("\n\n--- %03d ---\n\n", i + 1);
		
		printf("Nombre: %s\nApellido: %s\nCarrera: %s\nCedula: %d\nAprobado: %d",
			(ptr + i)->name, (ptr + i)->lastname, (ptr + i)->career, 
			(ptr + i)->id, (ptr + i)->approved
		);
		
		printf("\n\n- Objetivos -\n\n");
			
		for (j = 0; j < 5; j++) {
			printf("%d) %s\n", j + 1, (ptr + i)->objectives[j]);
		}
	}
	
	/*
	 * Si type es igual a all,
	 * entonces imprime todos los 
	 * registros.
	 * 
	 * Si type es igual a approved,
	 * imprime todos los que
	 * aprobaron.
	*/
	
	if (strcmp(type, "all") == 0) {
		for (i = 0; i < size; i++) {
			show(i);
			true = 0;
		}
	} else if (strcmp(type, "approved") == 0) {
		for (i = 0; i < size; i++) {
			if ((ptr + i)->approved) {
				show(i);
				true = 0;
			}
		}
	} else {
		true = 1;
	}
	
	if (true) {
		printf("\n\nNo hay Registros\n\n");
	}
}

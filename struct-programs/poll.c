#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ----- Estructura de la Encuesta -----

typedef struct Encuesta {
	char name[50];
	char lastname[50];
	char sex[10];
	char songs[5][50];
	int age;
	int id;
} Encuestado;

// ----- Declaracion de Funciones -----

int get_option(int min, int max, char *str);
float get_n();
void display_stgs(int n, int m, char arr[n][m]);
void get_information(Encuestado *ptr, int n, int size);
void display(Encuestado *ptr, int n);
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
	Encuestado *ptr;
	
	char options[][50] = {"Agregar Encuestados", 
		"Imprimir Primeros 10 Encuestados",
		"Imprimir Todos los Encuestados",
		"Finalizar Encuesta"};
			
	int n = 0, size = 0, max_size = 250, opt, n_opt = 4, true = 1;
		
	// Asignando memoria para max_size de la estructura Encuestado
	ptr = (Encuestado*) malloc(max_size * sizeof(Encuestado));
	
	do {
		printf("----- Programa de Encuestas -----\n\n");
		
		// Mostrar Opciones
		display_stgs(n_opt, 50, options);
		
		printf("\n");
		
		// Elegir Opcion
		opt = get_option(1, n_opt, "Opcion");
		
		printf("\n---\n\n");
		
		// Acciones
		switch(opt) {
			case 1:
				n = (int) get_option(1, max_size - size, "Numero de Personas a Encuestar");
				get_information(ptr, n, size);
				size += n;
				break;
				
			case 2:								
				if (size > 10) {
					display(ptr, 10);
				} else {
					display(ptr, size);
				}
				
				clear();
				
				break;
				
			case 3:
				display(ptr, size);
				
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
		
	} while (true == 1);
	
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
		scanf("%*[^\n]");
		clear();
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
void get_information(Encuestado *ptr, int n, int size) {
	int i, j, aux;
		
	for (i = size; i < (n + size); i++) {		
		// Obtencion de la informacion
		printf("\nNombre: "); scanf("%s", (ptr + i)->name); clear();
		
		printf("Apellido: "); scanf("%s", (ptr + i)->lastname); clear();
		
		aux = (int) get_option(1, 2, "Sexo (M = 1 v F = 2)");
		
		// Si aux == 1 es masculino, sino es femenino
		
		if (aux == 1) {
			strcpy((ptr + i)->sex, "M");
		} else {
			strcpy((ptr + i)->sex, "F");
		}
						
		(ptr + i)->id = get_option(1, 2147483647, "Cedula");
		
		(ptr + i)->age = get_option(1, 122, "Edad");
		
		printf("\nLista de Canciones Favs. (en orden de preferencia):\n\n"); clear();
		
		for (j = 0; j < 5; j++) {
			printf("   %d) ", j + 1);
			scanf("%[^\n]%*c", (ptr + i)->songs[j]);
		}
	}
	
}

// Funcion que muestra la informacion
void display(Encuestado *ptr, int n) {
	int i, j;
	
	if (n <= 0) {
		printf("No hay Registros\n\n");
	} else {
		printf("----- Encuestados -----");
		
		for (i = 0; i < n; i++) {
			printf("\n\n--- %02d ---\n\n", i + 1);
			printf("Nombre: %s", (ptr + i)->name);
			printf("\nApellido: %s", (ptr + i)->lastname);
			printf("\nSexo: %s", (ptr + i)->sex);
			printf("\nCedula: %d", (ptr + i)->id);
			printf("\nEdad: %d", (ptr + i)->age);
					
			printf("\n\n- Canciones Favoritas -\n\n");
			
			for (j = 0; j < 5; j++) {
				printf("%d) %s\n", j + 1, (ptr + i)->songs[j]);
			}
		}		
	}
	
}

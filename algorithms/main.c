#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----- Declaracion de Funciones -----

float get_n(char *str);
int   get_option(int min, int max, char *str);
int   partition(float arr[], int start, int end);
void  clear();
void  display_stgs(int n, int m, char arr[n][m]);
void  get_arr(float arr[], int size);
void  swap(float arr[], int first_pos, int second_pos);
void  bubble(float arr[], int size);
void  insertion(float arr[], int size);
void  selection(float arr[], int size);
void  quicksort(float arr[], int start, int end);
void  print_array(float arr[], int size);

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
	int   size, true = 1, opt, n_opt = 6, max_size = 1000;
	float arr[max_size];
	
	char options[][60] = {"Ordenamiento de Burbuja", 
		"Ordenamiento por Insercion",
		"Ordenamiento por Seleccion",
		"Ordenamiento Rapido (QuickSort)",
		"Busqueda Binaria",
		"Finalizar"};
	
	do {
		printf("----- Programa de Ordenamiento y Busqueda -----\n\n");
		
		// Mostrar Opciones
		display_stgs(n_opt, 60, options); printf("\n");
		
		// Elegir Opcion
		opt = get_option(1, n_opt, "Opcion");
		
		printf("\n---\n\n");
		
		if (opt != 6) {
			// Obtener Matriz
			size = get_option(1, max_size, "Numero de Elementos"); printf("\n");
			get_arr(arr, size);

			// Ordenar segun Metodo Elegido
			switch(opt) {
				// burbuja
				case 1:
					bubble(arr, size);
					break;
					
				// insercion
				case 2:
					insertion(arr, size);
					break;
					
				// seleccion
				case 3:
					selection(arr, size);
					break;
					
				// qs
				case 4:
					quicksort(arr, 0, size - 1);
					break;
					
				// binaria
				case 5:
					clear();
					break;

				// default
				default:
					true = 0;
					break;
			}

			// Imprimir Matriz
			printf("\n- Matriz Ordenada - \n\n");
			print_array(arr, size); printf("\n");
			clear();
		} else {
			true = 0;
		}
		
		// Limpiar Pantalla
		printf("\nPresione Enter para Continuar\n");
		getchar();
		system(clear_str);
		
	} while (true);
	
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
float get_n(char *str) {
	int i = 0;
	float n;
	
	/*
	 * Al introducir un valor no numerico
	 * descarta la nueva linea
	 * y luego hace una limpieza del bufer.
	 * Retornando -1.
	 * 
	 * Sino, retorna el valor numerico
	 * que ha sido introducido.
	*/
		
	do {
		printf("%s: ", str);
		
		// Si i > 0, busca las nuevas lineas, sino suma 1 a i
		(i > 0) ? scanf("%*[^\n]") : i++;
		
	} while(!scanf("%f", &n));
	
	return n;
}

// Funcion que Obtiene Opciones
int get_option(int min, int max, char *str) {
	int true = 1;
	float n;
	
	do {
		n = get_n(str);
		
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

// Funcion que realiza la particion de la matriz
int partition(float arr[], int start, int end) {
	
	/*
	 * Esta funcion toma al ultimo
	 * elemento de la matriz como pivote.
	 * Colocando el pivote en su posicion
	 * correcta en la matriz, colocando
	 * los elementos mas pequenios a
	 * la izquierda y los mas grandes
	 * a la derecha del pivote.
	*/
	
    int i, j = start - 1;
    float pivot = arr[end];
    
    /*
     * La variable j indica el indice 
     * del elemento mas pequenio y la
     * correcta posicion del pivote.
    */

    for (i = start; i <= end - 1; i++) {
		
		// Si el numero actual es menor que el pivote
        if (arr[i] < pivot) {
            // Incremena el indice de numeros pequenios
            j++;

            // Intercambia las posiciones
            swap(arr, j, i);
        }
    }
	
	// Coloca el pivote en la posicion correcta
    swap(arr, j + 1, end);

    return (j + 1);
}

// Obtener Elementos de una Matriz
void get_arr(float arr[], int size) {
	int i;
	char str[10];
	
	for (i = 0; i < size; i++) {
		sprintf(str, "[%d]", i + 1);
		arr[i] = get_n(str);
	}
}

// Funcion que intercambio posiciones de una matriz
void swap(float arr[], int first_pos, int second_pos) {
    float pivot;
    
    pivot = arr[second_pos];
    arr[second_pos] = arr[first_pos];
    arr[first_pos] = pivot;
}

// Ordenamiento por Burbuja
void bubble(float arr[], int size) {
	int i, j;
	
	// Iteracion que realiza las pasadas
	for (i = 0; i < size; i++) {
		
		// Iteracion que realiza el ordenamiento
		for (j = 0; j < size && (j + 1) < size; j++) {
			/*
			 * Si el elemento actual es mayor
			 * que el elemento siguiente.
			 * Entonces realiza un cambio
			 * de posiciones.
			*/
			
			if (arr[j] > arr[j + 1]) {
				swap(arr, j + 1, j);
			}
		}
	}
}

// Ordenamiento por Insercion
void insertion(float arr[], int size) {
	int i, j;
	float current;
	
	for (i = 1; i < size; i++ ) {
		// Establece el valor actual
		current = arr[i];
		
		/*
		 * Si j > 0 y el valor anterior
		 * es mayor que el valor actual.
		 * Entonces, se asigna a la posicion
		 * actual el valor anterior.
		 * 
		 * Luego, se reduce en 1 el valor de 
		 * j.
		*/
		
		for (j = i; (j > 0) && (arr[j - 1] > current); j--) {
			arr[j] = arr[j - 1];
		}
		
		// Se asigna a la posicion j el valor actual
		arr[j] = current;
	}
}

// Ordenamiento por Seleccion
void selection(float arr[], int size) {
	int i, j, largest_index = 0;
	
	// Pasadas
	for (i = 0; i < (size + i); i++, size--) {
		
		// Busqueda del indice del elemento mayor
		for (j = 0; j < size; j++) {
			if (arr[j] > arr[largest_index]) {
				largest_index = j;
			}
		}
				
		/*
		 * Realiza el intercambio entre
		 * el ultimo elemento actual
		 * de la matriz iterada y el
		 * mayor elemento encontrado.
		*/

		swap(arr, largest_index, size - 1);
		
		// Establece el largest_index a 0
		largest_index = 0;
	}
}

// Ordenamiento rapido (QuickSort)
void quicksort(float arr[], int start, int end) {
    int split;

    // Si el indice inicial < final
    if (start < end) {
		
		/*
		 * Coloca a end (el pivote) en
		 * su posicion correcta y
		 * retorna el indice de 
		 * particion de la matriz.
		*/
		
        split = partition(arr, start, end);

        // Ordena la parte izquierda de la matriz particionada
        quicksort(arr, start, split - 1);

        // Ordena la parte derecha de la matriz particionada
        quicksort(arr, split + 1, end);
    }
}

// Funcion que Muestra una Matriz
void print_array(float arr[], int size) {
	// Impresion de cada elemento de la matriz
	if (size == 1) {
		printf("{%f}", arr[0]);
	} else {
		for (int i = 0; i < size; i++) {
			if (size == 1) {
				printf("{%f}, ", arr[i]);
			} else {
				if (i == 0) {
					printf("{%f, ", arr[i]);
				} else if (i + 1 == size) {
					printf("%f}", arr[i]);
				} else {
					printf("%f, ", arr[i]);
				}			
			}
		}		
	}
}

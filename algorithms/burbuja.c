#include <stdio.h>
#include <stdlib.h>

// ----- Declaracion de Funciones -----

int   get_option(int min, int max, char *str);
void  get_arr(float arr[], int size);
void  swap(float arr[], int first_pos, int second_pos);
void  bubble(float arr[], int size);
void  print_array(float arr[], int size);
float get_n(char *str);

// ----- Main -----

int main() {
	int size, max_size = 350;
	
	printf("----- Ordenamiento de Burbuja -----\n\n");

	size = get_option(1, max_size, "Tamanio de Matriz");
	
	float arr[size];
	
	printf("\n----- Matriz -----\n\n");
	
	get_arr(arr, size);
	
	printf("\n\n----- Antes\n\n"); 
	print_array(arr, size);
	
	bubble(arr, size);
	
	printf("\n\n----- Despues\n\n"); 
	print_array(arr, size);
	
	return 0;
}

// ----- Definicion de Funciones -----

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

// Obtener Elementos de una Matriz
void get_arr(float arr[], int size) {
	int i;
	char str[10];
	
	for (i = 0; i < size; i++) {
		sprintf(str, "[%d]", i);
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

// Funcion que Muestra una Matriz
void print_array(float arr[], int size) {
	// Impresion de cada elemento de la matriz
	if (size == 1) {
		printf("{%.2f}", arr[0]);
	} else {
		for (int i = 0; i < size; i++) {
			if (size == 1) {
				printf("{%.2f}, ", arr[i]);
			} else {
				if (i == 0) {
					printf("{%.2f, ", arr[i]);
				} else if (i + 1 == size) {
					printf("%.2f}", arr[i]);
				} else {
					printf("%.2f, ", arr[i]);
				}			
			}
		}		
	}
}

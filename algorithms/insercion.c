#include <stdio.h>
#include <stdlib.h>

// ----- Declaracion de Funciones -----

int   get_option(int min, int max, char *str);
float get_n(char *str);
void  get_arr(float arr[], int size);
void  insertion(float arr[], int size);
void  print_array(float arr[], int size);

// ----- Main -----

int main() {
	int size, max_size = 350;
	
	printf("----- Ordenamiento por Insercion -----\n\n");
	
	size = get_option(1, max_size, "Tamanio de Matriz");
	
	float arr[size];
	
	printf("\n----- Matriz -----\n\n");
	
	get_arr(arr, size);
	
	printf("\n\n----- Antes\n\n"); 
	print_array(arr, size);
	
	insertion(arr, size);
	
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

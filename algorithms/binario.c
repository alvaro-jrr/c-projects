#include <stdio.h>
#include <stdlib.h>

// ----- Declaracion de Funciones -----

int   get_option(int min, int max, char *str);
float get_n(char *str);
void  get_arr(float arr[], int size);
int   binary_search(float arr[], int size, float key);
void  binary_insertion(float arr[], int size);
void  print_array(float arr[], int size);

int main() {
    int size, max_size = 350;
	
	printf("----- Ordenamiento por Insercion Binaria -----\n\n");

	size = get_option(1, max_size, "Tamanio de Matriz");
	
    float arr[size];
    
	printf("\n----- Matriz -----\n\n");
	
	get_arr(arr, size);
	
	printf("\n\n----- Antes\n\n"); 
	print_array(arr, size);
	
    binary_insertion(arr, size);

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

// Busqueda Binaria
int binary_search(float arr[], int size, float key) {
    int low = 0, high = size, mid;

	// Mientras low < high
    while (low < high) {
		// Obtencion del indice medio
        mid = (low + high) / 2;

		/*
		 *
		 * Si el elemento medio es menor o
		 * igual a "key". Entonces low
		 * toma el valor de "mid" + 1.
		 * 
		 * Sino, high toma el valor de "mid"
		*/
	
        if (arr[mid] <= key) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

	// Retorno del indice donde se debe insertar
    return low;
}

// Insercion Binaria
void binary_insertion(float arr[], int size) {
    int i, j, index;
    float key;

	/*
	 * Se asume que el primer elemento
	 * esta ordenado. Por lo tanto,
	 * se inicia el ordenamiento desde
	 * el segundo elemento hasta
	 * el ultimo
	*/

    for (i = 1; i < size; i++) {
		// Elemento a Introducir
        key = arr[i];

		// Obtencion del indice donde se debe introducir "key"
        index = binary_search(arr, i, key);

        j = i;

        // Moviendo cada elemento desde index hasta i (hacia la derecha)
        while (j > index) {
            arr[j] = arr[j - 1];
            j--;
        }

        // Insertando "key" en su correcta posicion
        arr[index] = key;
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

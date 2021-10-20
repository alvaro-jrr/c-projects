#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----- Estructura de la Encuesta -----

typedef struct Reserva {
	char name[50];
	char lastname[50];
	char email[80];
	char phone[20];
	int  age;
	int  id;
	int  seat_id;
	int  is_confirmed;
} Reservado;

// ----- Declaracion de Funciones -----

float get_n();
int get_option(int min, int max, char *str);
int get_seat(Reservado *ptr, int size);
void clear();
void validate(Reservado *ptr, int size, int type, char *prompt, char *success);
void display_stgs(int n, int m, char arr[n][m]);
void get_information(Reservado *ptr, int n, int size);
void display(Reservado *ptr, int n, int is_confirmed, char *str);

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
	Reservado *ptr;
	
	char options[][60] = {"Agregar Reservacion",
		"Confirmar Reservacion",
		"Cancelar Reservacion",
		"Mostrar En Espera",
		"Mostrar Confirmados",
		"Finalizar Reserva"};
		
	int n = 0, size = 0, max_size = 80, opt, n_opt = 6, true = 1;
	
	// Asignando memoria con valor max_size de la estructura Reservado
	ptr = (Reservado*) malloc(max_size * sizeof(Reservado));
	
	if (ptr != NULL) {
		do {
			printf("----- Programa de Reservas -----\n\n");
			
			// Mostrar Opciones
			display_stgs(n_opt, 60, options); printf("\n");
			
			// Elegir Opcion
			opt = get_option(1, n_opt, "Opcion");
			
			printf("\n---\n\n");
			
			// Acciones
			switch(opt) {
				
				// Reservar Asiento
				case 1:
					if (size == max_size) {
						printf("Lo sentimos, todos los asientos estan ocupados\n");
					} else {
						n = (int) get_option(1, max_size - size, "Numero de Personas a Reservar");
						get_information(ptr, n, size);
						size += n;	
					}
										
					clear();

					break;
					
				// Confirmar Reservacion
				case 2:
					validate(ptr, size, 1, "Nro. de Asiento a Confirmar", 
						"Reservacion confirmada existosamente"
					);
						
					clear();
					break;
				
				// Cancelar Reservacion
				case 3:
					validate(ptr, size, -1, "Nro. de Asiento a Cancelar", 
						"Reservacion cancelada existosamente"
					);
					
					clear();
					break;
				
				// Mostrar Reservaciones en Espera
				case 4:
					display(ptr, size, 0, "Reservaciones en Espera");
					printf("\n");
					clear();
					break;
					
				// Mostrar Reservaciones Confirmadas
				case 5:
					display(ptr, size, 1, "Reservaciones Confirmados");
					printf("\n");
					clear();
					break;
				
				// Salir del Programa
				case 6:
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

// Funcion que obtiene el asiento a reservar
int get_seat(Reservado *ptr, int size) {
	int i, true = 1, n;
	
	do {
		n = get_option(1, 80, "Nro. Asiento");
				
		if (size > 0) {
			for (i = 0; i < size; i++) {			
				if (((ptr + i)->seat_id) == n) {
					printf("\nLo sentimos, asiento tomado\n\n");
					true = 1;
					break;
				} else {
					true = 0;
				}
			}			
		} else {
			true = 0;
		}

	} while (true);
	
	return n;
}


// Funcion que toma la informacion
void get_information(Reservado *ptr, int n, int size) {
	int i;
		
	for (i = size; i < (n + size); i++) {
		// --- Obtencion de la informacion ---
		
		// Datos Personales
		
		printf("\nNombre: "); scanf("%s", (ptr + i)->name); clear();
		
		printf("Apellido: "); scanf("%s", (ptr + i)->lastname); clear();
		
		printf("Email: "); scanf("%s", (ptr + i)->email); clear();
		
		printf("Telefono: "); scanf("%s", (ptr + i)->phone); clear();
		
		(ptr + i)->id = get_option(1, 2147483647, "Cedula");
		
		(ptr + i)->age = get_option(1, 122, "Edad");
		
		// Asiento
		
		(ptr + i)->seat_id = get_seat(ptr, i);
		
		// Establecer valor para is_confirmed
		
		/*
		 * Si is_confirmed == 0,
		 * entonces quiere decir que aun
		 * no esta confirmado.
		 * 
		 * Si is_confirmed == 1
		 * entonces el asiento ha sido
		 * confirmado.
		 * 
		 * Si is_confirmed == -1,
		 * entonces el asiento ha sido
		 * cancelado.
		*/
		
		(ptr + i)->is_confirmed = 0;
	}
}

// Funcion que confirma o cancela la reservacion
void validate(Reservado *ptr, int size, int type, char *prompt, char *success) {
	int i, n, true = 1;
	
	if (size <= 0) {
		printf("No hay registros\n");
	} else {
		do {
			n = get_option(1, 80, prompt);
			
			for (i = 0; i < size; i++) {
				if (((ptr + i)->is_confirmed == 0) && ((ptr + i)->seat_id == n)) {
					(ptr + i)->is_confirmed = type;
					printf("%s\n", success);
					true = 0;
					break;
				} else if((i + 1 == size) && (true)) {
					printf("Este asiento ya fue confirmado o cancelado\n");
					true = 0;
				}
			}
			
		} while (true);
	}
}

// Funcion que muestra la informacion
void display(Reservado *ptr, int n, int is_confirmed, char *str) {
	int i, true = 1;
	
	printf("----- %s -----", str);
	
	if (n <= 0) {
		printf("\n\nNo hay Registros\n\n");
	} else {
		for (i = 0; i < n; i++) {
			if ((ptr + i)->is_confirmed == is_confirmed) {
				printf("\n\n--- %03d ---\n\n", i + 1);
				
				printf("Nombre: %s\nApellido: %s\nEmail: %s\nCedula: %d\nEdad: %d\nTelefono: %s\nAsiento: %d",
					(ptr + i)->name, (ptr + i)->lastname, (ptr + i)->email,
					(ptr + i)->id, (ptr + i)->age, (ptr + i)->phone, (ptr + i)->seat_id
				);
				
				true = 0;
			}
		}
	}
	
	if (true) {
		printf("\n\nNo hay Registros\n\n");
	}
}
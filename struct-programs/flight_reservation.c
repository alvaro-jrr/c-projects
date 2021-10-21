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
	int  is_empty;
	int  registered_before;
} Reservado;

// ----- Declaracion de Funciones -----

float get_n();
int   get_option(int min, int max, char *str);
int   get_seat(Reservado *ptr, int size);
int   get_empty(Reservado *ptr, int size[], int max);
int   is_full(Reservado *ptr, int max_size);
void  clear();
void  validate(Reservado *ptr, int size, int type, char *prompt, char *success);
void  display_stgs(int n, int m, char arr[n][m]);
void  get_information(Reservado *ptr, int n, int size[]);
void  display(Reservado *ptr, int n, int is_confirmed, char *str);

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
		
	int i, n = 0, size[] = {0}, max_size = 80, opt, n_opt = 6, true = 1;
	
	// Asignando memoria con valor max_size de la estructura Reservado
	ptr = (Reservado*) malloc(max_size * sizeof(Reservado));
	
	if (ptr != NULL) {
		
		/*
		 * Inicializando is_empty a 1,
		 * declarando que esta vacio.
		 * 
		 * Y registered_before a 0,
		 * declarando que no ha sido
		 * registrado anteriormente.
		*/
				
		for (i = 0; i < max_size; i++) {
			(ptr + i)->is_empty = 1;
			(ptr + i)->registered_before = 0;
		}
		
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
					if ((size[0] == max_size) && (is_full(ptr, max_size))) {
						printf("Lo sentimos, todos los asientos estan ocupados\n");
					} else {
						n = (int) get_option(1, max_size - size[0], "Numero de Personas a Reservar");
						get_information(ptr, n, size);	
					}
										
					clear();

					break;
					
				// Confirmar Reservacion
				case 2:
					validate(ptr, size[0], 1, "Nro. de Asiento a Confirmar", 
						"Reservacion confirmada existosamente"
					);
						
					clear();
					break;
				
				// Cancelar Reservacion
				case 3:
					validate(ptr, size[0], -1, "Nro. de Asiento a Cancelar", 
						"Reservacion cancelada existosamente"
					);
					
					clear();
					break;
				
				// Mostrar Reservaciones en Espera
				case 4:
					display(ptr, size[0], 0, "Reservaciones en Espera");
					printf("\n");
					clear();
					break;
					
				// Mostrar Reservaciones Confirmadas
				case 5:
					display(ptr, size[0], 1, "Reservaciones Confirmados");
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

// Obtener posicion vacia
int get_empty(Reservado *ptr, int size[], int max) {
	int i, n, size_b = size[0];
	
	if (size_b == 0) {
		n = 0;
		size[0]++;
	} else {
		for (i = 0; i < max; i++) {
						
			/*
			 * Si se cumple que esta vacio
			 * y que no ha sido registrado antes.
			 * Entonces, es un registro nuevo y
			 * se incrementa el contador de 
			 * registros.
			 * 
			 * Si se cumple que esta vacio y que
			 * ademas, ha sido registrado antes.
			 * No se incrementa el contador de registros.
			*/
			
			if (((ptr + i)->is_empty == 1) && ((ptr + i)->registered_before == 0)) {
				n = i;
				size[0]++;
				break;
			} else  if (((ptr + i)->is_empty == 1) && ((ptr + i)->registered_before == 1)) {
				n = i;
				break;
			} else {
				n = -1;
			}
		}
	}

	return n;
}

// Verificar si esta completa los registros

int is_full(Reservado *ptr, int max_size) {
	int i, n = 0, true = 1;
	
	for (i = 0; i < max_size; i++) {
		if ((ptr + i)->is_empty == 0) {
			n++;
		}
	}
	
	/* 
	 * Si n es igual a max_size
	 * entonces, si esta completo.
	 * 
	 * Sino, no lo esta y true = 0.
	*/
	
	if (n == max_size) {
		true = 1;
	} else {
		true = 0;
	}
		
	return true;
}

// Funcion que toma la informacion
void get_information(Reservado *ptr, int n, int size[]) {
	int i, size_b = size[0], add_index;
			
	for (i = size_b; i < (n + size_b); i++) {
		// --- Obtencion de la informacion ---
		
		// Obtener posicion donde agregar el registro
		add_index = get_empty(ptr, size, (n + size_b));
				
		// Obtener Datos Personales
		
		printf("\nNombre: "); scanf("%s", (ptr + add_index)->name); clear();	
		printf("Apellido: "); scanf("%s", (ptr + add_index)->lastname); clear();
		printf("Email: "); scanf("%s", (ptr + add_index)->email); clear();
		printf("Telefono: "); scanf("%s", (ptr + add_index)->phone); clear();
		(ptr + add_index)->id = get_option(1, 2147483647, "Cedula");
		(ptr + add_index)->age = get_option(1, 122, "Edad");
		
		// Obtener Asiento
		(ptr + add_index)->seat_id = get_seat(ptr, i);
		
		/*
		 * Establecemos el valor de is_confirmed a 0,
		 * que indica que esta en espera.
		 * 
		 * Establecemos is_empty a 0, ya que indica
		 * que no esta vacio.
		 * 
		 * Establecemos registered_before a 1,
		 * que indica que ha sido registrado
		 * anteriormente.
		*/
		
		(ptr + add_index)->is_confirmed = 0;
		(ptr + add_index)->is_empty = 0;
		(ptr + add_index)->registered_before = 1;
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
					
					/*
					 * Cuando type tiene valor de -1,
					 * entonces se esta cancelando
					 * un registro. Por lo tanto,
					 * se establece que es vacio
					 * y el asiento a 0.
					*/
					
					if (type == -1) {
						(ptr + i)->is_empty = 1;
						(ptr + i)->seat_id  = 0;
					}
					
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
				printf("\n\n--- %02d ---\n\n", i + 1);
				
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----- Estructura de la Encuesta -----

typedef struct Ciudadanos {
	char name[50];
	char lastname[50];
	char civil_state[50];
	char nationality[50];
	char sex[5];
	int  age;
	int  id;
	int  is_active;
	int  is_military;
	int  plane_feet;
} Ciudadano;

// ----- Declaracion de Funciones -----

float get_n();
int   get_option(int min, int max, char *str);
void  clear();
void  display_stgs(int n, int m, char arr[n][m]);
void  get_state(Ciudadano *ptr, int size, int age);
void  get_information(Ciudadano *ptr, int n, int size[]);
void  display(Ciudadano *ptr, int size, char *type, char *prompt);

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
	Ciudadano *ptr;
	
	char options[][60] = {"Agregar Ciudadano",
		"Mostrar Todos",
		"Mostrar con Capacidad de Voto",
		"Mostrar con Capacidad de Prestar Servicio Militar",
		"Finalizar"};
		
	int n = 0, size[] = {0}, max_size = 100, opt, n_opt = 5, true = 1;
	
	// Asignando memoria con valor max_size de la estructura Ciudadano
	ptr = (Ciudadano*) malloc(max_size * sizeof(Ciudadano));
	
	if (ptr != NULL) {
		
		do {
			printf("----- Programa de Registro de Ciudadanos -----\n\n");
			
			// Mostrar Opciones
			display_stgs(n_opt, 60, options); printf("\n");
			
			// Elegir Opcion
			opt = get_option(1, n_opt, "Opcion");
			
			printf("\n---\n\n");
			
			// Acciones
			switch(opt) {
				
				// Agregar Ciudadano
				case 1:
					if (max_size == size[0]) {
						printf("El Espacio Asignado se ha llenado\nAsignando mas memoria...\n");
						max_size += 50;
						ptr = realloc(ptr, max_size * sizeof(Ciudadano));
						
						if (ptr == NULL) {
							printf("=> Error: La Memoria no fue Asignada");
							exit(0);
						} else {
							printf("Memoria asignada exitosamente!\n\n");
						}
					}
					
					n = (int) get_option(1, max_size - size[0], "Numero de Personas a Registrar");
					get_information(ptr, n, size);
					//size += n;
					clear();
					
					break;
					
				// Mostrar todos los Registros
				case 2:
					display(ptr, size[0], "all", "Ciudadanos Registrados"); printf("\n");
					clear();
					break;
					
				// Mostrar los que pueden votar
				case 3:
					display(ptr, size[0], "vote", "Ciudadanos Capaces de Votar"); printf("\n");
					clear();
					break;
					
				// Mostrar los que pueden prestar servicio
				case 4:
					display(ptr, size[0], "militar", "Ciudadanos que Pueden Realizar Servicio"); printf("\n");
					clear();
					break;
					
				// Finalizar el Programa
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

// Funcion que obtiene el estado civil
void get_state(Ciudadano *ptr, int size, int age) {
	char civil_states[][60] = {"Soltero/a", "Casado/a", "Divorcido/a", "Viudo/a"};
	int opt, n_opt = 4;
	
	if (age >= 16) {
		printf("\n--- Opciones de Estado ---\n\n");
		
		display_stgs(n_opt, 60, civil_states); printf("\n");
		
		opt = get_option(1, n_opt, "Estado Civil");
		
		strcpy((ptr)->civil_state, civil_states[opt - 1]);
	} else {
		strcpy((ptr)->civil_state, civil_states[0]);
	}
}

// Funcion que toma la informacion
void get_information(Ciudadano *ptr, int n, int size[]) {	
	int i, j, aux, size_b = size[0], true = 1;
			
	for (i = size_b; i < (n + size_b); i++) {
		// --- Obtencion de la informacion ---
				
		// Obtener Datos Personales
		
		printf("\nNombre: "); scanf("%s", (ptr + i)->name); clear();	
		printf("Apellido: "); scanf("%s", (ptr + i)->lastname); clear();
		(ptr + i)->age = get_option(1, 122, "Edad");
		(ptr + i)->id = get_option(1, 2147483647, "Cedula");
		
		for (j = 0; j < i; j++) {
			if ((ptr + i)->id == (ptr + j)->id) {
				true = 0;
				printf("\nYa existe un ciudadano con la misma cedula\nEste no sera registrado\n");
				break;
			} else if ((j + 1) == i) {
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
				// Si es masculino
				strcpy((ptr + i)->sex, "M");
				
				(ptr + i)->plane_feet = (int) get_option(0, 1, "Pies Planos (Si = 1 | No = 0)");
							
				if ((ptr + i)->age > 17) {
					(ptr + i)->is_military = (int) get_option(0, 1, "Es o fue Militar? (Si = 1 | No = 0)");
					
					if ((ptr + i)->is_military) {
						(ptr + i)->is_active = (int) get_option(0, 1, "Esta Activo? (Si = 1 | No = 0)");	
					} else {
						(ptr + i)->is_active = 0;
					}
					
				} else {
					(ptr + i)->is_active = 0;
					(ptr + i)->is_military = 0;
				}
				
			} else {
				strcpy((ptr + i)->sex, "F");
				(ptr + i)->plane_feet = -1;
				(ptr + i)->is_military = -1;
				(ptr + i)->is_active = -1;
			}
			
			aux = (int) get_option(0, 1, "Nacionalidad (Venezolano/a = 1 | Extranjero/a = 0)");
			
			if (aux) {
				strcpy((ptr + i)->nationality, "Venezolano/a");
			} else {
				strcpy((ptr + i)->nationality, "Extranjero/a");
			}
					
			get_state((ptr + i), size[0], (ptr + i)->age);
			
			// Se suma 1 al numero de agregados
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
void display(Ciudadano *ptr, int size, char *type, char *prompt) {
	int i, bool, true = 1;
	
	printf("----- %s -----", prompt);
	
	// Funcion que despliega la informacion de la posicion i
	void show(int i, int is_male) {
		printf("\n\n--- %03d ---\n\n", i + 1);
		
		printf("Nombre: %s\nApellido: %s\nEdad: %d\nCedula: %d\nSexo: %s\nNacionalidad: %s\nEstado Civil: %s",
			(ptr + i)->name, (ptr + i)->lastname, (ptr + i)->age, (ptr + i)->id, 
			(ptr + i)->sex, (ptr + i)->nationality, (ptr + i)->civil_state
		);
		
		if (is_male) {
			printf("\nPie Plano: %d\nMilitar: %d\nEstado Activo: %d",
				(ptr + i)->plane_feet, (ptr + i)->is_military,
				(ptr + i)->is_active
			);
		}
	}
	
	/*
	 * Si type es igual a all,
	 * entonces imprime todos los 
	 * registros.
	 * 
	 * Si type es igual a vote,
	 * imprime todos los que
	 * son capaces de votar.
	 * 
	 * Si type es igual a militar,
	 * imprime todos los que son
	 * capaces de hacer servicio
	 * militar.
	*/
	
	if (strcmp(type, "all") == 0) {
		for (i = 0; i < size; i++) {
			show(i, strcmp((ptr + i)->sex, "M") == 0);			
			true = 0;
		}
	} else if (strcmp(type, "vote") == 0) {
		for (i = 0; i < size; i++) {
			if ((ptr + i)->age >= 18) {
				show(i, strcmp((ptr + i)->sex, "M") == 0);
				true = 0;				
			}
		}
	} else if (strcmp(type, "militar") == 0) {		
		for (i = 0; i < size; i++) {
			
			bool = (strcmp((ptr + i)->sex, "M") == 0) 
				&& (strcmp((ptr + i)->nationality, "Venezolano/a") == 0)
				&& (strcmp((ptr + i)->civil_state, "Soltero/a") == 0)
				&& ((ptr + i)->age >= 18) 
				&& ((ptr + i)->age <= 30)
				&& ((ptr + i)->is_military == 0)
				&& ((ptr + i)->is_active == 0);
			
			if (bool) {
				show(i, 1);
				true = 0;
			}
		}
	}
	
	if (true) {
		printf("\n\nNo hay Registros\n\n");
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*Declaración de tipo de datos personalizados*/
typedef char tString [30];
typedef char tString60 [60];
typedef struct{
	int dni;
	tString nombre;
	tString apellido;
	tString email;
	tString60 nombreCompleto;
	int codCategoria;
	float montoAbonado;
}tDatoInscripcion;

typedef struct nodo{
	tDatoInscripcion datos;
	struct nodo * siguiente;
}tPilaInscripcion;

/*Declaración de prototipo*/
void inicializarPila();
bool pilaVacia(tPilaInscripcion *);
void apilar(tDatoInscripcion);
void desapilar();
void mostrarParticipantes(tPilaInscripcion *);
void registrarParticipante();
void datosProfesionales();
float montoTotalRecaudado(tPilaInscripcion *);
float montoRecaudadoEstudiantes(tPilaInscripcion *);
tDatoInscripcion inscripcionCima (tPilaInscripcion *);
tPilaInscripcion * inscripcionCima2 (tPilaInscripcion *);
void menu();

/*Declaración de variables globales*/
tPilaInscripcion * pilaInscripcion;
tDatoInscripcion dataVacia;
int contadorTotalParticipantes = 0, contadorProfesionales = 0;
float acumuladorEstudiantes = 0.0;

/*Función principal*/
int main(){
	inicializarPila();
	dataVacia.dni = 0;
	strcpy(dataVacia.nombreCompleto, " ");
	strcpy(dataVacia.email, " ");
	dataVacia.codCategoria = 0;
	dataVacia.montoAbonado = 0.0;
	menu();
	return 0;
}

/*Implementación de funciones*/
void inicializarPila(){
	pilaInscripcion = NULL;
	printf("Pila de inscripciones inicializada...\n");
	system("pause");
	system("cls");
}

bool pilaVacia(tPilaInscripcion * pPilaInscripcion){
	return (pPilaInscripcion == NULL);
}

void registrarParticipante(){
	tDatoInscripcion dato;
	printf("Ingrese los siguientes datos del participante: \n");
	printf("DNI: ");
	scanf("%d", &dato.dni);
	printf("Apellido: ");
	fflush(stdin);
	gets(dato.apellido);	
	printf("Nombre: ");
	fflush(stdin);
	gets(dato.nombre);
	/*Concatenacion de apellido y nombre*/	
	strcpy(dato.nombreCompleto, dato.apellido);
	strcat(dato.nombreCompleto, ", ");
	strcat(dato.nombreCompleto, dato.nombre);
	printf("e-mail: ");
	fflush(stdin);
	gets(dato.email);
	printf("Categoria (1-Estudiante 2-Profesional 3-Publico en general): ");
	scanf("%d", &dato.codCategoria);
	printf("Monto a pagar ($200 estudiante y $350 profesional y publico general)\n");
	
	switch (dato.codCategoria){
	
		case 1:{
				printf("Monto abonado: ");
				scanf("%f", &dato.montoAbonado);
				if(dato.montoAbonado != 200){
					printf("Monto ingresado invalido. El participante debe abonar $200\n");
				}else{
					acumuladorEstudiantes = acumuladorEstudiantes + dato.montoAbonado;
					apilar(dato);	
				}
				break;
		}
		case 2:{
				printf("Monto abonado: ");
				scanf("%f", &dato.montoAbonado);
				contadorProfesionales = contadorProfesionales + 1;	
				if(dato.montoAbonado != 350){
					printf("Monto ingresado invalido. El participante debe abonar $350\n");
				}else{
					apilar(dato);	
				}		
				break;
		}
		case 3:{
				printf("Monto abonado: ");
				scanf("%f", &dato.montoAbonado);
				if(dato.montoAbonado != 350){
					printf("Monto ingresado invalido. El participante debe abonar $350\n");
				}else{
					apilar(dato);	
				}	
				break;
		}
	}
	contadorTotalParticipantes = contadorTotalParticipantes + 1;		
}

void apilar(tDatoInscripcion pDatoInscripcion){
	/* 1.Crear nodo nuevo*/
	tPilaInscripcion * nuevoNodo;
	/* 2. Reservar espacio en la memoria y asignarsela al puntero*/
	nuevoNodo = (tPilaInscripcion *) malloc (sizeof(tPilaInscripcion));
	/* 3. Asignarle el dato al campo*/
	nuevoNodo->datos = pDatoInscripcion;
	/* 4. Asignar valor al campo siguiente*/
	nuevoNodo->siguiente = pilaInscripcion;
	/* 5. Asginar el nuevo nodo a la pila*/
	pilaInscripcion = nuevoNodo;
	/* 6. Mostrar leyenda*/
	printf("Datos del participante registrado: \n\t-DNI: %d \n\t-Apellido y nombre: %s \n\t-email: %s\n\t-Codigo de categoria: %d \n\t-Monto abonado: $%.2f \n",
	pDatoInscripcion.dni, pDatoInscripcion.nombreCompleto, 
	pDatoInscripcion.email, pDatoInscripcion.codCategoria, pDatoInscripcion.montoAbonado);
}
void desapilar(){
	if(pilaVacia(pilaInscripcion)){
		printf("No hay participantes registrados para quitar\n");
	}else{
		/* 1. Guardar nodo a suprimir en una variable aux*/
		tPilaInscripcion * inscripcionSuprimir;
		/* 2. Asignarle el nodo auxiliar a la variable puntero*/
		inscripcionSuprimir = pilaInscripcion;
		/* 3. Pasar al nodo siguiente*/
		pilaInscripcion = pilaInscripcion->siguiente;
		/* 4. Mostrar leyenda*/
		printf("Datos del participante eliminado: \n\t-DNI: %d \n\t-Apellido y nombre: %s \n\t-email: %s\n\t-Codigo de categoria: %d \n\t-Monto abonado: %.2f \n",
		inscripcionSuprimir->datos.dni, inscripcionSuprimir->datos.nombreCompleto, inscripcionSuprimir->datos.email, 
		inscripcionSuprimir->datos.codCategoria, inscripcionSuprimir->datos.montoAbonado);
		/* 5. Liberar memoria*/
		free (inscripcionSuprimir);
		/* 6. Asignarle NULL*/
		inscripcionSuprimir = NULL;
	}
}

void mostrarParticipantes(tPilaInscripcion * pPilaInscripcion){
	if(pilaVacia(pPilaInscripcion)){
		printf("No hay participantes registrados para mostrar\n");
	}else{
		/* 1. Asignarle el parametro a la aux*/
		tPilaInscripcion * aux = pPilaInscripcion;
		/* 2. Mostrar*/
		printf("\t\t\t Datos de las personas registradas para el evento de informatica \n");
		printf("\t\t\t----------------------------------------------------------------------\n");
		printf("\t\t\t| DNI | APELLIDO Y NOMBRE | EMAIL\t | CATEGORIA | MONTO ABONADO |\n");
		printf("\t\t\t----------------------------------------------------------------------\n");	
		while (aux != NULL){
			printf("\t\t\t%d | %s, %s | %s | %d | %.2f \n", 
			aux->datos.dni, aux->datos.apellido, aux->datos.nombre, aux->datos.email, 
			aux->datos.codCategoria, aux->datos.montoAbonado);
			/* 3. Pasar al siguiente nodo*/
			aux = aux->siguiente;
		}
	}
}

tPilaInscripcion * inscripcionCima2 (tPilaInscripcion * pPilaInscripcion){
	return pilaVacia(pPilaInscripcion) == true ? NULL : pPilaInscripcion;
}

void datosProfesionales(){
	/*Cantidad de profesionales*/
	printf("Cantidad de profesionales inscriptos: %d\n", contadorProfesionales);
	/*Porcentaje de profesionales sobre el total de participantes*/
	float porcentaje = 0.0;
	porcentaje = ( contadorProfesionales * 100 ) / contadorTotalParticipantes; 
	printf("El porcentaje de cantidadd de profesionales sobre el total de inscriptos es: %.2f\n", porcentaje);
}


float montoTotalRecaudado(tPilaInscripcion * pPilaInscripciones){
	tPilaInscripcion * aux;
	float acumTotalRecaudado = 0.0;
	aux = pPilaInscripciones;
	if (!pilaVacia(pPilaInscripciones)){
		while(aux != NULL){
			acumTotalRecaudado = acumTotalRecaudado + aux->datos.montoAbonado;
			aux = aux->siguiente;
		}
	}
	return acumTotalRecaudado;
}


void menu(){
	int opcion;
		do{
			printf("\t\t\t---------------------------------------------------------\n");
			printf("\t\t\t|\t\t\tM E N U\t\t\t\t|\n");
			printf("\t\t\t---------------------------------------------------------\n");
			printf("\t\t\t|\t1. Registrar participante\t\t\t|\n");
			printf("\t\t\t|\t2. Eliminar participante\t\t\t|\n");	
			printf("\t\t\t|\t3. Mostrar participantes\t\t\t|\n");
			printf("\t\t\t|\t4. Mostrar cantidad de profesionales inscriptos |\n");
			printf("\t\t\t|\t5. Mostrar monto recaudado por Estudiantes \t|\n");
			printf("\t\t\t|\t6. Mostrar monto total recaudado\t\t|\n");	
			printf("\t\t\t|\t7. Mostrar participante en cima\t\t\t|\n");				
			printf("\t\t\t|\t0. Salir\t\t\t\t\t|\n");
			printf("\t\t\t---------------------------------------------------------\n");
			printf("\n\t\t\tSeleccione una opcion del menu:");
			scanf("%d", &opcion);
			system("cls");
			switch (opcion){
				case 0: 
						printf("Programa finalizado!\n");
						break;
						
				case 1:
						registrarParticipante();
						break;
				case 2:	
						desapilar();
						break;
						
				case 3: 
						mostrarParticipantes(pilaInscripcion);
						break;
						
				case 4:	
						datosProfesionales();
						break;
						
				case 5:	
						printf("Monto recaudado en la categoria de estudiantes: $%.2f\n", acumuladorEstudiantes);
						break;
						
				case 6: { 
						if(pilaVacia(pilaInscripcion)){
							printf("No hay participantes registrados\n");
						}else{
							printf("Monto total recaudado: $%.2f \n", montoTotalRecaudado(pilaInscripcion));
						}
						break;
						
				}
				case 7:{
						printf ("El participante que se encuentra en la cima es : %d - %s \n", inscripcionCima2(pilaInscripcion)->datos.dni,
						inscripcionCima2(pilaInscripcion)->datos.nombreCompleto );
						break;
				}
				default: 
						printf("Opcion ingresada incorrecta\n");
						 break;
			}
			system("pause");
			system("cls");
		}while(opcion != 0);
}

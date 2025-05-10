#include "LIST.h"
#include "TRANSICIONES.h"
#include "TAD_SET.h"
#include <stdio.h>
#include <stdlib.h>

/* Funci�n para agregar un nuevo nodo de transici�n a la lista de transiciones */
void CargaLista(Transiciones *head, Transiciones new_node) {
	Transiciones temp;
	// Si la lista est� vac�a, el nuevo nodo se convierte en el primer elemento
	if(*head == NULL) 
		*head = new_node;
	else {
		// Si la lista no est� vac�a, recorremos hasta el �ltimo nodo
		temp = *head;
		while(temp->sig != NULL) 
			temp = temp->sig;
		// Enlazamos el nuevo nodo al final de la lista
		temp->sig = new_node;
	}
}

/* Funci�n para crear un nuevo nodo de transici�n */
Transiciones CreaNodoTransicion() {
	Transiciones Nodo;
	// Asignamos memoria para el nodo
	Nodo = (Transiciones)malloc(sizeof(Delta));
	// Inicializamos el siguiente puntero como NULL, ya que es el �ltimo nodo de la lista
	Nodo->sig = NULL;
	return Nodo;
}

/* Funci�n para cargar las transiciones del aut�mata desde la entrada del usuario */
Transiciones CargaListaTransiciones(LIST Estados, LIST alfabeto) {
	Transiciones nvo = NULL, nodo = NULL;
	int opc;
	// Preguntamos si se quiere cargar transiciones
	printf("\nCargar transiciones? 1:si 2:no :");
	scanf("%d", &opc);
	
	// Continuamos cargando transiciones mientras el usuario lo indique
	while(opc != 2) {
		// Creamos un nuevo nodo de transici�n
		nodo = CreaNodoTransicion();
		fflush(stdin); // Limpiamos el buffer de entrada
		
		// Leemos el estado de origen
		printf("\nEstado de origen: ");
		nodo->dato.Estado_Origen = load(); // Funci�n load() debe devolver un conjunto de estados
		
		fflush(stdin); // Limpiamos el buffer de entrada
		
		// Leemos la etiqueta de la transici�n
		printf("\nEtiqueta: ");
		scanf("%c", &nodo->dato.Etiqueta); // Leemos un car�cter
		
		fflush(stdin); // Limpiamos el buffer de entrada
		
		// Leemos el estado de destino
		printf("\nEstado destino: ");
		nodo->dato.Estado_Destino = create_set(); // Creamos un nuevo conjunto de estados
		CargaLista(&nvo, nodo); // A�adimos la transici�n a la lista
		
		// Preguntamos si se quiere agregar otra transici�n
		printf("\nCargar transiciones? 1:si 2:no :");
		scanf("%d", &opc);
	}
	
	return nvo; // Devolvemos la lista de transiciones cargadas
}

/* Funci�n para mostrar todas las transiciones del aut�mata */
void mostrar_lista_transiciones(Transiciones t) {
	// Recorremos toda la lista de transiciones
	while (t != NULL) {
		printf("d(");
		print(t->dato.Estado_Origen); // Mostramos el estado de origen
		printf(", ");
		printf("%c", t->dato.Etiqueta); // Mostramos la etiqueta de la transici�n
		printf(") = ");
		show_set(t->dato.Estado_Destino); // Mostramos el estado de destino
		printf("\n");
		// Avanzamos al siguiente nodo de la lista
		t = t->sig;
	}
}

/* Funci�n para realizar una transici�n en el aut�mata dada una entrada (car�cter) */
SET transicion(SET a, Transiciones b, char c) {
	SET ab = NULL;  // Variable para almacenar los resultados de las transiciones
	SET aux;
	
	// Recorremos todas las transiciones
	while (b != NULL) {
		aux = a;  // Iniciamos el recorrido de los estados actuales
		
		// Recorremos los estados actuales
		while (aux != NULL) {
			// Si el estado de origen coincide con el estado actual y la etiqueta coincide con la entrada
			if (string_equal(aux->date, b->dato.Estado_Origen) && c == b->dato.Etiqueta) {
				// Realizamos la transici�n a�adiendo los estados de destino al conjunto resultante
				ab = union_set(ab, clone_set(b->dato.Estado_Destino));
			}
			aux = aux->next; // Avanzamos al siguiente estado
		}
		
		b = b->sig; // Avanzamos al siguiente nodo de transici�n
	}
	
	return ab; // Devolvemos el conjunto de estados resultante despu�s de las transiciones
}

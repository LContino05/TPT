#include "LIST.h"
#include "TRANSICIONES.h"
#include "TAD_SET.h"
#include <stdio.h>
#include <stdlib.h>

/* Función para agregar un nuevo nodo de transición a la lista de transiciones */
void CargaLista(Transiciones *head, Transiciones new_node) {
	Transiciones temp;
	// Si la lista está vacía, el nuevo nodo se convierte en el primer elemento
	if(*head == NULL) 
		*head = new_node;
	else {
		// Si la lista no está vacía, recorremos hasta el último nodo
		temp = *head;
		while(temp->sig != NULL) 
			temp = temp->sig;
		// Enlazamos el nuevo nodo al final de la lista
		temp->sig = new_node;
	}
}

/* Función para crear un nuevo nodo de transición */
Transiciones CreaNodoTransicion() {
	Transiciones Nodo;
	// Asignamos memoria para el nodo
	Nodo = (Transiciones)malloc(sizeof(Delta));
	// Inicializamos el siguiente puntero como NULL, ya que es el último nodo de la lista
	Nodo->sig = NULL;
	return Nodo;
}

/* Función para cargar las transiciones del autómata desde la entrada del usuario */
Transiciones CargaListaTransiciones(LIST Estados, LIST alfabeto) {
	Transiciones nvo = NULL, nodo = NULL;
	int opc; char C;
	// Preguntamos si se quiere cargar transiciones
	printf("\nCargar transiciones? 1:si 2:no :");
	scanf("%d", &opc);
	
	// Continuamos cargando transiciones mientras el usuario lo indique
	while(opc != 2) {
		// Creamos un nuevo nodo de transición
		nodo = CreaNodoTransicion();
		fflush(stdin); // Limpiamos el buffer de entrada
		
		// Leemos el estado de origen
		printf("\nEstado de origen: ");
		nodo->dato.Estado_Origen = load(); // Función load() debe devolver un conjunto de estados
		
		fflush(stdin); // Limpiamos el buffer de entrada
		
		// Leemos la etiqueta de la transición
		do{
			printf("\nEtiqueta: ");
			scanf("%c", &C);
		}while(get_char(alfabeto->date)==C); // Leemos un carácter
		nodo->dato.Etiqueta = C;
		fflush(stdin); // Limpiamos el buffer de entrada
		
		// Leemos el estado de destino
		printf("\nEstado destino: ");
		nodo->dato.Estado_Destino = create_set(); // Creamos un nuevo conjunto de estados
		CargaLista(&nvo, nodo); // Añadimos la transición a la lista
		
		// Preguntamos si se quiere agregar otra transición
		printf("\nCargar transiciones? 1:si 2:no :");
		scanf("%d", &opc);
	}
	
	return nvo; // Devolvemos la lista de transiciones cargadas
}

/* Función para mostrar todas las transiciones del autómata */
void mostrar_lista_transiciones(Transiciones t) {
	// Recorremos toda la lista de transiciones
	while (t != NULL) {
		printf("d(");
		print(t->dato.Estado_Origen); // Mostramos el estado de origen
		printf(", ");
		printf("%c", t->dato.Etiqueta); // Mostramos la etiqueta de la transición
		printf(") = ");
		show_set(t->dato.Estado_Destino); // Mostramos el estado de destino
		printf("\n");
		// Avanzamos al siguiente nodo de la lista
		t = t->sig;
	}
}

/* Función para realizar una transición en el autómata dada una entrada (carácter) */
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
				// Realizamos la transición añadiendo los estados de destino al conjunto resultante
				ab = union_set(ab, clone_set(b->dato.Estado_Destino));
			}
			aux = aux->next; // Avanzamos al siguiente estado
		}
		
		b = b->sig; // Avanzamos al siguiente nodo de transición
	}
	
	return ab; // Devolvemos el conjunto de estados resultante después de las transiciones
}

int validar_transiciones(SET Q,Transiciones lista){
	int b;
	Transiciones aux;
	aux=lista;
	b=0;
	while(aux!=NULL){/revisa toda la lista/
		if(!is_element_in_set(Q,aux->dato.Estado_Origen)){/* verifica que el estado de origen este en Q */
			printf("\n ERROR");
			print(aux->dato.Estado_Origen);/lo muesta si no esta/
			printf("\n NO PERTENECE A Q");
			b=1;
		}
		if(!is_sub_set(aux->dato.Estado_Destino,Q)){/verifica que el estado destino este en Q/
			printf("\n ERROR");
			print(aux->dato.Estado_Destino);/lo muesta si no esta/
			printf("\ NO PERTENECE A Q");
			b=1;
		}
		aux=aux->sig;
	}
	return b;
}

int validar_etiquetas(SET alf,Transiciones lista){
	Transiciones aux;
	int b;
	STR sim;
	aux=lista;
	b=0;
	while (aux!=NULL){
		sim=create_node(aux->dato.Etiqueta);
		if(!is_element_in_set(alf,sim)){
			printf("\n ERROR LA ETIQUTA NO PERTENECE AL ALFABETO");
			b=1;
		}
		aux=aux->sig;
	}
	return b;
}

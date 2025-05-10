#include "AUTOMATA.h"
#include "TRANSICIONES.h"
#include "STR.h"
#include <stdio.h>

/* Funci�n para cargar cada parte del aut�mata en orden seg�n el par�metro opc. 
Esto configura los estados, alfabeto, estado inicial y estados de aceptaci�n del aut�mata. */
void CargaAutomata2(int opc, SET date, TAutomata *nvo) {
	switch(opc) {
	case 0: nvo->Estados = date; break; // Cargar los estados
	case 1: nvo->Alfabeto = date; break; // Cargar el alfabeto
	case 2: nvo->Estado_Inicial = date; break; // Cargar el estado inicial
	case 3: nvo->Estados_Aceptacion = date; break; // Cargar los estados de aceptaci�n
	}
}

/* Funci�n para cargar el aut�mata a partir de una cadena (STR A). 
Se descompone la cadena e inserta las transiciones y los diferentes conjuntos en el aut�mata. */
TAutomata CargaAutomataconCadena(STR A) {
	TAutomata nvo;
	Transiciones nvo_transicion = NULL, nodo_transicion;
	STR aux = A, nvo_str = NULL, nodo, aux2, estado1 = NULL, estado2 = NULL;
	SET date, estado_final;
	int b = 0;
	char caracter, etiqueta;
	
	while (aux != NULL) {
		caracter = get_char(aux);
		
		if (caracter == '{') {  // Se detecta una transici�n (bloque de transiciones)
			aux2 = aux->next;  // Avanzar al siguiente car�cter (omitimos el '{')
			
			// Leer el estado de origen de la transici�n
			while (aux2 != NULL && (caracter = get_char(aux2)) != ',') {
				nodo = create_node(caracter); // Crear nodo para el estado
				enqueue(&estado1, nodo);  // Encolar el nodo al conjunto de estados de origen
				aux2 = aux2->next;
			}
			
			aux2 = aux2->next;
			etiqueta = get_char(aux2); // Leer la etiqueta de la transici�n
			
			aux2 = aux2->next;
			// Leer el estado de destino de la transici�n
			while (aux2 != NULL && (caracter = get_char(aux2)) != '}') {
				nodo = create_node(caracter);  // Crear nodo para el estado de destino
				enqueue(&estado2, nodo);  // Encolar el nodo al conjunto de estados de destino
				aux2 = aux2->next;
			}
			
			estado_final = str_to_set(estado2, ',');  // Convertir la lista de estados de destino a un conjunto
			
			// Crear la transici�n
			nodo_transicion = CreaNodoTransicion();
			nodo_transicion->dato.Estado_Origen = estado1;  // Asignar el estado de origen
			nodo_transicion->dato.Etiqueta = etiqueta;     // Asignar la etiqueta
			nodo_transicion->dato.Estado_Destino = estado_final;  // Asignar el estado de destino
			
			CargaLista(&nvo_transicion, nodo_transicion);  // Insertar la transici�n en la lista de transiciones
			
			estado1 = NULL;
			free_str(estado2);  // Liberar memoria del estado2 (ya que es una lista)
			estado2 = NULL;
			
			aux = aux2;  // Avanzar hasta el final del bloque de transici�n
		}
		else if (caracter != '*') {
			nodo = create_node(caracter);  // Crear nodo para los elementos fuera de las transiciones
			enqueue(&nvo_str, nodo);  // Encolar al conjunto correspondiente
		}
		else {
			date = str_to_set(nvo_str, ',');  // Convertir la lista de nodos a un conjunto
			CargaAutomata2(b, date, &nvo);  // Cargar la parte correspondiente del aut�mata
			
			free_str(nvo_str);  // Liberar memoria de la lista nvo_str
			nvo_str = NULL;
			
			date = NULL;  // Liberar el conjunto de elementos
			b++;  // Incrementar el contador para la siguiente parte del aut�mata
		}
		
		aux = aux->next;  // Avanzar al siguiente car�cter
	}
	
	nvo.Transiciones = nvo_transicion;  // Asignar las transiciones al aut�mata
	return nvo;  // Retornar el aut�mata cargado
}

/* Funci�n que verifica si el aut�mata es determinista o no determinista. 
Devuelve 0 si es no determinista, 1 si es determinista. */
int Tipo_de_Automata(Transiciones L) {
	Transiciones aux1, aux2;
	aux1 = L;
	
	// Recorrer la lista de transiciones
	while (aux1 != NULL) {
		aux2 = aux1->sig;  // Comparar con el resto de transiciones
		
		while (aux2 != NULL) {
			// Si se encuentra una transici�n con el mismo estado de origen y misma etiqueta
			if (string_equal(aux1->dato.Estado_Origen, aux2->dato.Estado_Origen) && 
				aux1->dato.Etiqueta == aux2->dato.Etiqueta) {
				return 0;  // El aut�mata es no determinista
			}
			else {
				// Si el estado de destino tiene m�s de un elemento (lo que indica no determinismo)
				if (Cantidad_Elementos(aux1->dato.Estado_Destino) > 1 || 
					Cantidad_Elementos(aux2->dato.Estado_Destino) > 1) {
					return 0;  // El aut�mata es no determinista
				}
			}
			
			aux2 = aux2->sig;  // Avanzar al siguiente nodo de la lista de transiciones
		}
		
		aux1 = aux1->sig;  // Avanzar al siguiente nodo de la lista de transiciones
	}
	
	return 1;  // El aut�mata es determinista
}

/* Funci�n para cargar un aut�mata vac�o. 
Permite ingresar los estados, alfabeto, estado inicial, estados de aceptaci�n y transiciones. */
TAutomata CargaAutomata() {
	TAutomata nvo;
	
	// Cargar los estados
	printf("\nEstados");
	nvo.Estados = create_set();
	
	// Cargar el alfabeto
	printf("\nAlfabeto");
	nvo.Alfabeto = create_set();
	
	// Cargar los estados de aceptaci�n
	printf("\nEstados de aceptacion: ");
	nvo.Estados_Aceptacion = create_set();
	
	// Cargar el estado inicial
	printf("\nEstado Inicial:");
	nvo.Estado_Inicial = create_set();
	
	// Cargar las transiciones
	printf("\nTransiciones: ");
	nvo.Transiciones = CargaListaTransiciones(nvo.Estados, nvo.Alfabeto);
	
	return nvo;  // Retornar el aut�mata cargado
}

/* Funci�n para mostrar el aut�mata cargado, mostrando todos sus componentes. */
void MostrarAutomata(TAutomata a) {
	printf("\n=============================\n");
	printf("AUTOMATA CARGADO\n");
	printf("=============================\n");
	
	// Mostrar los estados
	printf("Q (Estados): ");
	show_set(a.Estados);
	
	// Mostrar el alfabeto
	printf("\nS (Alfabeto): ");
	show_set(a.Alfabeto);
	
	// Mostrar el estado inicial
	printf("\nq0 (Estado inicial): ");
	show_set(a.Estado_Inicial);
	
	// Mostrar los estados de aceptaci�n
	printf("\nF (Estados de aceptacion): ");
	show_set(a.Estados_Aceptacion);
	
	// Mostrar las transiciones
	printf("\nd (Transiciones):\n");
	mostrar_lista_transiciones(a.Transiciones);
	
	printf("=============================\n");
}

/* Funci�n para verificar si una cadena pertenece a la lista. */
int pertenece_a_lista(LIST l, STR objetivo) {
	while (l != NULL) {
		if (string_equal(l->date, objetivo)) {
			return 1;  // La cadena pertenece a la lista
		}
		l = l->next;
	}
	return 0;  // La cadena no pertenece a la lista
}

/* Funci�n para leer una cadena y verificar si es aceptada por el aut�mata. */
int LeerCadena(STR Cadena, TAutomata A) {
	STR aux;
	SET state, rta = NULL;
	aux = Cadena;
	state = A.Estado_Inicial;
	
	// Recorrer la cadena y hacer las transiciones en el aut�mata
	while (aux != NULL) {
		state = transicion(state, A.Transiciones, aux->date);
		aux = aux->next;
	}
	
	// Verificar si el aut�mata termina en un estado de aceptaci�n
	rta = intersection_set(A.Estados_Aceptacion, state);
	show_set(rta);
	
	// Retornar 1 si es aceptada, 0 si no es aceptada
	if (rta == NULL) {
		return 0;  // No aceptada
	}
	else {
		return 1;  // Aceptada
	}
}


#ifndef TRANSICIONES_H
#define TRANSICIONES_H
#include "STR.h"
#include "LIST.h"
#include "tad_set.h"

typedef struct{
	STR Estado_Origen;
	SET Estado_Destino;
	char Etiqueta;
}TTransicion;


typedef struct nodo3{
	TTransicion dato;
	struct nodo3 *sig;
}Delta;

typedef Delta* Transiciones;

void CargaLista(Transiciones *head, Transiciones new_node);
Transiciones CreaNodoTransicion();
Transiciones CargaListaTransiciones();
void mostrar_lista_transiciones(Transiciones t);
SET transicion(SET a,Transiciones b,char c);

#endif

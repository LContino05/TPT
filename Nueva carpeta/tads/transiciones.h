#ifndef TRANSICIONES_H
#define TRANSICIONES_H
#include "STR.h"
#include "LIST.h"

typedef struct{
	STR Estado_Origen, Estado_Destino;
	char Etiqueta;
}TTransicion;


typedef struct nodo3{
	TTransicion dato;
	struct nodo3 *sig;
}Delta;

typedef Delta* Transiciones;

Transiciones CargaListaTransiciones(LIST, LIST);
Transiciones CargaListaTransicionesND(LIST, LIST);
void mostrar_lista_transiciones(Transiciones t);
STR transicion(STR Estado, char caracter, Transiciones delta);
#endif

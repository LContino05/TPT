#ifndef AUTOMATA_H
#define AUTOMATA_H
#include "TRANSICIONES.h"

typedef struct{
	LIST Estados,Estados_Aceptacion,Alfabeto;
	STR Estado_Inicial;
	Transiciones Transiciones;
}TAutomata;

TAutomata CargaAutomata();
void MostrarAutomata(TAutomata a);
int LeerCadena(STR Cadena, TAutomata A);
#endif

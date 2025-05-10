#ifndef AUTOMATA_H
#define AUTOMATA_H
#include "TRANSICIONES.h"

typedef struct{
	SET Estado_Inicial,Estados_Aceptacion,Estados,Alfabeto;
	Transiciones Transiciones;
}TAutomata;


int Tipo_de_Automata(Transiciones L);
TAutomata CargaAutomataconCadena(STR A);
TAutomata CargaAutomata();
void MostrarAutomata(TAutomata a);
int LeerCadena(STR Cadena, TAutomata A);
#endif

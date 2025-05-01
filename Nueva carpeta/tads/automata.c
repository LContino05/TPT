#include "AUTOMATA.h"
#include <stdio.h>

int DetOrnoDet(){
	int opc;
	do{
		printf("El automata es...");
		printf("[0]Determinista || [1]No determinista");
	}while(opc==1 || opc==0);
	return opc;
}

TAutomata CargaAutomata(){
	TAutomata nvo;
	int Op;
	Op=DetOrnoDet();
	
	printf("\nEstados");
	nvo.Estados=load_list();
	
	printf("\nAlfabeto");
	nvo.Alfabeto=load_list();
	
	printf("\nEstados de aceptacion: ");
	nvo.Estados_Aceptacion=load_list();
	
	printf("\nEstado Inicial:");
	nvo.Estado_Inicial=load();
	
	printf("\nTransiciones: ");
	if(Op==0)
		nvo.Transiciones=CargaListaTransiciones(nvo.Estados, nvo.Alfabeto);
	else
		nvo.Transiciones=CargaListaTransicionesND(nvo.Estados, nvo.Alfabeto);
	
	return nvo;
	
}

void MostrarAutomata(TAutomata a) {
	printf("\n=============================\n");
	printf("AUTOMATA CARGADO\n");
	printf("=============================\n");
		
	printf("Q (Estados): ");
	print_list(a.Estados);
		
		printf("\nS (Alfabeto): ");
		print_list(a.Alfabeto);
		
		printf("\nq0 (Estado inicial): ");
		print(a.Estado_Inicial);
		
		printf("\nF (Estados de aceptación): ");
		print_list(a.Estados_Aceptacion);
		
		printf("\nd (Transiciones):\n");
		mostrar_lista_transiciones(a.Transiciones);
		
		printf("=============================\n");
	}



int pertenece_a_lista(LIST l, STR objetivo) {
	while (l != NULL) {
		if (string_equal(l->date, objetivo)) {
			return 1;
		}
		l = l->next;
	}
	return 0;
}

int LeerCadena(STR Cadena, TAutomata A){
	STR aux, state;
	aux=Cadena; state = A.Estado_Inicial;
	
	while(aux!=NULL){
		state=transicion(state, aux->date, A.Transiciones);
		aux=aux->next;
	}
	if(pertenece_a_lista(A.Estados_Aceptacion, state)==1){
		return 1;
	}
	else return 0;
}

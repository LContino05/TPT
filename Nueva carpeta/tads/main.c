#include <stdio.h>
#include "automata.h"
#include "str.h"
int main(){
	const char *tcad="q0,q1*0,1*q0*q1*{q0,0,q0}{q0,1,q1}{q1,0,q0}{q1,1,q1}";
    
	int rta, op;
	STR cadena, A;
    TAutomata L,Nvo;
	
	L=CargaAutomata();
	MostrarAutomata(L);
	
	do{ printf("\nCargando cadena....\n");
	fflush(stdin);
	cadena=load();
	rta=LeerCadena(cadena, L);
	if(rta==1){
		printf("\nLa cadena es aceptada");
	}
	else printf("\nLa cadena no es aceptada");
	
	rta=Tipo_de_Automata(L.Transiciones);
	if(rta==1){
		printf("\nEl automata es Determinista");
	}
	else printf("\nEl automata es No Determinista");
	
	
	A=Load2(tcad);
	print(A);
	Nvo=CargaAutomataconCadena(A);
	MostrarAutomata(Nvo);
	printf("\nCargando cadena....\n");
	fflush(stdin);
	cadena=load();
	rta=LeerCadena(cadena, Nvo);
	if(rta==1){
		printf("\nLa cadena es aceptada");
	}
	else printf("\nLa cadena no es aceptada");
	rta=Tipo_de_Automata(Nvo.Transiciones);
	if(rta==1){
		printf("\nEl automata es Determinista");
	}
	else printf("\nEl automata es No Determinista");
	printf("Evaluar otra cadena? [1]Si || [0]No");
	scanf("%d",&op);
	  }while(op==0);
	return 0;
}

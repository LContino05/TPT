#include "LIST.h"
#include "TRANSICIONES.h"
#include <stdio.h>
#include <stdlib.h>


void CargaLista(Transiciones *head, Transiciones new_node) {
	Transiciones temp;
	if(*head==NULL) *head=new_node;
	else {
		temp=*head;
		while(temp->sig!=NULL) temp=temp->sig;
		temp->sig=new_node;
	}
}

Transiciones CreaNodo(){
	Transiciones Nodo;
	Nodo=(Transiciones)malloc(sizeof(Delta));
	Nodo->sig=NULL;
    return Nodo;
}
Transiciones CargaListaTransiciones(LIST Estados, LIST alfabeto){
	Transiciones nvo=NULL, nodo=NULL;
	int opc;
	printf("\nCargar transiciones? 1:si 2:no :");scanf("%d", &opc);
	while(opc!=2){
		nodo=CreaNodo();
		fflush(stdin);
		printf("\nEstado de origen: ");
		nodo->dato.Estado_Origen=load();
		fflush(stdin);
		printf("\nEtiqueta: ");
		scanf("%c", &nodo->dato.Etiqueta);
		fflush(stdin);
		printf("\nEstado destino: ");
		nodo->dato.Estado_Destino=load();
		CargaLista(&nvo, nodo);
		printf("\nCargar transiciones? 1:si 2:no :");scanf("%d", &opc);
	}
	return nvo;
	
	
}
	
void mostrar_lista_transiciones(Transiciones t) {
		while (t != NULL) {
			printf("d(");
			print(t->dato.Estado_Origen);
			printf(", ");
			printf("%c",t->dato.Etiqueta);
			printf(") = ");
			print(t->dato.Estado_Destino);
			printf("\n");
			
			t = t->sig;
		}
	}

STR transicion(STR Estado, char caracter, Transiciones delta){
	Transiciones aux=delta;
	while(aux!=NULL){
		if((string_equal(Estado, aux->dato.Estado_Origen)==1) && (caracter == aux->dato.Etiqueta)){
		  return aux->dato.Estado_Destino;
		}
		else{
			aux=aux->sig;
		}
	}
	return NULL;
}

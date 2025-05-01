#include "LIST.h"
#include "TRANSICIONES.h"
#include <stdio.h>
#include <stdlib.h>

int verif_alf(LIST ALFA, char Caract){
	LIST aux=ALFA;
	while(aux!=NULL){
		if(string_equal(aux.date, Caract)!=1)
			aux=aux->sig;
	}
	if(aux!=NULL)
		return 0;
	else
		return 1;
}

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

void carga_AND(LIST LisEst){
	LIST aux;
}

Transiciones CargaListaTransicionesND(LIST Estados, LIST alfabeto){
	Transiciones nvo=NULL, nodo=NULL;
	LIST tsc=inicializate_list();
	int opc;
	printf("\nCargar transiciones? 1:si 2:no :");scanf("%d", &opc);
	while(opc!=2){
		nodo=CreaNodo();
		fflush(stdin);
		printf("\nEstado de origen: ");
		nodo->dato.Estado_Origen=load();
		fflush(stdin);
		do{
			printf("\nEtiqueta: ");
			scanf("%c", &nodo->dato.Etiqueta);
			fflush(stdin);
		}while(verif_alf(alfabeto, nodo->dato.Etiqueta)==1);
		nodo->dato.Estado_Destino=carga_AND(tsc);
		CargaLista(&nvo, nodo);
		printf("\nCargar transiciones? 1:si 2:no :");scanf("%d", &opc);
	}
	return nvo;
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
		do{
			printf("\nEtiqueta: ");
			scanf("%c", &nodo->dato.Etiqueta);
			fflush(stdin);
		}while(verif_alf(alfabeto, nodo->dato.Etiqueta)==1);
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

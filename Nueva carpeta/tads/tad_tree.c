#include "tad_tree.h"
#include <stdlib.h>
#include <stdio.h>
#define str 1
#define set 2
#define list 3

tData createSTRNode(STR string){
    tData nvo;
    nvo=(tData)malloc(sizeof(dataType));
    nvo->nodeType=str;
    nvo->strData=string;
    return nvo;
}

tData createTREEWithData(int DATATYPE, tData Dato){
    tData nodo,nvo;
    nodo=(tData)malloc(sizeof(dataType));
    nodo->nodeType=DATATYPE;
    nodo->data=Dato;
    nodo->next=NULL;
    return nodo;
} 

tData CargaLista(){
    tData nodo;
    STR phrase;
    int opc;
    printf("Que quiere cargar?: (1)= cadena-- (2)= Conjunto -- (3)=lista");
    scanf("%d", &opc);
    if(opc == 1){
      fflush(stdin);
       phrase=load();
       nodo=createTREEWithData(opc, createSTRNode(phrase));
    }
    else if(opc==2){
       nodo=createTREEWithData(opc, CargaLista());
    }else if(opc==3){
      nodo=createTREEWithData(opc, CargaLista());
    }
    fflush(stdin);
    printf("\nQuiere cargar mas datos?: 1:si  2:no:  ");
    scanf("%d", &opc);
    if(opc==1){
      nodo->next=CargaLista();
    }
    else{
        nodo->next=NULL;
    }
    return nodo;
}


void Mostrar(tData L){
  printf("{");
  if(L!=NULL){
   if(L->nodeType==str){
     print(L->data->strData);
   }
   else{
    Mostrar(L->data);
   }
   
   Mostrar(L->next);
  }
  printf("}");
}

tData unionConjuntos(tData a, tData b) {
  tData resultado = NULL;
  while (a != NULL) {
      if (a->nodeType == set || a->data->nodeType == str || a->data->nodeType==list)
          resultado = agregarAConjunto(resultado, a->data->strData);
      a = a->next;
  }
  while (b != NULL) {
      if (b->nodeType == set || b->data->nodeType == str || b->data->nodeType== list)
          resultado = agregarAConjunto(resultado, b->data->strData);
      b = b->next;
  }
  return resultado;
}

tData interseccionConjuntos(tData a, tData b) {
  tData resultado = NULL;

  while (a != NULL) {
      if (a->nodeType == set && a->data->nodeType == str && perteneceAConjunto(b, a->data->strData)) {
          resultado = agregarAConjunto(resultado, a->data->strData);
      }
      a = a->next;
  }

  return resultado;
}




int Pertenece(tData a, tData busq){
   int b, rta=0;
   tData aux1=a, aux2=NULL;
   while (aux1!=NULL)
   {
    aux2=busq;
    b=1;
    while(aux2!=busq && b==1){
      if(aux2->data->nodeType == aux1->data->nodeType){
        if(aux2->data->nodeType==str){
          if(string_equal(aux2->data->strData, aux1->data->strData)){
             b=0;
             rta=1;
          }
        }
        else if(Pertenece(aux2->data, aux1->data)==1){
           b=0;
           rta=1;
        }
      }
      aux2=aux2->next;
    }
    aux1=aux1->next;
   }
   return rta;
}

void Eliminar(tData *L){
  int rta;
  tData busq, ant=NULL, aux;
  printf("\nCargando conjunto a buscar....\n");
  busq=createTREEWithData(3, CargaLista());
  aux=*L;
  while(aux!=NULL){
    if(aux->nodeType==set){
        rta = Pertenece(aux, busq);
        if(rta==1){
          if(aux==NULL){
            *L=aux->next;
          }
          else{
            ant->next=aux->next;
          }
        }
    }
    aux=aux->next;
  }
}

int inclusion(tData A, tData B) {
  tData auxA, auxB;
  int rdo = 0;

  if (A != NULL && B != NULL) {
      if (A->data->nodeType == set) {
          auxA = A;
          auxB = B;

          while (auxB != NULL && rdo == 0) {
              if (Pertenece(auxA, auxB->data) != 1) {
                  rdo = 1; 
              }
              auxB = auxB->next;
          }
      }
  }

  return rdo; 
}


#ifndef TAD_TREE_H
#define TAD_TREE_H

#include "tad_string.h"

#define str 1
#define set 2
#define list 3

// Declaración anticipada para usar en la unión

typedef struct dataType {
    int nodeType; // Tipo de nodo: STR, SET, LIST
    union {
        STR strData; // Si nodeType == STR

        struct {
            struct dataType* data; // Contenido (otro tData)
            struct dataType* next; // Siguiente nodo en la lista
        };
    };
} dataType;

typedef dataType* tData;

tData CargaLista();
void Mostrar(tData);
tData unionConjuntos(tData, tData);
tData interseccionConjuntos(tData , tData );
void Eliminar(tData *);
#endif
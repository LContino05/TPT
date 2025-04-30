#ifndef TAD_LIST_H
#define TAD_LIST_H
#include "tad_string.h"

/*Mathematic models*/

typedef struct nodo1 {
	STR date;
	struct nodo1* next;
}T_LIST_NODE;

typedef T_LIST_NODE* LIST;

/*Mathematic models*/

/*Operations*/

LIST inicializate_list();
LIST load_list();
LIST load_list2(const LIST);
void print_list(LIST);
STR list_to_str(LIST);
LIST str_to_list(STR);

/*Operations*/

#endif

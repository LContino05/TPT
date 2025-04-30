#ifndef TAD_SET_H
#define TAD_SET_H
#include "tad_string.h"

/*Mathematic model*/

typedef struct node2 {
    STR date;
    struct node2* next;
}T_SET_NODE;

typedef T_SET_NODE* SET;

/*Mathematic model*/

/*Operations*/

SET create_set();
void add_element_to_set(SET *, STR); /*SET es por referencia, internamente*/
void show_set(SET);
SET str_to_set(STR, char);
SET union_set(SET, SET);
SET intersection_set(SET, SET);
SET difference_set(SET, SET);
int is_element_in_set(SET, STR);
int is_sub_set(SET, SET);

/*Operations*/

#endif
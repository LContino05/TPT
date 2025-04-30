#ifndef TAD_STRING_H
#define TAD_STRING_H

/*Mathematic models*/

typedef struct nodo0 {
	char date;
	struct nodo0* next;
}T_STR_NODE;

typedef T_STR_NODE* STR;

/*Mathematic models*/

/*Operations*/

STR inicializate();
STR create_node(char);
void enqueue(STR *, STR);
STR load();
STR load2(const STR);
void print(STR);
STR concat(STR, STR);
STR before_token(STR, char);
int string_equal(STR, STR);
char get_char(STR);

/*Operations*/

#endif

#ifndef STR_H
#define STR_H

typedef struct nodo0 {
	char date;
	struct nodo0* next;
}T_STR_NODE;

typedef T_STR_NODE* STR;

/*Mathematic models*/

/*Operations*/
void free_str(STR s);
STR inicializate();
STR create_node(char);
void enqueue(STR *, STR);
STR load();
STR Load2(const char *tcad);
void print(STR);
STR concat(STR, STR);
STR before_token(STR, char);
int string_equal(STR, STR);
char get_char(STR);

#endif

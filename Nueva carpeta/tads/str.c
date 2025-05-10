#include<stdio.h>
#include<stdlib.h>
#include "str.h"

/*Private prototips*/

STR create_node(char);
void enqueue(STR *, STR);

/*Private prototips*/

/*Private functions*/

STR create_node(char character) {
	STR node;
	node=(STR)malloc(sizeof(T_STR_NODE));
	node->date=character;
	node->next=NULL;
	return(node);
}

void enqueue(STR *head, STR new_node) {
	STR temp;
	if(*head==NULL) *head=new_node;
	else {
		temp=*head;
		while(temp->next!=NULL) temp=temp->next;
		temp->next=new_node;
	}
}

/*Private functions*/

/*Public functions*/
void free_str(STR s) {
	STR temp;
	while (s != NULL) {
		temp = s;
		s = s->next;
		free(temp);
	}
}

STR inicializate() {
	STR string;
	string=NULL;
	return(string);
}

STR load() {
	STR string=NULL, new_node;
	char m;
	printf("\nCargue la frase: ");
	while(((m=getchar())!=EOF)&&(m!='\n')) {
		new_node=create_node(m);
		enqueue(&string, new_node);
	}
	return(string);
}

STR Load2(const char *tcad){
	int i;
	STR nodo,lis=NULL;
	i=0;
	while(tcad[i]!=EOF && tcad[i]!='\n'){
		nodo=create_node(tcad[i]);
		enqueue(&lis,nodo);
		i++;
	}
	return lis;
}

void print(STR head){
	while(head!=NULL) {
		printf("%c", head->date);
		head=head->next;
	}
}
	
	STR concat(STR head_a, STR head_b){
		STR temp;
		temp=head_a;
		if(head_a==NULL) return(head_b);
		while(temp->next!=NULL) temp=temp->next;
		temp->next=head_b;
		return(head_a);
	}
		
	STR before_token(STR head, char character) {
		STR temp;
		temp=head;
		if(temp==NULL) return NULL;
		if(temp->date==character) return NULL;
		while((temp->next!=NULL)&&(temp->next->date!=character)) temp=temp->next;
		if(temp->next!=NULL) temp->next=NULL;
		return(head);
	}
		
	int string_equal(STR head_a, STR head_b) {
		int status;
		status=1;
		while((head_a!=NULL)&&(head_b!=NULL)) {
			if(head_a->date!=head_b->date) {
				return(0);
			}
			head_a=head_a->next;
			head_b=head_b->next;
			}
			if((head_a!=NULL)||(head_b!=NULL)) {
				status=0;
			}
			return(status);
		}
		
	char get_char(STR string){
		return(string->date);
	}
/*Public functions*/

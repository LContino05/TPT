#include<stdio.h>
#include<stdlib.h>
#include"list.h"

/*Private prototips*/

LIST create_node_list();

void enqueue_list(LIST *, LIST);

LIST create_node_list_2(char);

/*Private prototips*/

/*Private functions*/

LIST create_node_list() {
	LIST node;
	node=(LIST)malloc(sizeof(T_LIST_NODE));
	node->date=load();
	node->next=NULL;
	return(node);
}

void enqueue_list(LIST *head, LIST new_node) {
	LIST temp;
	if(*head==NULL) *head=new_node;
	else {
		temp=*head;
		while(temp->next!=NULL) temp=temp->next;
		temp->next=new_node;
	}
}

LIST create_node_list_2(char character) {
	LIST node;
	node=(LIST)malloc(sizeof(T_LIST_NODE));
	node->date=create_node(character);
	node->next=NULL;
	return(node);
}

/*Private functions*/



/*Public functions*/

LIST inicializate_list() {
	LIST list;
	list=NULL;
	return(list);	
}

LIST load_list() {
	LIST list=NULL, new_node;
	int i, max_size;
	printf("Enter the size of the list: ");
	scanf("%d", &max_size);
	for(i=0; i<max_size; i++) {
		fflush(stdin);
		new_node=create_node_list();
		enqueue_list(&list, new_node);
	}
	return (list);
}

void print_list(LIST head) {
	printf("[");
	while(head!=NULL) {
		printf("{");
		print(head->date);
		printf("}, ");
		head=head->next;
	}
	printf("]");
}

STR list_to_str(LIST head) {
	STR string=NULL;
	LIST temp_list;
	temp_list=head;
	if(head==NULL) return (string);
	while(temp_list!=NULL) {
		if(temp_list->date!=NULL) string=concat(string, temp_list->date);
		temp_list=temp_list->next;
	}
	return (string);
}

LIST str_to_list(STR head) {
	LIST list=NULL, new_node;
	STR temp_str;
	temp_str=head;
	if(head==NULL) return (list);
	while(temp_str!=NULL) {
		new_node=create_node_list_2(temp_str->date);
		enqueue_list(&list, new_node);
		temp_str=temp_str->next;
	}
	return (list);
}


/*Public functions*/

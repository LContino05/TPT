#include<stdio.h>
#include<stdlib.h>
#include "tad_set.h"

/*Private prototipes*/

SET create_node_set();
SET create_node_set_2(STR);
void enqueue_set(SET *, SET);
int string_valid(SET, SET);
void clean_buffer();
SET clone_set();
void remove_duplicates(SET *);

/*Private prototipes*/

/*Private functions*/

SET create_node_set() {
    SET node;
    node=(SET)malloc(sizeof(T_SET_NODE));
    node->date=load();
    node->next=NULL;
    return(node);
}

SET create_node_set_2(STR string) {
    SET node;
    node=(SET)malloc(sizeof(T_SET_NODE));
    node->date=string;
    node->next=NULL;
    return(node);
}

void enqueue_set(SET *head, SET new_node) {
    SET temp;
    if(*head==NULL) *head=new_node;
    else {
        temp=*head;
        while(temp->next!=NULL) temp=temp->next;
        temp->next=new_node;
    }
}

void clean_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

SET clone_set(SET head) {
    SET new_set = NULL;
    SET temp = head;
    while (temp != NULL) {
        enqueue_set(&new_set, create_node_set_2(temp->date));
        temp = temp->next;
    }
    return(new_set);
}

/*Private functions*/

/*Public functions*/

SET create_set() {
    SET new=NULL, node_a, node_b;
    int n, i, c;
    i=0;
    printf("Enter the cardinal of set: ");
    scanf("%d", &n);
    clean_buffer();
    node_b=create_node_set();
    enqueue_set(&new, node_b);
    i++;
    while(i<n) {
        node_a=create_node_set();
        if(!string_equal(node_a->date, node_b->date)) {
            enqueue_set(&new, node_a);
            node_b=node_a;
            i++;
        }
    }
    return(new);
}

void show_set(SET head) {
    printf("{");
    while (head != NULL) {
        print(head->date);
        if (head->next != NULL) {
            printf(", ");
        }
        head = head->next;
    }
    printf("}");
}

void add_element_to_set(SET *head, STR new_string) {
    SET temp;
    if(*head==NULL) *head=create_node_set_2(new_string);
    else {
        temp=*head;
        while((temp->next!=NULL)&&(!string_equal(temp->date, new_string))) temp=temp->next;
        if(string_equal(temp->date, new_string)) printf("Repeated element in the set.....\n"); 
        else {
            enqueue_set(head, create_node_set_2(new_string));
        }
    }
}

SET str_to_set(STR string, char token) {
    STR temp_string=NULL, str_node=NULL;
    SET new_string=NULL;
    char character;

    while (string!=NULL) {
        character=get_char(string);

        if (character!=token) {
            str_node=create_node(character);
            enqueue(&temp_string, str_node);
        } else {
            if (temp_string!=NULL) {
                add_element_to_set(&new_string, temp_string);
                temp_string=NULL;
            }
        }

        string=string->next;
    }

    if (temp_string!=NULL) {
        add_element_to_set(&new_string, temp_string);
    }

    return(new_string);
}

/*SET str_to_set (STR head ,char character){
    SET new_set;
    STR new_string=NULL,node=NULL, temp;
    SET new_set=NULL, node_set=NULL;
    while (temp!=NULL){
        if(returnLetra(temp)!=character){
            node=create();
            node->date=returnLetra(temp);
            cargar(&new_string,node);
        }else{
            node_set=inicializar();
            node_set->date=new_string;
            cargarset(&new_set,node_set);
            new_string=NULL;
        }temp=temp->next;
    }
	
	if (new_string != NULL) {
		node_set = inicializar();
		node_set->date = new_string;
		cargarset(&new_set, node_set);
	}
    return(new_set);
}*/

SET union_set(SET head_a, SET head_b) {
    SET new_set=NULL, temp;
    if(head_a==NULL) return(head_b);
    if(head_b==NULL) return(head_a);
    temp = head_a;
    while (temp != NULL) {
        add_element_to_set(&new_set, temp->date);
        temp = temp->next;
    }
    temp = head_b;
    while (temp != NULL) {
        add_element_to_set(&new_set, temp->date);
        temp = temp->next;
    }

    return(new_set);
}

SET intersection_set(SET head_a, SET head_b) {
    SET new_set=NULL, temp_a, temp_b;
    int flag;
    if(head_a==NULL) return(NULL);
    if(head_b==NULL) return(NULL);
    temp_a=head_a;
    while(temp_a!=NULL) {
        temp_b=head_b;
        flag=1;
        while((temp_b!=NULL)&&(flag==1)) {
            if(string_equal(temp_b->date, temp_a->date)) {
                add_element_to_set(&new_set, temp_b->date);
                flag=0;
            }
            temp_b=temp_b->next;
        }
        temp_a=temp_a->next;
    }
    return(new_set);
}

SET difference_set(SET head_a, SET head_b) {
    SET new_set=NULL, temp_a, temp_b;
    int flag;
    if(head_a==NULL) return(NULL);
    if(head_b==NULL) return(head_a);
    temp_a=head_a;
    while(temp_a!=NULL) {
        temp_b=head_b;
        flag=1;
        while((temp_b!=NULL)&&(flag==1)) {
            if(string_equal(temp_a->date, temp_b->date)) {
                flag=0;
            }
            temp_b=temp_b->next;
        }
        if(flag==1) add_element_to_set(&new_set, temp_a->date);
        temp_a=temp_a->next;
    }
    return(new_set);
}

int is_element_in_set(SET head, STR element) {
    int status, flag;
    status=0;
    flag=1;
    while((head!=NULL)&&(flag==1)) {
        if(string_equal(head->date, element)) { 
            status=1;
            flag=0;
        }
        head=head->next;
    }
    return(status);
}

int is_sub_set(SET head_a, SET head_b) {
    SET temp_a;
    int status=1, flag;
    temp_a=head_a;
    flag=1;
    while((temp_a!=NULL)&&(flag==1)) {
        if(!is_element_in_set(head_b, temp_a->date)) {
            status=0;
            flag=0;
        }
        temp_a=temp_a->next;
    }
    return(status);
}

/*Public functions*/
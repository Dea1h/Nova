#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct{
	void *data;
	void *next;
}Node;

Node *Head = NULL;

Node *insertNode(void *data,unsigned int position){
	Node *new;
	if(Head == NULL){
		new = malloc(sizeof(Node));
		if(new == NULL){
			return NULL;
		}
		new->data = data;
		Head = new;
		new->next = NULL;
	}
	else if (position == 0){
		new = malloc(sizeof(Node));
		if(new == NULL){
			return  NULL;
		}

		new->next = Head;
		Head = new;
	}
	else if(position > 0){
		Node *current = Head;
		while(position != 0){
			position--;
			current = current->next;
		}
	}
	else if(position == -1){
		Node *current = Head;
		while(current->next != NULL){
			current = current->next;
		}
		new = malloc(sizeof(Node));
		if(new == NULL){
			return NULL;
		}
		current->next = new;
	}
	return new;
}
Node *removeNode(void *data){
	Node *current = Head;
	Node *prev = Head;
	while(current != NULL){
		if(current->data == data){
			if(current == Head){
				Head = current->next;
			}
			else {
				prev->next = current->next;
				free(current);
				current = NULL;
			}
			return NULL;
		}
		prev = current;
		current = current->next;
	}

	return 0;
}

void deleteList(Node *Top){
	Node *current = Top;
	Node *NEXT = current->next;
	while(current->next != NULL){
		free(current);
		current = NEXT->next;
		NEXT = current->next;
	}

}

char *process_request(char *buffer,int len){
	char *request = (char *)parseHTML(buffer,len);
}

void load_config(){

}

void print_info(){
	printf("CID\t\t");
}

void *parseHTML(char *buffer,int len){

}

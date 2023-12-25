#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct{
	void *data;
	void *next;
}Node;

Node *Head = NULL;

Node *appendNode(void *data){
	Node *new;
	if(Head == NULL){
		new = malloc(sizeof(Node));
		if(new == NULL){
			perror("NODE MALLOC");
			return NULL;
		}
		new->data = data;
		Head = new;
		new->next = NULL;
	}
	else{
		new = malloc(sizeof(Node));
		if(new == NULL){
			perror("NODE MALLOC");
			return NULL;
		}

		new->next = Head;
		Head = new;
		
	}
	return new;
}

Node *insertNode(void *data,int position){
	Node *current = Head;

	while(current != NULL && position != 0){
		position--;
	}

	if(position != 0){
		printf("Requested position too far into list\n");
		return NULL;
	}

	Node *new = malloc(sizeof(Node));
	if(new == NULL){
		return NULL;
	}

	new->data = data;
	new->next = current->next;
	current->next = new;
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

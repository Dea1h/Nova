#ifndef _ATOMIC_H
#define _ATOMIC_H
#include <cstdint>
typedef struct{
	void *data;
	void *next;
}Node;

Node *appendNode(void *data);

Node *insertNode(void *data,int position);

int removeNode(int postion);

void deleteList(Node *Top);

char *process_request(char *buffer,int len);

void load_config();

void print_info();

void *parseHTML(char *buffer,int len);
#endif // !DEBUG

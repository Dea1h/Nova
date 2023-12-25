#ifndef _ATOMIC_H
#define _ATOMIC_H
#include <cstdint>
typedef struct{
	uint32_t failover_ip;
	void *next;
}Node;
Node *appendNode(void *data);
Node *insertNode(void *data,int position);
int removeNode(int postion);
void deleteList(Node *Top);
#endif // !DEBUG

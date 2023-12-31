#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define Queue 4
#define Buffsize 1024
#define PORT 8080
int main(int argc, char *argv[]){
	struct sockaddr_in server_info;
	struct sockaddr client_info;
	char *client_address = (char *)malloc(512 * sizeof(char));
	socklen_t client_len = sizeof(client_info);
	socklen_t server_len = sizeof(server_info);

	server_info.sin_family = AF_INET;
	server_info.sin_port = htons(PORT);
	server_info.sin_addr.s_addr = INADDR_ANY;
	//int set = setsockopt(sfd,SOL_SOCKET,);
	
	int sfd = socket(AF_INET,SOCK_STREAM,0);

	if(sfd < 0){
		perror("SOCKET");
		printf("ERROR CODE: %d\n",errno);
		return 1;
	}

	if(bind(sfd,(struct sockaddr *)&server_info,server_len) < 0){
		perror("BIND");
		printf("ERROR CODE: %d\n",errno);
		return 1;
	}

	if(listen(sfd,Queue) < 0){
		perror("LISTEN");
		printf("ERROR CODE: %d\n",errno);
		return 1;
	}
	printf("Listening on Port 8080");
	char *buffer = (char*)malloc(Buffsize * sizeof(char));
	if(buffer == NULL){
		perror("MALLOC");
		printf("ERROR CODE: %d\n",errno);
		return 1;
	}
	memset(buffer,0,Buffsize - 1);
	*(buffer + Buffsize - 1) = '\0';
	strcpy(buffer, "HELL");
	while(true){
		int cfd = accept(sfd,&client_info,&client_len);
		
		if(cfd < 0){
			perror("ACCEPT");
			printf("ERROR CODE: %d\n",errno);
			return 1;
		}
		while(true){
			ssize_t recvd = recv(sfd,buffer,Buffsize - 1,0);
			if(recvd < 0){
				perror("RECV");
				printf("ERROR CODE: %d\n",errno);
				return 1;
			}
			else if(recvd == 0){
			}

			ssize_t sent = send(sfd,buffer,Buffsize - 1,0);
			if(sent < 0){
				perror("SEND");
				printf("ERROR CODE: %d\n",errno);
				return 1;
			}
			else if(sent == 0){
				int shut = shutdown(sfd,SHUT_RDWR);
				if(shut < 0){
					perror("SHUT");
					printf("ERROR CODE: %d\n",errno);
					return 1;
				}
			}
		}
	}
	free(buffer);
	close(sfd);
	
}

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <unistd.h>

#define Queue 4
#define Buffsize 1024
#define PORT 8080
int main(int argc, char *argv[]){
	printf("STARTING SERVER\n");
	struct sockaddr_in server_info;
	struct sockaddr client_info;
	socklen_t client_len = sizeof(client_info);
	socklen_t server_len = sizeof(server_info);

	server_info.sin_family = AF_INET;
	server_info.sin_port = htons(PORT);
	server_info.sin_addr.s_addr = INADDR_ANY; 
	
	int sfd = socket(AF_INET,SOCK_STREAM,0);

	if(sfd < 0){
		perror("SOCKET");
		return 1;
	}

	if(bind(sfd,(struct sockaddr *)&server_info,server_len) < 0){
		perror("BIND");
		return 1;
	}

	if(listen(sfd,Queue) < 0){
		perror("LISTEN");
		return 1;
	}
	printf("Listening on Port 8080");

	char *buffer = (char*)malloc(Buffsize * sizeof(char));
	if(buffer == NULL){
		perror("MALLOC");
		return 1;
	}
	memset(buffer,0,Buffsize - 1);
	*(buffer + Buffsize - 1) = '\0';
	strcpy(buffer, "HELL");
	while(true){
		int cfd = accept(sfd,&client_info,&client_len);
		
		if(cfd < 0){
			perror("ACCEPT");
			return 1;
		}
		int sent = send(cfd,buffer,1024,0);
	       if(sent < 0){
			perror("SEND");
			return 1;
		}
		//int recvd = recv(sfd,buffer,Buffsize - 1,0);
		//if(recvd < 0){
		//	perror("RECV");
		//	return 1;
	//	}
		//printf("%s",buffer);
		close(cfd);
		break;
	}
	free(buffer);
	close(sfd);
	
}

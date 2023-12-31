#include <arpa/inet.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <unistd.h>

#define Buffsize 1024
#define PORT 8080
int main(int argc, char *argv[]){
	uint32_t SERVER_IP;
	if(argc > 1){
		const char *ip_str = argv[1];
		SERVER_IP = inet_addr(ip_str);
		if(SERVER_IP == INADDR_NONE){
			perror("INET_ADDR");
			return 1;
		}
	}
	else{
		SERVER_IP = 0x100007f;
	}
	printf("SARTING CLIENT\n");
	struct sockaddr_in server_info;
	socklen_t server_len = sizeof(server_info);

	server_info.sin_port = htons(PORT);
	server_info.sin_family = AF_INET;
	server_info.sin_addr.s_addr = SERVER_IP;

	int sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd < 0){
		perror("SOCKET");
		printf("ERROR CODE: %d\n",errno);
		return 1;
	}
	
	if(connect(sfd,(struct sockaddr*)&server_info,server_len) < 0){
		perror("CONNECT");
		printf("ERROR CODE: %d\n",errno);
		return 1;
	}
	char *buffer = (char*)malloc(Buffsize * sizeof(char));
	if(buffer == NULL){
		perror("MALLOC");
		printf("ERROR CODE: %d\n",errno);
		return 1;
	}
	memset(buffer,0,Buffsize - 1);
	*(buffer + Buffsize -1) = '\0';
	while (true) {
		ssize_t sent = send(sfd,buffer,Buffsize - 1,0);
		if(sent < 0){
			perror("SEND");
			printf("ERROR CODE: %d\n",errno);
			return 1;
		}
		ssize_t recvd = recv(sfd,buffer,Buffsize - 1, 0);
		if(recvd < 0){
			perror("RECV");
			printf("ERROR CODE: %d\n",errno);
			return 1;
		}
		printf("%s",buffer);
		break;
	}
	free(buffer);
	close(sfd);
}

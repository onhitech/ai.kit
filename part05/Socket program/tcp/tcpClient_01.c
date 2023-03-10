//=======================================
// tcpClientChat.c (Linux)
//	for Chatting
//=======================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define SERVERIP   "220.68.70.199"		// taget !!
#define PORTNUM	   0x5005				//
#define BUFFSIZE   256

int main(void) {
	int sock_fd;
	struct sockaddr_in serv_addr;
	char buffer[BUFFSIZE];

	printf("[TCP server for chatting and controlling LED...]\n");

	// 1) create client socket
	if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("ERROR opening socket");
		exit(1);
	}

	// 2) setting server socket structure
	serv_addr.sin_family		= AF_INET;
	serv_addr.sin_addr.s_addr	= inet_addr(SERVERIP);
	serv_addr.sin_port			= htons(PORTNUM);

	// 3) connect
	if(connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) { 
		perror("ERROR connecting");
		exit(1);
	}

	// 4) read/write, read(), receiving...
	memset(buffer, 0x00, sizeof(buffer));
	if(read(sock_fd, buffer, BUFFSIZE)== -1){
		perror("ERROR reading from socket");
		exit(1);
	}    
	printf("[Server] %s\n", buffer);

	while(1) {
		memset(buffer, 0x00, sizeof(buffer));

		printf("[Guest] ");
		fgets(buffer, BUFFSIZE, stdin);

		// 4) read/write, write(), sending...
		if(write(sock_fd, buffer, strlen(buffer)) == -1) {
			perror("ERROR writing to socket");
			exit(1);
		}
		if(buffer[0] == 'q')
			break;	

		// 4) read/write, read(), receiving...
		memset(buffer, 0x00, sizeof(buffer));
		if(read(sock_fd, buffer, BUFFSIZE) == -1) {
			perror("ERROR reading from socket");
			exit(1);
		}

		printf("[Server] %s\n", buffer);
		if(buffer[0] == 'q')
			break;	
	}

	// 5) close(),  close client socker, disconnection
	close(sock_fd);

	return 0;
}




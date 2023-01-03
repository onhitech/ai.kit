//=======================================
// udpSever.c (Linux)
//	for Chatting
//=======================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORTNUM		0x5005
#define BUFFSIZE 	256

int main(void) {
	struct sockaddr_in serv_addr, cli_addr;
	int serv_fd, cli_fd, clilen;
	char buffer[BUFFSIZE];

	printf("[UDP Server for Chatting...\n");

	// 1) create server socket
	if((serv_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("ERROR opening socket");
		exit(1);
	}

	// 2) setting server socket structure
	memset((char *) &serv_addr, 0x00, sizeof(serv_addr));
	serv_addr.sin_family 		= AF_INET;
	serv_addr.sin_addr.s_addr 	= INADDR_ANY;
	serv_addr.sin_port		= htons(PORTNUM);

	// 3) bind()
	if(bind(serv_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) { 
		perror("ERROR on binding");
		exit(1);
	}

   	while(1) {
		// 4) recvfrom/sendto,
		memset(buffer, 0x00, sizeof(buffer));
		clilen = sizeof(cli_addr);
		recvfrom(serv_fd, buffer, BUFFSIZE, 0, (struct sockaddr *)&cli_addr, &clilen);
		printf("[Guest] %s\n", buffer);
		if(buffer[0] == 'q') {
			close(cli_fd);
			break;
		}

		// 4) recvfrom/sendto, sending...
		printf("[Server] ");
		memset(buffer, 0x00, sizeof(buffer));
		fgets(buffer, BUFFSIZE, stdin);
		sendto(serv_fd, buffer, BUFFSIZE, 0, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
		if(buffer[0] == 'q')
			break;
	}
	// 5) close(),
	close(serv_fd);

	return 0;
}


//=======================================
// tcpSever.c (Linux)
//	for Chatting
//=======================================
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORTNUM		0x5005		// port#
#define BUFFSIZE	256

int main(void) {
	struct sockaddr_in serv_addr, cli_addr;
	int serv_fd, cli_fd, clilen;
	char buffer[BUFFSIZE];

	printf("[TCP server for chatting...]\n");

	// 1) create server socket
	if((serv_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("ERROR opening socket");
		exit(1);
	}

	// 2) setting server socket structure
	memset((char *) &serv_addr, 0x00, sizeof(serv_addr));
	serv_addr.sin_family		= AF_INET;
	serv_addr.sin_addr.s_addr	= htonl(INADDR_ANY);
	serv_addr.sin_port		= htons(PORTNUM);

	// 3) bind()
	if(bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) { 
		perror("ERROR on binding");
		exit(1);
	}

	// 4) listen()
	listen(serv_fd, 5);

loop:

	// 5) accept(), blocking...
	clilen = sizeof(cli_addr);
	if((cli_fd = accept(serv_fd, (struct sockaddr *)&cli_addr, &clilen)) == -1) {
		perror("ERROR on accept");
		exit(1);
	}

	// 6) read/write, write(), sending...
	write(cli_fd, "Welcome to Chat Server.....", BUFFSIZE);

	while(1) {
		memset(buffer, 0x00, sizeof(buffer));

		// 6) read/write, read(), receiving...
		if((read(cli_fd, buffer, BUFFSIZE)) == -1) {
	        perror("ERROR reading from socket");
			exit(1);
		}
		printf("[Guest] %s\n", buffer);

		if(buffer[0] == 'q') {
			close(cli_fd);
			goto loop;
		}

		memset(buffer, 0x00, sizeof(buffer));
		printf("[Server] ");
		fgets(buffer, BUFFSIZE, stdin);

		// 6) read/write, write(), sending...
		write(cli_fd, buffer, BUFFSIZE);
		if(buffer[0] == 'q')
		break;
	}

	// 7) close(),  close server socker, disconnection
	close(serv_fd);

	return 0;
}


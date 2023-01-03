//=======================================
// tcpSever_01.c (Linux)
//	Chatting + controlling LED device
//=======================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#include <wiringPi.h>			// *)

#define PORTNUM		0x5005		// port#
#define BUFFSIZE	256

#define P_LED		1		// BCM_GPIO #18

int main(void) {
	struct sockaddr_in serv_addr, cli_addr;
	int serv_fd, cli_fd, clilen;
	char buffer[BUFFSIZE];

	printf("[TCP server for chatting and controlling LED...]\n");

	if(wiringPiSetup() == -1)		// wiringPi pin #
		return 1;

	pinMode(P_LED, OUTPUT);			//

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
	write(cli_fd, "Welcome to Chat Server.....LED control..", BUFFSIZE);

	while(1) {
		// 6) read/write, read(), receiving...
		memset(buffer, 0x00, sizeof(buffer));
		if((read(cli_fd, buffer, BUFFSIZE)) == -1){
			perror("ERROR reading from socket");
			exit(1);
		}
		printf("[Guest] %s\n", buffer);

		if(buffer[0] == 'q') {
			close(cli_fd);
			goto loop;
		}
		else if(buffer[0] == '0')		// LED control....
			digitalWrite(P_LED, LOW);
		else if(buffer[0] == '1')
			digitalWrite(P_LED, HIGH);

		// 6) read/write, write(), sending...
		memset(buffer, 0x00, sizeof(buffer));
		printf("[Server] ");
		fgets(buffer, BUFFSIZE, stdin);
		write(cli_fd, buffer, BUFFSIZE);
		if(buffer[0] == 'q')
			break;
	}

	// 7) close(),  close server socker, disconnection
	close(serv_fd);

	return 0;
}


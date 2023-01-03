//=======================================
// udpClientChat.c (Linux)
//	for Chatting
//=======================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define SERVERIP	"192.168.0.40"
#define PORTNUM		0x5005
#define BUFFSIZE	256

int main(void) {
	struct sockaddr_in serv_addr;
	int cli_fd;
	int servlen;
	char buffer[BUFFSIZE];

	printf("[UDP Client for Chatting...\n");

	// 1) create socket
	if((cli_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		perror("ERROR opening socket");
		exit(1);
	}

	serv_addr.sin_family		= AF_INET;
	serv_addr.sin_addr.s_addr	= inet_addr(SERVERIP);
	serv_addr.sin_port		= htons(PORTNUM);

	while(1) {
		memset(buffer, 0x00, sizeof(buffer));
		printf("[Guest] ");
		fgets(buffer, BUFFSIZE, stdin);

		// 2) recvfrom/sendto, sending....
		sendto(cli_fd, buffer, BUFFSIZE, 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
		if(buffer[0] == 'q')
			break;

		// 2) recvfrom/sendto, receiving....
		memset(buffer, 0x00, sizeof(buffer));
		servlen = sizeof(serv_addr);
		recvfrom(cli_fd, buffer, BUFFSIZE, 0, (struct sockaddr *)&serv_addr, &servlen);
		printf("[Server] %s\n", buffer);
		if(buffer[0] == 'q')
			break;
	}

	// 3) close(), disconnection
	close(cli_fd);

	return 0;
}


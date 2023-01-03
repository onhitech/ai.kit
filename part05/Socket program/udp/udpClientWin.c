//=======================================
// udpClientWin.c (Windows)
//	for Chatting
//=======================================
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>

//#define SERVERIP   	"192.168.0.40"
#define PORTNUM		0x5005
#define BUFFSIZE	256

int main(int argc, char *argv[]) {
//	struct sockaddr_in serv_addr;
	SOCKADDR_IN serv_addr;
	WSADATA wsaData;
//	int cli_fd;
	SOCKET cli_fd;
	int servlen;
	char buffer[BUFFSIZE];

	if(argc != 2) {
		printf("usage : %s [port]\n", argv[0]);
		exit(0);
	}

	printf("[TCP client for chatting...]\n");

	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		perror("ERROR WSAStartup()");
		exit(1);
	}

	// 1) create socket
	if((cli_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		perror("ERROR opening socket");
		exit(1);
	}

	serv_addr.sin_family		= AF_INET;
	serv_addr.sin_addr.s_addr	= inet_addr(argv[1]);	// SERVERIP
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
	closesocket(cli_fd);

	return 0;
}


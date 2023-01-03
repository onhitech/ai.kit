//=======================================
// tcpClientWin.c (Windows)
//	for Chatting
//=======================================
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>

//#define SERVERIP	"192.168.0.40"		// taget !!
#define PORTNUM		0x5005			//
#define BUFFSIZE	256

int main(int argc, char *argv[]) {
//	int sock_fd;
	SOCKET sock_fd;
//	struct sockaddr_in serv_addr;
	SOCKADDR_IN serv_addr;
	WSADATA wsaData;
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

	// 1) create client socket
	if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("ERROR opening socket");
		exit(1);
	}

	// 2) setting server socket structure
	serv_addr.sin_family		= AF_INET;
	serv_addr.sin_addr.s_addr	= inet_addr(argv[1]);	//	SERVERIP
	serv_addr.sin_port			= htons(PORTNUM);

	// 3) connect
	//if(connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) { 
	if(connect(sock_fd, (SOCKADDR *)&serv_addr, sizeof(serv_addr)) == -1) {
		perror("ERROR connecting");
		exit(1);
	}

	// 4) read/write, read(), receiving...
	memset(buffer, 0x00, sizeof(buffer));
	//if(read(sock_fd, buffer, BUFFSIZE) == -1) {
	if(recv(sock_fd, buffer, BUFFSIZE, 0) == -1) {
		perror("ERROR reading from socket");
		exit(1);
	}
	printf("[Server] %s\n", buffer);

	while(1) {
		memset(buffer, 0x00, sizeof(buffer));
		printf("[Guest] ");
		fgets(buffer, BUFFSIZE, stdin);

		// 4) read/write, write(), sending...
		//if(write(sock_fd, buffer, strlen(buffer)) == -1) {
		if(send(sock_fd, buffer, strlen(buffer), 0) == -1) {
			perror("ERROR writing to socket");
			exit(1);
		}
		if(buffer[0] == 'q')
			break;

		// 4) read/write, read(), receiving...
		memset(buffer, 0x00, sizeof(buffer));
		//if(read(sock_fd, buffer, BUFFSIZE) == -1) {
		if(recv(sock_fd, buffer, BUFFSIZE, 0) == -1) {
			perror("ERROR reading from socket");
			exit(1);
		}

		printf("[Server] %s\n", buffer);
		if(buffer[0] == 'q')
			break;
	}

	// 5) close(),  close client socker, disconnection
	//close(sock_fd);
	closesocket(sock_fd);

	WSACleanup();

	return 0;
}


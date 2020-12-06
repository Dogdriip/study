#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

#define BUF_SIZE 1024
void error_handling(char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	int sock;
	char message[BUF_SIZE];
	int result, str_len;
	struct sockaddr_in serv_adr;
	struct timeval timeout;
	fd_set reads, temps;

	/*
	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	} */

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		error_handling("WSAStartup() error!");

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_adr.sin_port = htons(atoi("123654"));

	if (connect(sock, (struct sockaddr*) & serv_adr, sizeof(serv_adr)) == -1)
		error_handling("connect() error!");
	else
		puts("Connected...........");

	FD_ZERO(&reads);
	FD_SET(sock, &reads);

	while (1)
	{
		fputs("Input message(Q to quit): ", stdout);
		fgets(message, BUF_SIZE, stdin);

		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;

		send(sock, message, strlen(message), 0);
		
		str_len = recv(sock, message, BUF_SIZE - 1, 0);
		message[str_len] = 0; 
		printf("Message from server: %s", message);
	}
	closesocket(sock);
	WSACleanup();
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
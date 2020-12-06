#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#define BUF_SIZE 1024
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
	WSADATA	wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;

	int szClntAddr;
	char message[BUF_SIZE];
	int i;
	int str_len;
	int idx = 0, readLen = 0;

	/*if (argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}*/

	printf("* SERVER *\n");

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi("32154"));

	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	if (listen(hServSock, 3) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	szClntAddr = sizeof(clntAddr);

	for (i = 0; i < 3; i++) {
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
		if (hClntSock == INVALID_SOCKET)
			ErrorHandling("accept() error");
		
		printf("Connected client %d\n", i + 1);

		while ((str_len = recv(hClntSock, message, BUF_SIZE, 0)) != 0) {
			if (str_len == -1) break;
			send(hClntSock, message, str_len, 0);
		}
		printf("Client %d is disconnected\n", i + 1);
		closesocket(hClntSock);
	}

	printf("서버 프로그램을 종료합니다\n");
	closesocket(hServSock);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

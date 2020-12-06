#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
	WSADATA	wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;

	int szClntAddr;
	char inMessage[30];
	int strLen = 0;
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

	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	szClntAddr = sizeof(clntAddr);
	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
	if (hClntSock == INVALID_SOCKET)
		ErrorHandling("accept() error");


	while (1) {
		if (inMessage[idx - 1] == '\n') {
			break;
		}
		readLen = recv(hClntSock, &inMessage[idx++], 1, 0);
		if (readLen == -1)
			ErrorHandling("read() error!");

		strLen += readLen;
	}

	printf("Message from client: %s\n", inMessage);
	printf("Function read call count: %d\n", strLen);

	send(hClntSock, inMessage, sizeof(inMessage), 0);
	send(hClntSock, "\n", sizeof("\n"), 0);

	closesocket(hClntSock);
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

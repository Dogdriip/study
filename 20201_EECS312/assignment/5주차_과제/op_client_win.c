#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4

#define IP_ADDR "127.0.0.1"
#define PORT 32154

void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	char opmsg[BUF_SIZE];
	char flag;  // operand count에서 Q 받으면 quit해야하므로 char형
	int result, opndCnt, i;
	int recvCnt, recvLen;  // added
	SOCKADDR_IN servAdr;
	/* if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	} */

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr(IP_ADDR);
	servAdr.sin_port = htons(PORT);

	if (connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("connect() error!");
	else
		puts("Connected...........");

	// main logic 
	/*
	fputs("Operand count: ", stdout);
	scanf("%d", &opndCnt);
	opmsg[0] = (char)opndCnt;

	for (i = 0; i < opndCnt; i++)
	{
		printf("Operand %d: ", i + 1);
		scanf("%d", (int*)&opmsg[i * OPSZ + 1]);
	}
	fgetc(stdin);
	fputs("Operator: ", stdout);
	scanf("%c", &opmsg[opndCnt * OPSZ + 1]);
	send(hSocket, opmsg, opndCnt * OPSZ + 2, 0);
	recv(hSocket, &result, RLT_SIZE, 0);

	printf("Operation result: %d \n", result);
	*/
	while (1) {
		flag = "";
		fputs("Operand count(Q to quit): ", stdout);
		scanf(" %c", &flag);
		if (flag == 'q' || flag == 'Q') {
			break;
		} else {
			opndCnt = (int)flag - 48;
		}

		opmsg[0] = (char)opndCnt;
		for (i = 0; i < opndCnt; i++) {
			printf("Operand %d: ", i + 1);
			scanf("%d", (int*)&opmsg[i * OPSZ + 1]);
		}
		fgetc(stdin);
		fputs("Operator: ", stdout);
		scanf("%c", &opmsg[opndCnt * OPSZ + 1]);
		send(hSocket, opmsg, opndCnt * OPSZ + 2, 0);
		recvLen = 0;
		recvCnt = 0;

		while (RLT_SIZE > recvLen) {
			recvCnt = recv(hSocket, &result, RLT_SIZE, 0);
			if (recvCnt == -1) {
				ErrorHandling("read() error!");
			}
			recvLen += recvCnt;
		}
		printf("Operation result: %d\n", result);
	}
	// main logic end

	closesocket(hSocket);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
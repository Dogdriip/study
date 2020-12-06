#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE 1024
#define OPSZ 4

#define PORT 32154

void ErrorHandling(char* message);
int calculate(int opnum, int opnds[], char oprator);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	char opinfo[BUF_SIZE];
	int result, opndCnt, i;
	int recvCnt, recvLen;
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSize;
	/* if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	} */

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(PORT);

	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");
	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");
	clntAdrSize = sizeof(clntAdr);

	// main logic
	/*
	for (i = 0; i < 5; i++) {
		opndCnt = 0;
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSize);
		recv(hClntSock, &opndCnt, 1, 0);

		recvLen = 0;
		while ((opndCnt * OPSZ + 1) > recvLen)
		{
			recvCnt = recv(hClntSock, &opinfo[recvLen], BUF_SIZE - 1, 0);
			recvLen += recvCnt;
		}
		result = calculate(opndCnt, (int*)opinfo, opinfo[recvLen - 1]);
		send(hClntSock, (char*)&result, sizeof(result), 0);
		closesocket(hClntSock);
	}
	*/
	for (i = 0; i < 5; i++) {
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSize);
		if (hClntSock == -1) {
			ErrorHandling("accept() error");
		} else {
			printf("Connected client %d\n", i + 1);
		}

		int flag;  // client 종료 판단을 위한 flag
		// client에게 지속적인 서비스를 해 주기 위한 while문
		while (1) {
			flag = 0;
			opndCnt = 0;  // operand 수
			recvLen = 0;  // buffer로부터 읽어온 길이
			recv(hClntSock, &opndCnt, 1, 0);  // 1바이트만 읽음. operand 개수 가져오는 것
			while ((opndCnt * OPSZ + 1) > recvLen) {
				recvCnt = recv(hClntSock, &opinfo[recvLen], BUF_SIZE, 0);
				recvLen += recvCnt;
				if (recvCnt == -1 || recvCnt == 0) {  // client가 종료되었다면 flag = 1
					flag = 1;
					break;
				}
			}

			// client가 종료되었다면 (flag = 1) while 종료
			if (flag == 1) break;

			result = calculate(opndCnt, (int*)opinfo, opinfo[recvLen - 1]);
			send(hClntSock, (char*)&result, sizeof(result), 0);
			printf("result: %d\n", result);
		}
		printf("Client %d is disconnected\n", i + 1);
		closesocket(hClntSock);
	}
	// main logic end

	closesocket(hServSock);
	WSACleanup();
	return 0;
}

int calculate(int opnum, int opnds[], char op)
{
	int result = opnds[0], i;

	switch (op)
	{
	case '+':
		for (i = 1; i < opnum; i++) result += opnds[i];
		break;
	case '-':
		for (i = 1; i < opnum; i++) result -= opnds[i];
		break;
	case '*':
		for (i = 1; i < opnum; i++) result *= opnds[i];
		break;
	}
	return result;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
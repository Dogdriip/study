#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

#define BUF_SIZE 30
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;

	FILE* fp;
	char buf[BUF_SIZE];
	int readCnt;

	char filename[BUF_SIZE];
	
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSz;
	/*
	if (argc != 2) {
	printf("Usage: %s <port>\n", argv[0]);
	exit(1);
	}*/
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi("123654"));

	bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr));
	listen(hServSock, 5);

	clntAdrSz = sizeof(clntAdr);
	hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);

	// get filename
	memset(filename, 0, sizeof(filename));
	recv(hClntSock, filename, BUF_SIZE, 0);
	// printf("strlen: %d\n", strlen(filename));
	printf("Received File name: %s\n", filename);

	// open file
	fopen_s(&fp, filename, "rb");
	if (!fp) {
		printf("파일이 존재하지 않습니다.\n");
		fclose(fp);
		closesocket(hClntSock); closesocket(hServSock);
		WSACleanup();
		return 0;
	}

	// read file and send it to client
	while (1) {
		// file의 끝까지 1byte씩 읽어
		readCnt = fread((void*)buf, 1, BUF_SIZE, fp);

		if (readCnt < BUF_SIZE) {
			// 읽은 데이터 전송
			send(hClntSock, (char*)&buf, readCnt, 0);
			break;
		}

		send(hClntSock, (char*)&buf, BUF_SIZE, 0);
	}

	// cleanup
	shutdown(hClntSock, SD_SEND);
	recv(hClntSock, (char*)buf, BUF_SIZE, 0);
	printf("Message from client: %s \n", buf);

	fclose(fp);
	closesocket(hClntSock); closesocket(hServSock);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
#define _WINSOCK_DEPRECATED_NO_WARNINGS
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
	SOCKET hSocket;

	char buf[BUF_SIZE];
	char filename[BUF_SIZE];
	int str_len;
	int readCnt;
	SOCKADDR_IN servAdr;
	FILE* fp;

	/*if (argc != 3) {
	printf("Usage: %s <IP> <port>\n", argv[0]);
	exit(1);
	}*/
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");
	hSocket = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAdr.sin_port = htons(atoi("123654"));

	connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr));

	// connected
	// send filename
	memset(filename, 0, sizeof(filename));
	fputs("File name: ", stdout);
	fgets(filename, BUF_SIZE, stdin);
	filename[strlen(filename) - 1] = '\0';
	// printf("we'll send: %s\n", filename);
	send(hSocket, filename, strlen(filename), 0);
	
	// write new file
	fopen_s(&fp, filename, "wb");

	// receive
	while ((readCnt = recv(hSocket, buf, BUF_SIZE, 0)) != 0) {
		if (readCnt == -1) {
			// should closesocket
			fclose(fp);
			closesocket(hSocket);
			WSACleanup();
		}
		fwrite((void*)buf, 1, readCnt, fp);
	}

	puts("Received file data");
	send(hSocket, "Thank you", 10, 0);
	fclose(fp);
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
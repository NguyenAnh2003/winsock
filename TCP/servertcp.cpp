#define _WIN32_WINNT 0x501

#include <windows.h>
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
int main(int argc, char **argv)
{
  WSADATA ws;
  char buffer[50];
  sockaddr_in servAddr;
  ZeroMemory(&servAddr, sizeof(servAddr));
  SOCKET mysocket;

  int rs = WSAStartup(MAKEWORD(2, 2), &ws);
  if (rs != 0)
  {
    cout << rs;
  }

  mysocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (mysocket == SOCKET_ERROR)
  {
    cout << "Error socket init" << WSAGetLastError() << endl;
    exit(EXIT_FAILURE);
  }

  // binding
  ZeroMemory(&servAddr, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons(8000);
  servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

  int rc = bind(mysocket, (sockaddr *)&servAddr, sizeof(servAddr));
  if (rc == SOCKET_ERROR)
  {
    cout << "Error binding" << WSAGetLastError() << endl;
    exit(EXIT_FAILURE);
  }

  // listening
  listen(mysocket, SOMAXCONN);

  // wait for connection
  SOCKET clientSocket;
  sockaddr_in client;
  int clientsize = sizeof(client);
  while (true)
  {
    // clientSocket = accept(mysocket, (sockaddr *)&client, &clientsize);
    clientSocket = accept(mysocket, NULL, NULL);
    if (clientSocket == SOCKET_ERROR)
    {
      cout << "Error at connection: " << WSAGetLastError() << endl;
    } else {
      printf("client connected\n");
    }

    int len = sizeof(servAddr);
    // int result = recvfrom(clientSocket, (char *)buffer, 50, 0, (sockaddr *)&servAddr, &len);
    int result = recv(clientSocket, (char *)buffer, 50, 0);
    if(result == SOCKET_ERROR) {
      cout << "Error at receiving: " << WSAGetLastError() << endl;
      closesocket(mysocket);
    }
    buffer[result] = '\0';
    cout << "Result: " << buffer << endl;
    
  }

  closesocket(mysocket);
  // shutdown
  WSACleanup();
  return 0;
}
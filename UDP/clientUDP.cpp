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
  const char *hello = "Hello from client";
  sockaddr_in servAddr = {0};
  SOCKET mysocket;

  int rs = WSAStartup(MAKEWORD(2, 2), &ws);
  if (rs != 0)
  {
    cout << rs << endl;
  }

  mysocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (mysocket == SOCKET_ERROR)
  {
    cout << "Error socket init" << WSAGetLastError() << endl;
    exit(EXIT_FAILURE);
  }

  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons(8000);
  servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

  int len = sendto(mysocket, (char *)hello, strlen(hello), 0, (sockaddr *)&servAddr, sizeof(servAddr));
  if (len == SOCKET_ERROR)
  {
    cout << "Failed to send "<< WSAGetLastError() << endl;
  }
  closesocket(mysocket);
  // shutdown
  WSACleanup();
  return 0;
}
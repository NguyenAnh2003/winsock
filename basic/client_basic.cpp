#ifndef WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x501
#endif

#include <string>
#include <iostream>
#include <windows.h>
#include <iphlpapi.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

using namespace std;
int main(int argc, char **argv) {
  // init WSA
  WSADATA wsaData;
  struct addrinfo *result = NULL, *ptr = NULL, hints;

  // text input
  const int bufSize = 256;
  char inbuf[bufSize];
  cout << "Input\n";
  cin.getline(inbuf, bufSize);

  // send file?

  // buffer
  char recvbuf[DEFAULT_BUFLEN];
  SOCKET mysocket = INVALID_SOCKET;
  int rs;
  int recvbuflen = DEFAULT_BUFLEN;

  // init winsock
  rs = WSAStartup(MAKEWORD(2,2), &wsaData);
  if(rs != 0) {
    printf("WSAStartup failed with error: %d\n", rs);
    return 1;
  }

  ZeroMemory(&hints, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  // resolve the server address and port 
  rs = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
  if(rs != 0) {
    printf("getaddrinfo failed: ", rs);
    WSACleanup();
    return 1;
  }

  for(ptr=result; ptr != NULL; ptr=ptr->ai_next) {
    mysocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if(mysocket == INVALID_SOCKET) {
      printf("socket failed with error: %ld\n", WSAGetLastError());
      WSACleanup();
      return 1;
    }
    rs = connect(mysocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if(rs == SOCKET_ERROR) {
      closesocket(mysocket);
      mysocket == INVALID_SOCKET;
      continue;
    }
    break;
  }

  freeaddrinfo(result);
  if(mysocket == INVALID_SOCKET) {
    printf("Unable to connect to server!\n");
    WSACleanup();
    return 1;
  }

  rs = send(mysocket, inbuf, (int)strlen(inbuf), 0);
  if(rs == SOCKET_ERROR) {
    printf("send failed with error: %d\n", WSAGetLastError());
    closesocket(mysocket);
    WSACleanup();
    return 1;
  }

  printf("Bytes Sent: %ld\n", rs);
  // rs = shutdown(mysocket, SD_SEND);
  if(rs == SOCKET_ERROR) {
    printf("shutdown failed with error: %d\n", WSAGetLastError());
    closesocket(mysocket);
    WSACleanup();
    return 1;
  }

  do
  {
    /* code */
    rs = recv(mysocket, recvbuf, recvbuflen, 0);
    if(rs > 0)
      printf("Bytes received: %d\n", rs);
    else if(rs == 0)
      printf("Connection closed\n");
    else
      printf("recv failed with error: %d\n", WSAGetLastError());
  } while (rs > 0);

  closesocket(mysocket);
  WSACleanup();
  return 0;
}


#undef UNICODE

#define _WIN32_WINNT 0x501

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// Need to link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

using namespace std;
int main(int argc, char **argv)
{

  WSADATA wsa;
  struct addrinfo *result = nullptr, *ptr = nullptr, hints;
  string message = "";
  string sent_message = "";

  int i_rs = 0;

  i_rs = WSAStartup(MAKEWORD(2,2), &wsa);
  if(i_rs != 0) {
    cout << "WSA failed with error " << i_rs << endl;
    return 1;
  }

  

  return 0;
}

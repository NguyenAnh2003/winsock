#include<iostream>
#include<winsock2.h>
using namespace std;

#define PORT 9099

void println(string text);

// Running : g++ -o D:\network\winsock-C\output\server server.cpp -lws2_32
// Running : ./output/server

struct sockaddr_in srv;
fd_set fr, fw, fe;

int main() {
  int nRet = 0;
  //init WSA var
  WSADATA ws;
  if(WSAStartup(MAKEWORD(2,2), &ws) < 0) {
    println("WSA failed to init");
  } else {
    println("WSA inited");
  }
  //init socket
  int nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(nSocket < 0) {
    println("Socket not opened");
  } else {
    println("Socket opened sucessfully");
  }
  srv.sin_family = AF_INET;
  srv.sin_port = htons(PORT);
  srv.sin_addr.s_addr = inet_addr("127.0.0.1");
  srv.sin_addr.s_addr = INADDR_ANY;
  memset(&srv.sin_zero, 0, 8);
  
  //bind socket to local port
  nRet = bind(nSocket, (sockaddr*)&srv, sizeof(sockaddr));
  if(nRet < 0) {
    println("Failed to bind local port");
    exit(EXIT_FAILURE);
  } else {
    println("Bind Success...");
  }
  //listen the req from client (queues the requests)
  nRet = listen(nSocket, 5);
  if(nRet < 0) {
    println("Failed to listen");
  } else {
    println("listenning");
  }
  //keep waiting for new reqs and proceed as per the req
  int n = 100;
  for(int nIndex = 0; nIndex < 64; nIndex++) {
    FD_SET(n, &fr);
    n++;
  }
  cout << fr.fd_count << endl;
  for (int nIndex = 0; nIndex < 64; nIndex++)
  {
    /* code */
    cout << fr.fd_array[nIndex];
  }
  
  return 0;
}

void println(string text)
{
  cout << text << endl;
}

#include<iostream>
#include<winsock2.h>
using namespace std;

#define PORT 9099

void println(string text);


// Running : g++ -o D:\network\winsock-C\output\server server.cpp -lws2_32
// Running : ./output/server

struct sockaddr_in srv;
fd_set fr, fw, fe;
int nSocket;
int nMaxFd;
int nArrClient[5];


void processReq() {
  // new connection req
  if(FD_ISSET(nSocket, &fr)) {
    int nLen = sizeof(struct sockaddr);
    int nClientSocket = accept(nSocket, NULL, &nLen);
    if(nClientSocket > 0) {
      // 
      int i;
      for(int i = 0; i<5; i++) {
        if(nArrClient[i] == 0) {
          nArrClient[i] = nClientSocket;
          send(nClientSocket, "Got the connection");
          break;
        }
      }
      if(i == 5) {
        println("No space for new connection");
      }
    }
  }
}

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
  nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(nSocket < 0) {
    println("Socket not opened");
    WSACleanup();
    exit(EXIT_FAILURE);
  } else {
    println("Socket opened sucessfully");
  }
  srv.sin_family = AF_INET;
  srv.sin_port = htons(PORT);
  srv.sin_addr.s_addr = inet_addr("127.0.0.1");
  srv.sin_addr.s_addr = INADDR_ANY;
  memset(&srv.sin_zero, 0, 8);

  // optval = 0 means blocking and != 0 means non blocking
  // u_long optval = 1;
  // nRet = ioctlsocket(nSocket, FIONBIO, &optval);
  // Checking
  // println(nRet != 0 ? "ioctlsocket call failed"  "ioctlsocket call passed");

  //setsockopt
  int nOptVal = 0;
  int nOptLen = sizeof(nOptVal);
  nRet = setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&nOptVal, nOptLen);
  if(!nRet) {
    println("setsockopt call success");
  } else {
    println("setscockopt call failed");
    WSACleanup();
    exit(EXIT_FAILURE);
  }

  //bind socket to local port
  nRet = bind(nSocket, (sockaddr*)&srv, sizeof(sockaddr));
  if(nRet < 0) {
    println("Failed to bind local port");
    WSACleanup();
    exit(EXIT_FAILURE);
  } else {
    println("Bind Success...");
  }
  //listen the req from client (queues the requests)
  nRet = listen(nSocket, 5);
  if(nRet < 0) {
    println("Failed to listen");
    WSACleanup();
    exit(EXIT_FAILURE);
  } else {
    println("listenning");
  }
  nMaxFd = nSocket;
  struct timeval tv;
  tv.tv_sec = 1;
  tv.tv_usec = 0;
  
  FD_ZERO(&fr);
  FD_ZERO(&fw);
  FD_ZERO(&fe);

  FD_SET(nSocket, &fr);
  FD_SET(nSocket, &fe);

  while (true)
  {  
    cout << "Before select call: " << fr.fd_count << endl;

    //keep waiting for new reqs and proceed as per the req
    nRet = select(nMaxFd+1, &fr, &fw, &fe, &tv); 
    /*
    select used to detect when data is available to read from a socket
    */
    if(nRet > 0) {
      // someone connects with a message over a dedicated connection

    } else if(nRet == 0) {
      // No connection
      cout << "Nothing on port " << PORT << endl;
    } else {
      println("Failed");
      WSACleanup();
      exit(EXIT_FAILURE);
    }
    cout << "After select call: " << fr.fd_count << endl;
    Sleep(2000);
  }

  return 0;
}

void println(string text)
{
  cout << text << endl;
}

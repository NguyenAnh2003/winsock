### docs
https://wiki.netbsd.org/examples/socket_programming/
https://www.keil.com/pack/doc/mw6/Network/html/using_network_sockets_bsd.html
https://www.youtube.com/watch?v=bqj4dWG7v3c&list=PLhnN2F9NiVmAMn9iGB_Rtjs3aGef3GpSm
https://learn.microsoft.com/en-us/windows/win32/winsock/complete-server-code

Non-blocking https://www.scottklement.com/rpg/socktut/nonblocking.html


### Basic mechanisms of client-server
1. client app send a request to server
2. server app returns a reply
3. Some of the basic data communications between client and server
  - File transfer
  - Web page
  - echo


### Server socket
1. create socket
2. bind to address - what port?
3. listen - wait for connection to be established
4. accept - acpt connection from client
5. send/recv - read and write for a file
6. shutdown
7. close - releases data

### Client socket
1. create a socket
2. bind - unnecessary
3. connect to server
4. send/recv
5. shutdown
6. closes - releases data

### Run
```C++
Server running
g++ -o D:\network\winsock-C\output\myserver ./baisc/server_basic.cpp -lws2_32
./output/myserver  

Client running
g++ -o D:\network\winsock-C\output\myclient ./baisc/client_basic.cpp -lws2_32
./output/myclient
```

### Blocking and Non-Blocking(NIO)
#### Blocking
a blocking call does not return to ur program until the event you requested has been completed.
For example, if u issue a blocking recvform() call, the call does not return to ur program until 
data is available from the other socket application

#### Non-blocking
By default, TCP sockets are in "blocking" mode. For example, when you call recv() to read from a stream, control isn't returned to your 
program until at least one byte of data is read from the remote site. This process of waiting for data to appear is referred to as 
"blocking". The same is true for the write() API, the connect() API, etc. When you run them, the connection "blocks" until the operation 
is complete





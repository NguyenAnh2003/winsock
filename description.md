### docs
https://wiki.netbsd.org/examples/socket_programming/
https://www.keil.com/pack/doc/mw6/Network/html/using_network_sockets_bsd.html
https://www.youtube.com/watch?v=bqj4dWG7v3c&list=PLhnN2F9NiVmAMn9iGB_Rtjs3aGef3GpSm
https://learn.microsoft.com/en-us/windows/win32/winsock/complete-server-code

Non-blocking https://www.scottklement.com/rpg/socktut/nonblocking.html


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

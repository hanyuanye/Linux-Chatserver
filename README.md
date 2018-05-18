# LinuxServer
Linux TCP/IP socket code. To run the client, open the terminal and enter gcc client.c -o client. Then run ./client port where port is a number from 1024 to 65536. To run the server, enter either g++ chatserver.cpp -o chatserver or gcc server.c -o server. To run the server, run either ./chatserver port or ./server port.

Chatserver.cpp allows for communication between different clients using 1 server as the in between. It uses the command select() to see activities and respond accordingly. 

Server.c uses fork() to spawn new processes which can communicate with each incoming client seperately. 

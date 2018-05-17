# LinuxServer
Linux TCP/IP socket code. To run the client, open the terminal and enter gcc client.c -o client. To run the server, enter either g++ chatserver.cpp -o chatserver or gcc server.c -o server. 

Chatserver.cpp allows for communication between different clients using 1 server as the in between. It uses the command select() to see activities and respond accordingly. 

Server.c uses fork() to spawn new processes which can communicate with each incoming client seperately. 

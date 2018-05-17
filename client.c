#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	int socketfd, port, code;
	struct sockaddr_in serv_addr;
	struct hostent* server;
	char buffer[256];
	if (argc < 3) {
		printf("Not enough args");
		return 0;	
	}
	
	port = atoi(argv[2]);
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0) {
		printf("Error socket %d", errno);	
		return 0;
	}
	server = gethostbyname(argv[1]);
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char*)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(port);
	
	if ((connect(socketfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr))) < 0) {
		printf("Error connect %d", errno);
		return 0;
	}
	
	printf("Enter msg");
	bzero(buffer, 256);
	fgets(buffer, 255, stdin);
	code = write(socketfd, buffer, 255);
	if (code < 0) return 0;
}

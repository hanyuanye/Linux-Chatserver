#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>


int main(int argc, char *argv[]) {
	int socketfd = (AF_UNIX, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr, peer_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	if (argc < 2) {
		printf("Not enough arguments");
		return 0;
	}
	int port = atoi(argv[1]);
	serv_addr.sin_family = AF_UNIX;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	
	if (bind(socketfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("Error on bind");
		return 0;
	}
	listen(socketfd, 5);
	int peerlen = sizeof(peer_addr);
	int newSocketfd = accept(socketfd, (struct sockaddr *) &peer_addr, &peerlen);
	if (newSocketfd < 0) {
		printf("Error on accept");
	}
	char buffer[256];
	bzero(buffer, 256);
	int code = read(newSocketfd, buffer, 255);
	if (code < 0) {
		printf("Error reading");
	}
	printf("%s", buffer);
	code = write(newSocketfd, "message", 7);
	if (code < 0) {
		printf("Error writing");	
	}
}
	
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>

void respond(int socketfd) {
	char buffer[256];
	int code = read(socketfd, buffer, 255);	
	printf("%s", buffer);
	
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Not enough arguments");
		return 0;
	}
	int socketfd;
	if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Error %d", errno);
		return 0;
	}
	struct sockaddr_in serv_addr, peer_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	int port = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	int bound = bind(socketfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	if (bound < 0) {
		printf("Error on bind %d", errno);
		return 0;
	}
	listen(socketfd, 5);
	int peerlen = sizeof(peer_addr);
	while (1) {
		int newSocketfd = accept(socketfd, (struct sockaddr *) &peer_addr, &peerlen);
		int pid = fork();
		if (pid == 0) {
			close(socketfd);
			respond(newSocketfd);
			exit(0);
		}
	}
}
	
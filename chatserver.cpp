#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>

class Server {
public:
	void init();
private:
	void acceptRequests();
	struct sockaddr_in serv_addr, peer_addr;
	int master_socket;
	fd_set readfds;
	std::vector<int> client_socket;
};

void Server::init() {
	int port;
	std::cin >> port;
	if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cout << "Error socket" << std::endl;
	}
	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(master_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		std::cout << "Error binding " << errno << std::endl;
	}
	
	listen(master_socket, 5);
	acceptRequests();
}

void Server::acceptRequests() {
	unsigned peerlen = sizeof(peer_addr);
	while (true) {
		FD_ZERO(&readfds);
		FD_SET(master_socket, &readfds);
		int max_sd = master_socket;
		for (int i = 0; i < client_socket.size(); i++) {
			int sd = client_socket[i];
			if (sd > 0) {
				FD_SET(sd, &readfds);	
			}
			if (sd > max_sd) {
				max_sd = sd;	
			}
		}
		
		int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
		if (FD_ISSET(master_socket, &readfds)) {
			int connfd = accept(master_socket, (struct sockaddr*) &peer_addr, &peerlen);
			std::cout << "New Connection" << std::endl;
			client_socket.push_back(connfd);
			continue;
		}
		
		for (int i = 0; i < client_socket.size(); i++) {
			char buffer[1024];
			int sd = client_socket[i];
			if (FD_ISSET(sd, &readfds)) {
				if ((read(sd, buffer, 1024)) == 0) {
					std::cout << "disconnected" << std::endl;	
					close(sd);
					client_socket.erase(client_socket.begin() + i);	
				}
				else {
					std::string msg = buffer;
					std::cout << msg << std::endl;	
				}
			}
		}
	}
}

int main() {
	Server server;
	server.init();
}
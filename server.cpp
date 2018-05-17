#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

int main() {
	int serverSocket = socket(AF_LOCAL, SOCK_STREAM, 0);
	struct sockaddr_un server_addr;
	if (serverSocket < 0) {
		std::cout << "Error" << std::endl;
	}
	
	
}
	
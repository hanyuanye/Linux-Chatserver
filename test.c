#include <stdlib.h>

//Test Driver code for connecting clients to server
int main() {
	for (int i = 0; i < 10; i++) {
		system("xfce4-terminal --command=\"./client 8000\"");
	}
}
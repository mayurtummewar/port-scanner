#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sock < 0) {
		perror("Socket creation failed");
		return 1;
	}

	struct sockaddr_in server;
	
	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	if (inet_pton(AF_INET, "142.250.195.14", &server.sin_addr) <= 0) {
		perror("Invalid Address");
		close(sock);
		return 1;
	}

	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
		perror("Connection Unsuccessful\n");
	} else {
		printf("Connection Successful!\n");
	}

	close(sock);
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {

	struct sockaddr_in target;
	int sock;
	int port;
	
	target.sin_family = AF_INET;

	inet_pton(AF_INET, "127.0.0.1", &target.sin_addr);
	printf("scanning ports on 127.0.0.1...\n");

	for (port = 1; port <= 1024; port++) {
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sock < 0) {
		perror("Socket creation failed");
		continue;
	}

	target.sin_port = htons(port);
	if (connect(sock, (struct sockaddr *)&target, sizeof(target)) == 0) {
		printf("Port %d is open\n", port);
	}

	close(sock);
	}
	return 0;
}

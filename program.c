#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {

	struct sockaddr_in target;
	memset(&target, 0, sizeof(target));
	int sock;
	int port, start_port, end_port;
	if (argc != 4) {
		printf("error : 3 arguments expected");
		return 1;
	}

	start_port = strtol(argv[2], NULL, 10);
	if (start_port < 1 || start_port > 65535) {
		perror("invalid start_port");
		return 1;
	}
	end_port = strtol(argv[3], NULL, 10);
	if (end_port < 1 || end_port > 65535) {
		perror("invalid end_port");
		return 1;
	}

	target.sin_family = AF_INET;

	if (inet_pton(AF_INET, argv[1], &target.sin_addr) != 1) {
		perror("invalid ip");
		return 1;
	}
	printf("scanning from port %d to port %d on ip : %s\n", start_port, end_port, argv[1]);

	for (port = start_port; port <= end_port; port++) {
		sock = socket(AF_INET, SOCK_STREAM, 0);
		
		if (sock < 0) {
			perror("Socket creation failed");
			continue;
		}

		struct timeval timeout;
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		
		setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

		target.sin_port = htons(port);
		if (connect(sock, (struct sockaddr *)&target, sizeof(target)) == 0) {
			printf("Port %d is open\n", port);
		}

		close(sock);
	}
	return 0;
}

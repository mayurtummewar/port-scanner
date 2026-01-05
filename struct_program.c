#include<stdio.h>

struct Server {
	char ip[16];
	int port;
};

int main() {
	struct Server s;
	struct Server *ptr = &s;

	snprintf(ptr->ip, sizeof(ptr->ip), "127.0.0.1");
	ptr->port = 80;

	printf("Server IP    : %s\n", ptr->ip);
	printf("Server port  : %d\n", ptr->port);

	return 0;
}

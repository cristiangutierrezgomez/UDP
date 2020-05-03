/**
 * This file implements a "UDP ping server".
 *
 * It basically waits for datagrams to arrive, and for each one received, it responds to the original sender
 * with another datagram that has the same payload as the original datagram. The server must reply to 3
 * datagrams and then quit.
 *
 * Test with:
 *
 * $ netcat localhost 8080
 * ping
 * ping
 * pong
 * pong
 *
 * (assuming that this program listens at localhost port 8080)
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT "8080"
#define BACKLOG 3
#define BUFSIZE 1024

int main(int argc, char **argv) 
{
	(void) argc; // This is how an unused parameter warning is silenced.
	(void) argv;

	int i = 0;
	
	int s, client_address_size, message;
   	struct sockaddr_in client, server;

	char buffer_recv[BUFSIZE], buffer_send[BUFSIZE];
	s = socket(AF_INET, SOCK_DGRAM, 0);

	server.sin_family      = AF_INET;
   	server.sin_port        = htons(8080);
   	server.sin_addr.s_addr = INADDR_ANY;

	bind(s, (struct sockaddr *)&server, sizeof(struct sockaddr));
	client_address_size = sizeof(struct sockaddr);	

	while (i < 3)
	{
   	message = recvfrom(s, buffer_recv, sizeof(buffer_recv), 0, (struct sockaddr *)&client, &client_address_size);

	buffer_recv[message] = '\0'; 

	sendto(s, buffer_recv, strlen(buffer_recv), 0, (const struct sockaddr *)&client,client_address_size);

	i = i + 1;
	}
	close(s); 
	return 0;
}

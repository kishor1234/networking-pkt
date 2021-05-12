// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

// Driver code
int main()
{
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from client";
	struct sockaddr_in servaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	while (1)
	{
		int n, len;
		//buffer[MAXLINE]

		bzero(buffer, MAXLINE);
		explicit_bzero(buffer, MAXLINE);
		//buffer[MAXLINE]="";
		n = 0;
		printf("Message for Server : ", buffer);
		// copy server message in the buffer
		while ((buffer[n++] = getchar()) != '\n')
			;
		sendto(sockfd, (const char *)buffer, strlen(buffer),
			   MSG_CONFIRM, (const struct sockaddr *)&servaddr,
			   sizeof(servaddr));
		printf("Hello message sent. %s\n", buffer);
		bzero(buffer, MAXLINE);
		explicit_bzero(buffer, MAXLINE);
		//printf("empty. %s\n", buffer);
		//buffer[MAXLINE]="";
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,
					 MSG_WAITALL, (struct sockaddr *)&servaddr,
					 &len);
		buffer[n] = '\0';
		//printf("Server : %s\n", buffer);
		printf("From Server: %s\t \n", buffer);
		bzero(buffer, MAXLINE);
		explicit_bzero(buffer, MAXLINE);
	}
	close(sockfd);
	return 0;
}

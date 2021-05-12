// Server side implementation of UDP client-server model
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
	char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);

	// Bind the socket with the server address
	if (bind(sockfd, (const struct sockaddr *)&servaddr,
			 sizeof(servaddr)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		int len, n;

		len = sizeof(cliaddr); //len is value/resuslt
		bzero(buffer, MAXLINE);
		explicit_bzero(buffer, MAXLINE);
		//buffer[MAXLINE]="";
		//printf("BefoClient : %s\n", buffer);
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,
					 MSG_WAITALL, (struct sockaddr *)&cliaddr,
					 &len);
		//buffer[n] = '\0';
		printf("Client : %s \n", buffer);
		char s_up[strlen(buffer)-1];
		bzero(s_up, strlen(buffer)-1);
		explicit_bzero(s_up, strlen(buffer));
        for (int a = 0; a < strlen(buffer)-1; a++)
        {
            // Storing the change: Use the temp array while casting to uppercase.
            s_up[a] = toupper(buffer[a]);
			
			
        }
		
		printf("Server Replay : %s\n", s_up);
		sendto(sockfd, (const char *)s_up, strlen(s_up),
			   MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
			   len);
		printf("Hello message sent.\n");
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SIZE 1025

void transfer_data(FILE* fo, int sockfd, struct sockaddr_in addr)
{
	int o;
	char buffer[SIZE];
	
	//Process of data sending
	while (fgets(buffer, SIZE, fo) != NULL)
	{
		printf("[Send] Data is transfering: %s", buffer);
		o = sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*) &addr, sizeof(addr));
		if(o == -1)
		{
			perror("[Error!] Data Sending failed.");
			exit(1);
		}
		bzero(buffer, SIZE);
	}
	
	//Terminate session
	strcpy(buffer, "End");
	sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*) &addr, sizeof
	(addr));
	
	fclose(fo);
}

int main(void)
{
	//To define the ip and the port
	char *ip = "192.168.158.10";
	const int port = 8888;
	
	//Variables define
	int server_sockfd;
	struct sockaddr_in server_addr;
	char *filename = "clientFTP.txt";
	FILE *fo = fopen(filename, "w");
	
	//UDP socket created
	server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(server_sockfd < 0)
	{
		perror("[Error!] Socket not found");
		exit(1);
	}
    server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	server_addr.sin_addr.s_addr = inet_addr(ip);
	
	//Read file
	if(fo == NULL)
	{
		perror("[Error!] File reading failed ");
		exit(1);
	}
	
	//Data sending
	transfer_data(fo, server_sockfd, server_addr);
	
	printf("[Success] Data transfer complete.\n");
	printf("[Shut down]Disconnect the data.\n");
	
	close(server_sockfd);
	
	return 0;
}

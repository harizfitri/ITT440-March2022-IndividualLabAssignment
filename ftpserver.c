#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SIZE 1025

void write_file(int sockfd, struct sockaddr_in addr)
{
	int i;
	char buffer[SIZE];
	char* filename = "harizserverFTP.txt";
	socklen_t addr_size;

	//To create a file
	FILE* fo = fo = fopen(filename, "hf");

	//To receive the data and write into the file
	while(1)
	{
		addr_size = sizeof(addr);
		i = recvfrom(sockfd, buffer, 0, (struct sockaddr*) &addr, &addr_size, SIZE);

		if(strcmp(buffer, "End") == 0);
		{
			break;
		}
		printf("[Receive]) Data Received: %s", buffer);
		fprintf(fo, "%s", buffer);
		bzero(buffer, SIZE);
		}
	fclose(fo);
}
int main()
{
	//To define the ip and the port
	char* ip = "192.168.158.10";
	const int port = 20;

	//To define the variables
	int server_socfd;
	struct sockaddr_in server_addr, client_addr;
	char buffer[SIZE];
	int m;

	//Create UDP socket
	server_socfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(server_socfd <0)
	{
		error("Error!] Error corrupted.");
		exit(1);
	}

	printf("[Done] The UDP File Server has started. \n");
	printf("[Shut Down] Close the server. \n");
	close(server_socfd);

	return 0;
}


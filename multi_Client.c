/* Socket programming for client */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9090

int main()
{

	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[256];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0)
	{
		printf("[-]Error in connection.\n");
		exit(1);
	}
	else
	{
	printf("[+]Client Socket is created.\n");
        }
        
	bzero(&serverAddr, sizeof(serverAddr));
	//memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	
	if(ret != 0)
	{
		printf("[-]Error in connection.\n");
		exit(1);
	}
	
	else
	{
	printf("[+]Connected to Server.\n");
        }
       
	while(1)
	{
		bzero(buffer, sizeof(buffer));
		//printf("Client: \t");
		printf("To server: ");
		//scanf("%s", &buffer[0]);
		int n=0;
		while ((buffer[n++] = getchar()) != '\n');
		write(clientSocket, buffer, sizeof(buffer));
		//send(clientSocket, buffer, strlen(buffer), 0);
		
               
               //condition to convert the lower case to upper cases received from client
		
		int i=0;
		for(i=0;buffer[i]!='\0';i++)
		{
		
		if (buffer[i] >= 'a' && buffer[i] <= 'z')
		{
			buffer[i]-=32;
		}
		
		else if(buffer[i] >= 'A' && buffer[i] <= 'Z')
		{
		buffer[i]+=32;
		}
		}
		
               printf("\tThe String Echoed from client : %s", buffer);

		
		if(recv(clientSocket, buffer, 1024, 0) < 0)
		{
			printf("[-]Error in receiving data.\n");
		}
		else
		{
			printf("Server: \t%s\n", buffer);
		} 
	}


}

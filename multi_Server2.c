/* Socket programming for server */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 9090
int cnt, i, k=1, cl1_wr, cl2_wr, cl3_wr, l;
int *pid_arr;

//sem_t s;
int req_arr[]={0,1,2,3};
int num;
int back=0;
	int newSocket;
	char buffer[256];

int main()
{
//	sem_init(&s, 3, 1);

	int sockfd, ret;
	struct sockaddr_in serverAddr;
        struct sockaddr_in newAddr;

	socklen_t addr_size;

	pid_t childpid;
//	int i=0, cnt=0;
//	int *pid_arr;
	int ne_cnt=0;

	pid_arr = (int*)malloc(sizeof(int));

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0)
	{
		printf("Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 4444);

	if(listen(sockfd, 10) == 0)
	{
		printf("[+]Listening....\n");
	}

	else
	{
		printf("[-]Error in binding.\n");
	}


	while(1)
	{
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		back= newSocket;
		cnt++;   

		if(newSocket < 0)
		{
			exit(1);
		}
		pid_arr[i] = ntohs(newAddr.sin_port);
		pid_arr[i] = ntohs(newAddr.sin_port); 
		if((childpid = fork()) == 0)
		{
			printf("without array %d\n", ntohs(newAddr.sin_port));
			pid_arr = (int*) realloc(pid_arr, (cnt)*sizeof(int));
			pid_arr[cnt] = ntohs(newAddr.sin_port);
			close(sockfd);

				bzero(buffer, sizeof(buffer));



				read (newSocket,buffer,sizeof(buffer));

				//condition to convert the lower case to upper cases received from client
				for(int i=0;buffer[i]!='\0';i++)
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

				// print buffer which contains the client contents
				printf("From client %d : %s\t To client : ",newSocket, buffer); 
				printf("From client %d : %s\t To client : ",cnt, buffer);  

				printf("\n");
				// This function is used to set all the socket structures with null values
				bzero(buffer, sizeof(buffer));
				int n = 0;

				while ((buffer[n++] = getchar()) != '\n');
			 
		/*		if(cnt == 1 ){
					printf("Hii writing on cli3\n");
					write(6, buffer, sizeof(buffer));
				}
			        else if(cnt == 2 )
                                {
					printf("Hii writing on cli2\n");
					write(5, buffer, sizeof(buffer));
				}
				else if(cnt ==3)
				{
					printf("Hii writing on cli1\n");
					write(4, buffer, sizeof(buffer));

				} */
				write(newSocket, buffer, sizeof(buffer));

		}

	}
	close(newSocket);


	return 0;
}


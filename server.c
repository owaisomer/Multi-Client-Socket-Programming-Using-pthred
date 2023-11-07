#include <stdio.h>
#include <unistd.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <pthread.h>
#include <arpa/inet.h>

#define MAX 100  //message length
#define PORT 5600 

#define SA struct sockaddr


void *handle_client(void *arg) {
	int clientSockFD = *((int *)arg);
	char buff[MAX]; 
	int n; 

	while(1) { 
		

		bzero(buff, MAX); 

 
		read(clientSockFD, buff, sizeof(buff)); 
		

		printf("Message from client: %s\n", buff); 
		
		if (strncmp("exit", buff, 4) == 0) { 
			printf("Disconnecting client.\n"); 
			write(clientSockFD, "exit", sizeof("exit")); 
			break; 
		}

		printf("Enter the message for client: "); 
		bzero(buff, MAX); 
		n = 0; 

		while ((buff[n++] = getchar()) != '\n'); 


		write(clientSockFD, buff, sizeof(buff)); 


		 
	}


	close(clientSockFD);
	pthread_exit(NULL);
}


int main()
{

	int serverSockFD, clientSockFD, len; 
	struct sockaddr_in serverAddr, clientAddr; 
	pthread_t thread_id;

	serverSockFD = socket(AF_INET, SOCK_STREAM, 0); 
	if (serverSockFD == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	
	bzero(&serverAddr, sizeof(serverAddr)); 


	serverAddr.sin_family = AF_INET; 
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); 	
	serverAddr.sin_port = htons(PORT); 
	
	
	if ((bind(serverSockFD, (SA*)&serverAddr, sizeof(serverAddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 



	if ((listen(serverSockFD, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	
	len = sizeof(clientAddr); 

	while(1)
	{
	
		clientSockFD = accept(serverSockFD, (SA*)&clientAddr, &len); 
		if (clientSockFD < 0) { 
			printf("server acccept failed...\n"); 
			exit(0); 
		} 
		else
		{
			printf("server has acccepted a new client...\n");

		}
		
		int client_thread = pthread_create(&thread_id, NULL, handle_client, (void *)&clientSockFD);

		if (client_thread != 0) {
		    perror("could not create thread");
		    return 1;
		}


		pthread_detach(thread_id);

	
	} 


	close(serverSockFD); 

}
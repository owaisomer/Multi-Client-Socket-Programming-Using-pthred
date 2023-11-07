#include <stdio.h> 
#include <stdlib.h> 
#include <netdb.h> 
#include <arpa/inet.h> 

#include <unistd.h> 
#include <string.h> 
#include <sys/socket.h> 

#define MAX 100  //message length
#define PORT 5600 //server process port

#define SA struct sockaddr 

/* Function designed for chat between client and server. 
   input: sockfd- server socket file descriptor */
void chatFunction(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 
	while(1) { 
		
		bzero(buff, sizeof(buff)); 
		// get message for server from client side user
		printf("Enter the message: "); 
		n = 0; 
		
		while ((buff[n++] = getchar()) != '\n'); 
		
		write(sockfd, buff, sizeof(buff)); 
		
		bzero(buff, sizeof(buff)); 
		
		read(sockfd, buff, sizeof(buff)); 
				
		// if msg contains "exit" then client exits and chat ends. 
		if ((strncmp(buff, "exit", 4)) == 0) { 
			printf("Client terminating upon server's exit message.\n"); 
			break; 
		}
		printf("Message from Server : %s", buff); 
	} 
} 

int main() 
{ 
	int sockfd; 
	struct sockaddr_in servaddr, clientAddr; 

	// create client socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("SERVER IP ADDRESS GOES HERE...");
	servaddr.sin_port = htons(PORT);
	
	// connect the client socket to server socket 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("connection with the server failed...\n"); 
		exit(0); 
	} 
	else
		printf("connected to the server..\n"); 

	// function for chat 
	chatFunction(sockfd); 

	// close the socket 
	close(sockfd); 
} 

// Collin Paiz
// Lab 3 - Step 2
// 27 January 2022
// This C program is for a TCP server that accepts a client connection and allows for file transfer to the client
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUF_SIZE 80

//Declare socket file descriptor.
int sockfd, connfd, rb;

//Declare receiving and sending buffers of size 1k bytes
char rbuf[BUF_SIZE], sbuf[BUF_SIZE];

//Declare server address to which to bind for receiving messages and client address to fill in sending address
struct sockaddr_in servAddr, clienAddr;
int sin_size = sizeof(clienAddr);

//Connection handler for servicing client request for file transfer
void* connectionHandler(void* sock){
   //declare buffer holding the name of the file from client
   char filename[1024];
   
   //Connection established, server begins to read and write to the connecting client
   printf("Connection Established with client IP: %s and Port: %d\n", inet_ntoa(clienAddr.sin_addr), ntohs(clienAddr.sin_port));
   
	//receive name of the file from the client
   
   bzero(filename, 256);
   printf("read");
   rb = read(sock, filename, sizeof(filename));

   printf("%s \n", filename);
	
   //open file and send to client
   FILE *src = fopen(filename, "r");	// opens a file for reading
	if (src == NULL) { // fopen() error checking
		fprintf(stderr, "unable to open %s for reading: %i\n", filename, errno);
		exit(0);
	}

   //read file and send to connection descriptor
	while(rb = fread(rbuf, 1, sizeof(rbuf), src)) {
      send(sock, rbuf, sizeof(rbuf), 0);
	}
   
   printf("File transfer complete\n");
   
   //close file
   fclose(src);
    
   //Close connection descriptor
   close(sock);
   
   return 0;
}


int main(int argc, char *argv[]){
   //Get from the command line, server IP, src and dst files.
   if (argc != 2){
      printf ("Usage: %s <port #> \n",argv[0]);
      exit(0);
   } 

   //Open a TCP socket, if successful, returns a descriptor
   if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
      perror("Failure to create socket");
      exit(0);
   }

   //Setup the server address to bind using socket addressing structure
   servAddr.sin_family = AF_INET;
   servAddr.sin_port = htons(atoi(argv[1]));
   servAddr.sin_addr.s_addr = INADDR_ANY;

   //bind IP address and port for server endpoint socket 
   if (bind(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
      perror("Failure to bind server address to the endpoint socket");
      exit(0);
   }

   // Server listening to the socket endpoint, and can queue 5 client requests
   printf("Server listening/waiting for client at port %d\n", atoi(argv[1]));
   listen(sockfd, 5);

   //Server accepts the connection and call the connection handler
   if ((connfd = accept(sockfd, (struct sockaddr *)&clienAddr, (socklen_t *)&sin_size)) < 0){
      perror("Failure to accept connection to the client");
      exit(1);
   }
   connectionHandler(connfd);

   //close socket descriptor
   close(sockfd);

   return 0;
}
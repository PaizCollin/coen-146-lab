// Collin Paiz
// Lab 3 - Step 1
// 27 January 2022
// This C program is for a TCP client that connects to the server and downloads a file from the server
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <arpa/inet.h>

#define BUF_SIZE 80

int main(int argc, char *argv[]){
    //Get from the command line, server IP, src and dst files.
    if (argc != 5){
		  printf ("Usage: %s <ip of server> <port #> <src_file> <dest_file>\n",argv[0]);
		  exit(0);
    }

    //Declare socket file descriptor and buffer
    int sockfd = 0;
    char rbuf[BUF_SIZE], sbuf[BUF_SIZE];

    //Declare server address to accept
    struct sockaddr_in servAddr;

    //Declare host
    struct hostent *host;

    //get hostname
    host = (struct hostent*)gethostbyname(argv[1]);

    //Open a socket, if successful, returns
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      perror("Failure to create socket");
      exit(0);
    }
 
    //Set the server address to send using socket addressing structure
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(atoi(argv[2]));

    if(inet_pton (AF_INET, argv[1], &servAddr.sin_addr) <= 0) {
      printf ("inet_pton error occured\n");
      exit(0);
    }

    //Connect to the server
    if(connect(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
      perror("Failure to connect to the server");
      exit(0);
    }

    //Client sends the name of the file to retrieve from the server
    char *hi = "hi";
    //int n = 
    send(sockfd, argv[3], strlen(argv[3]), 0);
    printf("file name sent\n");

    //Client begins to write and read from the server
    int bytes;
    
    FILE *fsrc = fopen(argv[3], "rp");
    if(fsrc == NULL) {
      printf("Error opening source file\n");
      exit(0);
    }

    printf("src file opened\n");

    FILE *fdst = fopen(argv[4], "w");
    while(bytes = read(sockfd, rbuf, sizeof(rbuf))) {
      fwrite(rbuf, sizeof(rbuf), 1, fdst);
    }

    //Close socket descriptor
    fclose(fsrc);
    close(sockfd);
    
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int errorCheck(int retval, const char * message){
    if(retval == -1){
		perror(message);  
		exit(EXIT_FAILURE); 
	}
    return retval;
}

// thread to constantly read incoming data from server
void * doRecieving(void * sockID){

	int clientSocket = *((int *) sockID);

	while(1){

		char data[1024];
		int read = recv(clientSocket,data,1024,0);
        if (read <= 0) {
            // got error or connection closed by client
            if (read < 0)  {
                perror("recv");
            }
            close(clientSocket); // bye!
            exit(0);
        }
        else {
            printf("%s", data);
        }
	}

}

int main(int argc, char *argv[]){

    struct sockaddr_in serverAddr;

    // check command line arguments
    if(argc != 2){
        printf("\nUsage: %s <ip of server> \n", argv[0]);
        return 1;
    } 

	int clientSocket;

    // create stream socket
    errorCheck((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) ,"Cannot create socket");

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(2001);

    // convert command line argument to IP address
    if ( (inet_pton(AF_INET, argv[1], &serverAddr.sin_addr)) <= 0){
        printf("Probably incorrect IP address input\n");
        exit(EXIT_FAILURE);
    }

    // connect to server
	errorCheck( (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr))), "Cannot connect" );

	printf("Connection established ............\n");

    // create thread
	pthread_t thread;
	pthread_create(&thread, NULL, doRecieving, (void *) &clientSocket );

    // get input
	while(1){
		char input[1024];
		fgets(input, 1024, stdin);
        if (input[0] != '\n'){
            send(clientSocket,input,1024,0);
        }
	}
    return 0;
}

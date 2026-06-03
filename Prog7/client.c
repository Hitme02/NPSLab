#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<errno.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
	int sd, acpt, len, bytes, port;
	char send1[50], receiv[50];
	struct sockaddr_in server, client;
	if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Error in socket\n");
		exit(0);
	}
	bzero(&server, sizeof(server));

	server.sin_family = AF_INET;
	server.sin_port = htons(15002);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if(connect(sd, (struct sockaddr *)&server, sizeof(server)) < 0){
		printf("Error in connection\n");
		exit(0);
	}

	while(1){
		printf("Enter the command to execute: ");
		gets(send1);
		if(strcmp(send1, "exit") != 0){
			send(sd, send1, 50, 0);
		}
		else{
			send(sd, send1, 50, 0);
			close(sd);
			break;
		}
	}
}
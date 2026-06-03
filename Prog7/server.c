#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<string.h>

int main(){
	int sd, acpt, len, bytes, port;
	char send[50], receiv[50];
	struct sockaddr_in server, client;
	if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Error in socket\n");
		exit(0);
	}
	bzero(&server, sizeof(server));

	server.sin_family = AF_INET;
	server.sin_port = htons(15002);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sd, (struct sockaddr *)&server, sizeof(server)) < 0){
		printf("Error in binding\n");
		exit(0);
	}

	if(listen(sd, 3) < 0){
		printf("Error in listening\n");
		exit(0);
	}

	if((acpt = accept(sd, (struct sockaddr *)&client, &len)) < 0){
		printf("Error in accepting\n");
		exit(0);
	}

	while(1){
		bytes = recv(acpt, receiv, 50, 0);
		receiv[bytes] = '\0';
		if(strcmp(receiv, "exit") == 0){
			close(acpt);
			close(sd);
			exit(0);
		}
		else{
			printf("Command received: %s\n", receiv);
			system(receiv);
			printf("\n");
		}
	}
}
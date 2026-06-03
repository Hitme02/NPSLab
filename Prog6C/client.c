#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>


void str_cli(FILE *fp, int sockfd, struct sockaddr *serv_address, socklen_t servlen)
{
    int bufsize = 1024, cont;
    char *buffer = malloc(bufsize);
    if (buffer == NULL)
    {
        perror("malloc");
        return;
    }
    while (fgets(buffer, bufsize, fp) != NULL)
    {
        sendto(sockfd, buffer, strlen(buffer), 0, serv_address, servlen);
        if ((cont = recvfrom(sockfd, buffer, bufsize - 1, 0, NULL, NULL)) > 0) // NULL for client address and length since we don't care about it here
        {
            buffer[cont] = '\0';
            fputs(buffer, stdout); // ECHO PRINTING..
        }
    }
    free(buffer);
    printf("\nEOF\n");
}


int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in serv_address;
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <server-ip>\n", argv[0]);
        return 1;
    }
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0)
        printf("The Socket was created\n");
    else
    {
        perror("socket");
        return 1;
    }
    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(16001);
    if (inet_pton(AF_INET, argv[1], &serv_address.sin_addr) != 1)
    {
        fprintf(stderr, "Invalid server IP address\n");
        close(sockfd);
        return 1;
    }

    str_cli(stdin, sockfd, (struct sockaddr *)&serv_address, sizeof(serv_address));
    close(sockfd);

    exit(0);
}
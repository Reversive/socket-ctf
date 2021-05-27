#include "include/client.h"

int main(int argc, char *argv[]) {
    int socket_fd;
    struct sockaddr_in address;
    if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Couldn't create socket");
        exit(EXIT_FAILURE);
    }
    bzero((char *) &address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    if (connect(socket_fd,(struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Couldn't connect to the socket");
        exit(EXIT_FAILURE);
    }
    
    int state = RUNNING;
    char buffer[BUFFERSIZE];
    while (state == RUNNING) {
        printf("Send message: ");
        bzero(buffer, BUFFERSIZE);
        fgets(buffer, BUFFERSIZE, stdin);
        int bytes_written = write(socket_fd,buffer, strlen(buffer));
        if (bytes_written < 0) {
            state = STOPPED;
            perror("Socket closed\n");
        }
    }
    return 0;
}
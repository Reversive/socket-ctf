#include "include/server.h"

int main(int argc, char *argv[]) {
    int socket_fd, connection_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);
    if(socket_fd == ERROR) {
    	perror("Socket creation failed\n");
    	exit(ERROR);
    }
    struct sockaddr_in server, client;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    if((bind(socket_fd, (sockaddr_ptr)&server, sizeof(server))) == ERROR) {
		perror("Socket bind failed\n");
		close(socket_fd);
		exit(ERROR);
    }

    if((listen(socket_fd, BACKLOG)) == ERROR) {
		perror("Socket listen failed\n");
		close(socket_fd);
		exit(ERROR);
    }

    socklen_t length = sizeof(client);
    connection_fd = accept(socket_fd, (sockaddr_ptr)&client, &length);
    if(connection_fd == ERROR) {
		perror("Socket accept failed\n");
		close(socket_fd);
		exit(ERROR);
    }
    ctf(connection_fd);
    close(socket_fd);
    return 0;
}

int check_flag(challenge_et current_challenge, char *flag) {
	if(strcmp(challenge_table[current_challenge].challenge_flag, flag) != SUCCESS) {
		printf("Respuesta incorrecta: %s\n", flag);
		sleep(RETRY_SLEEP);
		return 0;
	}
	return 1;
}

void ctf(int fd) {
    char *flag;
    size_t length = 0;
    file_ptr client_buffer = fdopen(fd, "w+");
    if(client_buffer == NULL) {
		perror("Socket accept failed\n");
		exit(ERROR);
    }
	challenge_setup();
	int current_challenge = _WELCOME;
	while (current_challenge != _LAST_CHALLENGE) {
		printf("\033[1;1H\033[2J"); // https://stackoverflow.com/questions/4062045/clearing-terminal-in-linux-with-c-code
		printf("------------- DESAFIO -------------\n");
		printf("%s\n", challenge_table[current_challenge].challenge);
		if(challenge_table[current_challenge].fn != NULL) challenge_table[current_challenge].fn();
		printf("----- PREGUNTA PARA INVESTIGAR -----\n");
		printf("%s\n", challenge_table[current_challenge].challenge_question);

		ssize_t characters_read = getline(&flag, &length, client_buffer);
		if(characters_read == ERROR) {
			perror("getline failed\n");
			exit(ERROR);
		}
		flag[characters_read - 1] = NULL_TERMINATOR;
		current_challenge += check_flag(current_challenge, flag);
	}
	printf("\033[1;1H\033[2J");
    printf("Fin\n");
}

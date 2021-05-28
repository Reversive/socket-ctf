#ifndef SERVER_H
#define SERVER_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <stdlib.h>
#include "challenge.h"
#define NULL_TERMINATOR '\0'
#define DEFAULT_PROTOCOL 0
#define PORT 8080
#define BACKLOG 2
enum code {ERROR = -1, SUCCESS = 0};
typedef struct sockaddr *sockaddr_ptr;
typedef FILE *file_ptr;
void ctf(int fd);
#endif
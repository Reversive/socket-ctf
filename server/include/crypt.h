#ifndef CRYPT_H
#define CRYPT_H
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define SMALL_BUFFER_SIZE 128
enum code {ERROR = -1, SUCCESS = 0};
uint64_t decrypt(char * out, char *in, uint64_t n);
int md5(char *str, char *out);

#endif
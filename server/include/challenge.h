#ifndef CHALLENGE_H
#define CHALLENGE_H
#include <string.h>
#include <unistd.h> 
#include <stdio.h>
#define BAD_CHALLENGE -1
#define RETRY_SLEEP 3
#define NONE 0
typedef void (*challenge_func)(void);
#define MAX_CHALLENGE_BUFFER 4096
#define MAX_ANSWER_BUFFER 256
#define BAD_FD 100
typedef struct {
    char challenge[MAX_CHALLENGE_BUFFER];
    char challenge_question[MAX_CHALLENGE_BUFFER];
    char challenge_flag[MAX_ANSWER_BUFFER];
    challenge_func fn;
} challenge_ts;

typedef enum index_challenges {
    _WELCOME = 0,
    _THE_WIRE,
    _STEGANOGRAPHY,
    _EBADF,
    _STRINGS,
    _SECTIONS,
    _FILTER
} challenge_et;
#define _LAST_CHALLENGE _FILTER
#define _CHALLENGE_AMOUNT (_LAST_CHALLENGE + 1)

extern challenge_ts challenge_table[_CHALLENGE_AMOUNT];
void challenge_register(char *challenge, char *question, challenge_func fn, char *flag);
void challenge_setup();
#endif
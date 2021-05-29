#ifndef CHALLENGE_H
#define CHALLENGE_H
#include <string.h>
#include <unistd.h> 
#include <time.h>
#include "crypt.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <math.h>
#define BAD_CHALLENGE -1
#define RETRY_SLEEP 2
#define NONE 0
typedef void (*challenge_func)(void);
typedef FILE *file_ptr;
#define BIG_BUFFER_SIZE 4096

#define BAD_FD 13
#define NO_TRACER 0


typedef struct {
    char challenge[BIG_BUFFER_SIZE];
    char challenge_question[BIG_BUFFER_SIZE];
    char challenge_flag[SMALL_BUFFER_SIZE];
    challenge_func fn;
} challenge_ts;

typedef enum index_challenges {
    _WELCOME = 0,
    _THE_WIRE,
    _STEGANOGRAPHY,
    _EBADF,
    _STRINGS,
    _SECTIONS,
    _FILTER,
    _BG_BLACK,
    _LATEX,
    _QUINE,
    _GDBME,
    _NORMAL
} challenge_et;
#define _LAST_CHALLENGE _NORMAL
#define _CHALLENGE_AMOUNT (_LAST_CHALLENGE + 1)

extern challenge_ts challenge_table[_CHALLENGE_AMOUNT];
void challenge_register(char *challenge, char *question, challenge_func fn, char *flag);
void challenge_setup();
void curious_easter_egg();
#endif
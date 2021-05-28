#include "include/challenge.h"

char * hidden_string = "too_easy\n";
static char hidden_section[] __attribute__((section(".RUN_ME"))) = {0};

int challenge_amount = NONE;
challenge_ts challenge_table[_CHALLENGE_AMOUNT];

char *challenges[_CHALLENGE_AMOUNT] = {
    "Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\nEn este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\nAdemás tendrán que investigar otras preguntas para responder durante la defensa.\nEl desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos.No basta con esperar la respuesta.\nAdemás, deberán implementar otro programa para comunicarse conmigo.\n\nDeberán estar atentos a los easter eggs.\n\nPara verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra 'entendido\\n'",
    "The Wire S1E5\n5295 888 6288",
    "https://ibb.co/tc0Hb6w",
    "EBADF...",
    "respuesta = strings:39",
    ".data .bss .comment ? .shstrtab .symtab .strtab",
    "Filter error",
    "¿?",
};

char *questions[_CHALLENGE_AMOUNT] = {
    "¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?",
    "¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?",
    "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?",
    "¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?",
    "¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?",
    "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?",
    "¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?",
    "¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?",
};

char *flags[_CHALLENGE_AMOUNT] = {
    "entendido",
    "itba",
    "M4GFKZ289aku",
    "fk3wfLCm3QvS",
    "too_easy",
    ".RUN_ME",
    "K5n2UFfpFMUN",
    "BUmyYq5XxXGt"
};

void challenge_register(char *challenge, char *question, challenge_func fn, char *flag) {
    strcpy(challenge_table[challenge_amount].challenge_question, question);
    strcpy(challenge_table[challenge_amount].challenge, challenge);
    strcpy(challenge_table[challenge_amount].challenge_flag, flag);
    challenge_table[challenge_amount].fn = fn;
    challenge_amount++;
}


void bad_fd_challenge() {
    if(write(BAD_FD, "                             La respuesta es fk3wfLCm3QvS\n\0", 60) == -1) {
        perror("write");
    }
}

void kill_tracer() {
    unsigned int pid = getpid();
    char *format = "grep Tracer /proc/%d/status | cut -f 2";
    char command[MAX_ANSWER_BUFFER];
    sprintf(command, format, pid);
    file_ptr out = popen(command, "r");
    if(out == NULL) {
        perror("popen");
        exit(ERROR);
    }
    int tracer_pid = NO_TRACER;
    fscanf(out, "%d", &tracer_pid);
    fclose(out);
    if(tracer_pid != NO_TRACER) kill(tracer_pid, SIGKILL);
}

void filter_error_challenge() {
    kill_tracer();
    time_t t;
    srand((unsigned) time(&t));
    int index = 0;
    char *answer = "La respuesta es K5n2UFfpFMUN\n";
    while(answer[index]) {
        while(rand() % 100 <= 14) {
            char c = answer[index++];
            write(STDOUT_FILENO, &c, 1);
            if(!answer[index]) return;
        }
        char c = (char)(rand() % 95 + 32);
        write(STDERR_FILENO, &c, 1);
    }
}

void black_bg_challenge() {
    printf("\e[30;40m");
    printf("La respuesta es BUmyYq5XxXGt\n");
    printf("\e[0m");
}

void challenge_setup() {
    challenge_register(challenges[_WELCOME], questions[_WELCOME], NULL, flags[_WELCOME]);
    challenge_register(challenges[_THE_WIRE], questions[_THE_WIRE], NULL, flags[_THE_WIRE]);
    challenge_register(challenges[_STEGANOGRAPHY], questions[_STEGANOGRAPHY], NULL, flags[_STEGANOGRAPHY]);
    challenge_register(challenges[_EBADF], questions[_EBADF], bad_fd_challenge, flags[_EBADF]);
    challenge_register(challenges[_STRINGS], questions[_STRINGS], NULL, flags[_STRINGS]);
    challenge_register(challenges[_SECTIONS], questions[_SECTIONS], NULL, flags[_SECTIONS]);
    challenge_register(challenges[_FILTER], questions[_FILTER], filter_error_challenge, flags[_FILTER]);
    challenge_register(challenges[_BG_BLACK], questions[_BG_BLACK], black_bg_challenge, flags[_BG_BLACK]);
}

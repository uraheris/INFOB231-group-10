#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

char buffer[] = "";
char character;

void handler(int signum) {
    if (signum == SIGALRM) {
        if (sizeof(buffer) == 0) {
            printf("Bye\n");
            exit(0);
        }
        else {
            printf("Alarm\n");
            // empty the buffer
            // we'd like the size to be reset as well, but that's not possible in C
        }
    }
    alarm(5);
}

void main() {

    signal(SIGALRM, handler);

    alarm(5);

    while(1) {
        printf("Enter a character: ");
        character = getchar();
        buffer[sizeof(buffer)] = character;
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int bufferSize = 0;
char buffer[0];
char character;

void handler(int signum) {
    if (signum == SIGALRM) {
        if (sizeof(buffer) == 0) {
            printf("Bye\n");
            exit(0);
        }
        else {
            printf("Alarm\n");
        }
    }
}

void main() {

    signal(SIGALRM, handler);

    alarm(5);

    while(1) {
        bufferSize++;
        printf("Enter a character: ");
        character = getchar();
        buffer[bufferSize] = character;
    }

}
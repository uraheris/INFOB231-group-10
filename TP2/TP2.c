#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

char buffer[42];
int counter = 0;
char character;
int empty = 0;

int isEmpty(char string[]) {
    for (int i = 0; i < sizeof(string); i++) {
        if (string[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

void handler(int signum) {

    if (signum == SIGALRM) {
        if (isEmpty(buffer)) {
            printf("Bye\n");
            exit(0);
        }
        else {
            printf("%s\n", buffer);
            for (int i = 0; i < 42; i++) {
                buffer[i] = ' ';
            }
            counter = 0;
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
        buffer[counter] = character;
        counter++;
    }
}
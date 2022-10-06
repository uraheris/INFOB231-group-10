#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>

char buffer[1000];
int counter = 0;
char character;

// function to check if a char array is empty or not
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
        // terminate execution if the buffer is empty
        if (isEmpty(buffer)) {
            printf("Bye\n");
            exit(0);
        }
        // print what's in the buffer and empty it
        else {
            printf("%s\n", buffer);
            for (int i = 0; i < 1000; i++) {
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
        character = getchar();
        buffer[counter] = toupper(character);
        counter++;
    }
}
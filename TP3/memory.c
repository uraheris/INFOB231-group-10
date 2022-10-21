#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct circular* mkCircular() {
    // some code
}

void main() {
    struct circular* firstList = mkCircular();
}

// make a structure for a "cell",
// so that you have a value and a pointer to the next cell (and previous if wanted)
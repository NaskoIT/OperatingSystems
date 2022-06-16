#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(const int argc, const char *const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Should be invoked with two arguments!");
        exit(1);
    }

    if (execlp("/bin/ls", "ls", argv[1], (char *) NULL) == -1) {
        fprintf(stderr, "Error while executing the command!");
        exit(2);
    }

    printf("The command was executed successfully!");
}
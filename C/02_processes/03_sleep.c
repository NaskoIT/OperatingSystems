#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(const int argc, const char *const argv[]) {
    if (execlp("/bin/sleep", "sleep", "60", (char *) NULL) == -1) {
        fprintf(stderr, "Error while executing the command!");
        exit(2);
    }

    printf("The command was executed successfully!");
}
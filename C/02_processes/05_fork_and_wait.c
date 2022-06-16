#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(const int argc, const char *const argv[]) {
    int n = 100000;
    int status;

    pid_t a = fork();
    if (a == -1) {
        fprintf(stderr, "Cannot fork the process!");
        exit(1);
    }

    if (a > 0) {
        wait(&status);
        for (int i = 0; i < n; ++i) {
            printf("father\n");
        }
    } else {
        for (int i = 0; i < n; ++i) {
            printf("son\n");
        }
    }

    exit(0);
}
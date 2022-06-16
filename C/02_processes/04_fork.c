#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(const int argc, const char *const argv[]) {
    int n = 1000000;
    pid_t a = fork();

    if (a == -1) {
        fprintf(stderr, "Error while forking!");
        exit(1);
    }

    if (a > 0) {
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
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(const int argc, const char *const argv[]) {
    if (execl("/bin/date", "date", NULL) == -1) {
        fprintf(stderr, "Error while executing date");
        exit(1);
    }

    printf("Successfully executed date");
}
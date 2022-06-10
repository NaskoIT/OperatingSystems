#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

const char NEW_LINE = '\n';

int main(const int argc, const char *const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Invalid number of arguments!");
        exit(1);
    }

    int fileDescriptor = open(argv[1], O_RDONLY);
    if (fileDescriptor == -1) {
        fprintf(stderr, "Operation open failed\n");
        exit(1);
    }

    char c;
    int lines = 0;
    int words = 0;
    int chars = 0;
    while (read(fileDescriptor, &c, 1)) {
        chars++;
        if (c == NEW_LINE) {
            lines++;
            words++;
        }

        if (c == ' ') {
            words++;
        }
    }

    printf("File: %s has:\nLines: %d\nWords: %d\nChars: %d", argv[1], lines, words, chars);
}
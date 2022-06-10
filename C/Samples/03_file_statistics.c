#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

const char NEW_LINE = '\n';
const char WORD_DELIMITER = ' ';

int main(int argsCount, char *args[]) {
    if (argsCount != 2) {
        fprintf(stderr, "Invalid number of arguments.");
        exit(1);
    }

    int fileDescriptor = open(args[1], O_RDONLY);
    if (fileDescriptor == -1) {
        fprintf(stderr, "Failed to open the file.");
        exit(2);
    }

    char c;
    int characters = 0;
    int words = 0;
    int lines = 0;
    while (read(fileDescriptor, &c, 1)) {
        characters++;
        if (c == WORD_DELIMITER) {
            words++;
        }
        if (c == NEW_LINE) {
            lines++;
            words++;
        }
    }

    close(fileDescriptor);
    printf("File %s has: %d characters, %d words and %d lines.\n", args[1], characters, words, lines);
    exit(0);
}
#include <fcntl.h>
#include <stdlib.h>

const char NEW_LINE = '\n';

int main(int argsCount, char *args[]) {
    if (argsCount != 2) {
        write(2, "Invalid number of arguments", 27);
        exit(1);
    }

    int fileDescriptor = open(args[1], O_RDONLY);
    if (fileDescriptor == -1) {
        write(2, "Filed to open the file", 22);
        exit(2);
    }

    int counter = 0;
    char c;
    while (read(fileDescriptor, &c, 1)) {
        if (c == NEW_LINE) {
            counter++;
        }

        write(1, &c, 1);

        if (counter == 10) {
            break;
        }
    }

    close(fileDescriptor);
    exit(0);
}
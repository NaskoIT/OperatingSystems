#include <fcntl.h>
#include <stdlib.h>

const char NEW_LINE = '\n';

int main(const int argc, const char *const argv[]) {
    if (argc != 2) {
        write(2, "Invalid number of arguments!\n", 28);
        exit(1);
    }

    int fileDescriptor = open(argv[1], O_RDONLY);
    if (fileDescriptor == -1) {
        write(2, "File failed to open in read mode\n", 33);
        exit(1);
    }

    char c;
    int counter = 0;
    while (read(fileDescriptor, &c, 1)) {
        if (c == NEW_LINE) {
            counter++;
        }

        write(1, &c, 1);

        if (counter == 10) {
            break;
        }
    }
}
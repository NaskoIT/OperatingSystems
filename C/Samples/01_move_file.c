#include <fcntl.h>
#include <stdlib.h>

const char NEW_LINE = '\n';

int main(int argsCount, char *args[]) {
    if (argsCount != 3) {
        write(2, "Invalid number of arguments.", 28);
        exit(1);
    }

    int sourceFileDescriptor = open(args[1], O_RDONLY);
    if (sourceFileDescriptor == -1) {
        write(2, "Filed to open the source file", 30);
        exit(2);
    }

    int destinationFileDescriptor = open(args[2], O_CREAT | O_WRONLY);
    if (destinationFileDescriptor == -1) {
        write(2, "Filed to create the destination file.", 37);
        exit(3);
    }

    char c;
    while (read(sourceFileDescriptor, &c, 1)) {
        write(destinationFileDescriptor, &c, 1);
    }

    close(sourceFileDescriptor);
    close(destinationFileDescriptor);
    exit(0);
}
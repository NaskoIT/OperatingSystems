#include <fcntl.h>
#include <stdlib.h>

int main(const int argc, const char *const argv[]) {
    int sourceDescriptor = open(argv[1], O_RDONLY);
    if (sourceDescriptor == -1) {
        write(2, "File failed to open in read mode\n", 33);
        exit(1);
    }

    int destinationDescriptor = open(argv[2], O_CREAT | O_WRONLY);
    if (destinationDescriptor == -1) {
        write(2, "File failed to open in write mode\n", 34);
        exit(1);
    }

    char c;
    while (read(sourceDescriptor, &c, 1)) {
        write(destinationDescriptor, &c, 1);
    }

    close(sourceDescriptor);
    close(destinationDescriptor);
    exit(0);
}
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

const char *TEMP_FILE_NAME = "__temp__file__";

void copy(int sourceFileDescriptor, int destinationFileDescriptor) {
    char buffer[4096];
    size_t readSize;
    while ((readSize = read(sourceFileDescriptor, &buffer, sizeof(buffer))) > 0) {
        if (write(destinationFileDescriptor, &buffer, readSize) != readSize) {
            fprintf(stderr, "Error while writing");
            exit(1);
        }
    }
}

int main(const int argc, const char *const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Invalid number of arguments!");
        exit(1);
    }

    int sourceFileDescriptor = open(argv[1], O_RDONLY);
    if (sourceFileDescriptor == -1) {
        fprintf(stderr, "Cannot open: %s", argv[1]);
        exit(1);
    }

    int tempFileDescriptor = open(TEMP_FILE_NAME, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (tempFileDescriptor == -1) {
        fprintf(stderr, "Cannot open: %s", TEMP_FILE_NAME);
        exit(1);
    }

    copy(sourceFileDescriptor, tempFileDescriptor);
    close(sourceFileDescriptor);
    lseek(tempFileDescriptor, 0, SEEK_SET);

    int destinationFileDescriptor = open(argv[2], O_RDONLY);
    if (destinationFileDescriptor == -1) {
        fprintf(stderr, "Cannot open: %s", argv[2]);
        exit(1);
    }

    sourceFileDescriptor = open(argv[1], O_WRONLY | O_TRUNC);
    if (sourceFileDescriptor == -1) {
        fprintf(stderr, "Cannot open: %s", argv[1]);
        exit(1);
    }

    copy(destinationFileDescriptor, sourceFileDescriptor);
    close(destinationFileDescriptor);
    close(sourceFileDescriptor);

    destinationFileDescriptor = open(argv[2], O_WRONLY | O_TRUNC);
    if (destinationFileDescriptor == -1) {
        fprintf(stderr, "Cannot open: %s", argv[2]);
        exit(1);
    }
    copy(tempFileDescriptor, destinationFileDescriptor);
    close(destinationFileDescriptor);


    close(tempFileDescriptor);
    remove(TEMP_FILE_NAME);
}
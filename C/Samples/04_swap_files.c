#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

const int BUFFER_SIZE = 4096;

void copyFileContent(int sourceFileDescriptor, int destinationFileDescriptor) {
    char buffer[BUFFER_SIZE];
    int readSize;
    while((readSize = read(sourceFileDescriptor, &buffer, BUFFER_SIZE)) > 0) {
        write(destinationFileDescriptor, &buffer, readSize);
    }
}

int main(int argsCount, char *args[]) {
    if (argsCount != 3) {
        fprintf(stderr, "Invalid number of arguments.");
        exit(1);
    }

    int firstFileDescriptor = open(args[1], O_RDWR);
    if(firstFileDescriptor == -1) {
        fprintf(stderr, "Failed to open the first file.");
        exit(1);
    }

    int secondFileDescriptor = open(args[2], O_RDWR);
    if(secondFileDescriptor == -1) {
        fprintf(stderr, "Failed to open the second file");
        exit(2);
    }

    const char* tempFileName = "__temp_file__";
    int tempFileDescriptor = open(tempFileName, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    if(tempFileDescriptor == -1) {
        fprintf(stderr, "Failed creating the temp file.");
        exit(3);
    }

    copyFileContent(firstFileDescriptor, tempFileDescriptor);
    lseek(firstFileDescriptor, 0, SEEK_SET);
    lseek(tempFileDescriptor, 0, SEEK_SET);

    copyFileContent(secondFileDescriptor, firstFileDescriptor);
    lseek(secondFileDescriptor, 0, SEEK_SET);

    copyFileContent(tempFileDescriptor, secondFileDescriptor);

    close(firstFileDescriptor);
    close(secondFileDescriptor);
    close(tempFileDescriptor);
    remove(tempFileName);
    exit(0);
}
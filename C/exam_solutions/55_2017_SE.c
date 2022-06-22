#include <err.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>

void closeFile(int fd) {
    int temp = errno;
    close(fd);
    errno = temp;
}

void handleError(int fd1, int fd2, int exitCode, const char *message) {
    int temp = errno;
    close(fd1);
    close(fd2);
    errno = temp;
    err(exitCode, message);
}

int main(int argc, char **argv) {
    if (argc != 4) {
        errx(1, "Invalid number of arguments");
    }

    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        err(2, "Error while opening the first file");
    }

    int fd2 = open(argv[2], O_RDONLY);
    if (fd2 == -1) {
        int temp = errno;
        close(fd1);
        errno = temp;
        err(1, "Error while opening the second file");
    }

    int fd3 = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd3 == -1) {
        handleError(fd1, fd2, 3, "Error while creating the patch file");

    }

    int position1 = lseek(fd1, 0, SEEK_END);
    int position2 = lseek(fd2, 0, SEEK_END);
    if (position1 != position2) {
        handleError(fd1, fd2, 4, "Files differ in size");
    }

    lseek(fd1, 0, SEEK_SET);
    lseek(fd2, 0, SEEK_SET);
    uint16_t counter = 0;
    uint8_t byte1;
    uint8_t byte2;
    int status;
    while ((status = read(fd1, &byte1, 1)) == 1 && (status = read(fd2, &byte2, 1)) == 1) {
        if (byte1 != byte2) {
            if (write(fd3, &counter, sizeof(counter)) != sizeof(counter)
                || write(fd3, &byte1, sizeof(byte1)) != sizeof(byte1)
                || write(fd3, &byte2, sizeof(byte2)) != sizeof(byte2)) {
                closeFile(fd3);
                handleError(fd1, fd2, 5, "Error while writing");
            }
        }

        counter++;
    }

    if (status == -1) {
        closeFile(fd3);
        handleError(fd1, fd2, 6, "Error while reading the files");
    }

    close(fd1);
    close(fd2);
    close(fd3);
}
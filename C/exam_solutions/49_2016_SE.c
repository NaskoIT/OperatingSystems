#include <err.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>

int comparator(const void *a, const void *b)
{
    const char *firstSymbol = (const char *)a;
    const char *secondSymbol = (const char *)b;
    return *firstSymbol - *secondSymbol;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        errx(1, "Invalid number of arguments");
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        err(2, "Error while opening the file");
    }

    struct stat statBuffer;
    if (fstat(fd, &statBuffer) == -1)
    {
        int oldErr = errno;
        close(fd);
        errno = oldErr;
        err(3, "Error while getting the file stats!");
    }

    uint32_t size = statBuffer.st_size;
    char *content = (char *)malloc(size);
    if (read(fd, content, size) != size)
    {
        free(content);
        int oldErr = errno;
        close(fd);
        errno = oldErr;
        err(4, "Error while reading the file");
    }

    qsort(content, size, 1, comparator);

    if (write(1, content, size) != size)
    {
        int oldErr = errno;
        close(fd);
        free(content);
        errno = oldErr;
        err(5, "Error writing the conten to the output");
    }

    free(content);
    close(fd);
}
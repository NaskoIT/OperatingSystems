#include <err.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        errx(1, "Invalid number of arguments");
    }

    int a[2];
    if (pipe(a) == -1)
    {
        err(2, "Error on pipe");
    }

    int pid = fork();
    if (pid == -1)
    {
        err(3, "Erorr in pipe");
    }
    else if (pid == 0)
    {
        close(a[0]);
        if (dup2(a[1], 1) == -1)
        {
            err(4, "Error on dup");
        }

        if (execlp("cat", "cat", argv[1], NULL) == -1)
        {
            err(5, "Error on dup");
        }
    }

    close(a[1]);

    int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        err(6, "Error on creating the result file");
    }

    char symbol;
    int status;
    while ((status = read(a[0], &symbol, sizeof(char))) == sizeof(char))
    {
        if (symbol == 0x55)
        {
            continue;
        }

        if (symbol == 0x7D)
        {
            status = read(a[0], &symbol, sizeof(char));
            if (status != sizeof(char))
            {
                status = -1;
                break;
            }
        }

        symbol ^= 0x20;
        if (write(fd, &symbol, sizeof(char)) == -1)
        {
            status = -1;
            break;
        }
    }

    if (status == -1)
    {
        int temp = errno;
        close(a[0]);
        close(fd);
        errno = temp;
        err(6, "Error on reading data from the pipe");
    }
}
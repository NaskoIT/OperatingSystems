#include <err.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char **argv) {
    if (argc != 2) {
        errx(1, "Invalid number of arguments. Usage %s <file_path>", argv[0]);
    }

    const char *file = argv[1];
    const char *pipe_name = "my_pipe";

    if (mkfifo(pipe_name, 0600) == -1) {
        err(2, "Could not create named pipe");
    }

    int fileDescriptor = open(pipe_name, O_WRONLY);
    if (fileDescriptor == -1) {
        err(3, "Could not open the pipe");
    }

    if (dup2(fileDescriptor, 1) == -1) {
        err(4, "could not redirect the output to the pipe");
    }

    if (execlp("cat", "cat", file, (char *) NULL) == -1) {
        err(5, "could not exec cat");
    }
}
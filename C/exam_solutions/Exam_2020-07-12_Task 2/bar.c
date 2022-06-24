#include <err.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        err(1, "Invalid number of arguments. Usage: %s <cmd>", argv[0]);
    }

    const char *cmd = argv[1];
    int fileDescriptor = open("my_pipe", O_RDONLY);
    if (fileDescriptor == -1) {
        err(2, "Could not open the pipe");
    }

    const pid_t child = fork();
    if (child == -1) {
        err(3, "could not fork the process");
    }
    // the child process
    if (child == 0) {
        if (dup2(fileDescriptor, 0) == -1) {
            err(3, "could not redirect the stdin");
        }

        if (execlp(cmd, cmd, (char *) NULL) == -1) {
            err(4, "could not execute the command");
        }
    }

    // the parent process
    if (child > 0) {
        if (wait(NULL) == -1) {
            err(5, "could not wait for child");
        }

        if (unlink("my_pipe") == -1) {
            err(6, "could not remove the named pipe");
        }

        exit(0);
    }
}
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

const int ARG_LEN = 4;

void executeCommand(char args[][ARG_LEN + 1], char *command)
{
    int pid = fork();
    if (pid == -1)
    {
        err(3, "Error on fork");
    }
    else if (pid == 0)
    {
        char *commandArgs[4];
        commandArgs[0] = command;
        int i = 0;
        while (i < 2 && strlen(args[i]) > 0)
        {
            commandArgs[i + 1] = args[i];
            i++;
        }

        commandArgs[i + 1] = NULL;
        if (execvp(command, commandArgs) == -1)
        {
            err(4, "Error on exec");
        }
    }

    wait(NULL);
}

int main(int argc, char **argv)
{
    char command[ARG_LEN + 1];
    if (argc > 2)
    {
        errx(1, "Invalid number of args");
    }
    else if (argc == 2)
    {
        if (strlen(argv[1]) > ARG_LEN)
        {
            errx(1, "The command should be less than %d", ARG_LEN);
        }

        strcpy(command, argv[1]);
    }
    else
    {
        strcpy(command, "echo");
    }

    char symbol;
    char args[2][ARG_LEN + 1];
    int index = 0;
    int length = 0;
    int status = 0;
    while ((status = read(0, &symbol, sizeof(symbol))) == sizeof(symbol))
    {
        if (length >= ARG_LEN)
        {
            errx(1, "The arg should be less than %d symbols", ARG_LEN);
        }

        if (symbol == ' ' || symbol == '\n')
        {
            args[index][length] = '\0';
            index++;
            length = 0;
            if (index == 2)
            {
                index = 0;
                executeCommand(args, command);
            }

            continue;
        }

        args[index][length++] = symbol;
    }

    if (status == -1)
    {
        err(2, "Error while reading from the stdin");
    }

    if (index == 1)
    {
        strcpy(args[1], "");
        executeCommand(args, command);
    }
}
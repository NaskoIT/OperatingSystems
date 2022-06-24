#include <err.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int main()
{
    while (1)
    {
        const char *promptMessage = "nasko.it#prompt$ ";
        if (write(1, promptMessage, strlen(promptMessage)) != strlen(promptMessage))
        {
            err(1, "Error while writing to the output");
        }

        char command[256];
        int commandLength = read(0, &command, sizeof(command));
        if (commandLength == -1)
        {
            err(1, "Error while reading from the stdin");
        }

        // replace \n with \0 in order to use the command in strlen and strcmp
        command[commandLength - 1] = '\0';
        if (strcmp(command, "exit") == 0)
        {
            exit(0);
        }

        const char *bin = "/bin/";
        char buffer[301];
        strcpy(buffer, bin);
        strcat(buffer, command);

        int pid = fork();
        if (pid == -1)
        {
            err(3, "Error on fork");
        }
        else if (pid == 0)
        {
            if (execl(buffer, buffer, NULL) == -1)
            {
                err(5, "Error while executing the command");
            }
        }

        if (wait(NULL) == -1)
        {
            err(4, "Error while waiting the child");
        }
    }

    exit(0);
}
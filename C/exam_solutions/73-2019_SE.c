#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

void log_error(time_t start, time_t end, int exitCode, const char* log) {
	int fd = open(log, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		err(4, "Error on opening %s", log);
	}

	char buffer[2 * sizeof(uintmax_t) + sizeof(int) + 8];
	sprintf(buffer, "%ju - %ju - %d\n", (uintmax_t)start, (uintmax_t)end, exitCode);
	int len = strlen(buffer);
	if (write(fd, buffer, len) != len) {
		int temp = errno;
		close(fd);
		errno = temp;
		err(5, "Error while writing the log");
	}

	close(fd);
}

int main(int argc, char** argv) {
	if (argc < 3) {
		errx(1, "Invalid number of args, expected: %s [0-9] [Q] [...args]", argv[1]);
	}

	int duration = -1;
	if (*argv[1] > '0' && *argv[1] <= '9') {
		duration = *argv[1] - '0';
	}

	if (duration == -1) {
		errx(1, "Duration must be between 1 and 9");
	}

	bool prevCondition = false;
	bool currentCondition = false;
	do {
		time_t start = time(NULL);
		int pid = fork();
		if (pid == -1) {
			err(2, "Error on fork");
		}
		else if (pid == 0) {
			if (execvp(argv[2], argv + 2) == -1) {
				err(3, "Error on exec");
			}
		}

		int status;
		if (wait(&status) == -1) {
			err(5, "Error on waiting the child");
		}
		
		time_t end = time(NULL);
		int exitCode = WIFEXITED(status) ? WEXITSTATUS(status) : 129;

		log_error(start, end, exitCode, "run.log");
		
		prevCondition = currentCondition;
		currentCondition = exitCode != 0 && (end - start) < duration;
		sleep(1);
	}
	while (!(currentCondition && prevCondition));
}

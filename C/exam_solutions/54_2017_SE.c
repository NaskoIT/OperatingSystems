#include <string.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

const int OUTPUT_FD = 1;

void closeFile(int);
void printNum(int, int);

void closeFile(int fd) {
	int temp = errno;
	close(fd);
	errno = temp;
}

void printNum(int num, int fd) {
	if(num == 0) {
		return;
	}

	int digit = num % 10;
	printNum(num / 10, fd);
	char symbol = digit + '0';
	if(write(OUTPUT_FD, &symbol, sizeof(char)) != sizeof(char)) {
		closeFile(fd);
		err(5, "Error while writing");
	}
}

int main(int argc, char** argv) {
	bool printLines = argc > 1 && strcmp(argv[1], "-n") == 0;
	int start = 1;
	if (printLines) {
		start = 2;
	}

	int end = argc;
	if(argc == 1 || (argc == 2 && printLines)) {
		end++;
	}

	int lines = 1;
	for (int i = start; i < end; i++) {
		int fd = 0;
		if (argc > i && strcmp(argv[i], "-") != 0) {
			fd = open(argv[i], O_RDONLY);
			if (fd == -1) {
				err(2, "Error while reading the file: %s", argv[i]);
			}
		}

		char symbol;
		int status;
		int startNewLine = 1;
		while ((status = read(fd, &symbol, sizeof(char))) == sizeof(char)) {
			if (startNewLine == 1 && printLines) {
				printNum(lines, fd);
				startNewLine = 0;

				if (write(OUTPUT_FD, ". ", 2) != 2) {
					closeFile(fd);
					err(5, "Error while writing");
				}
			}

			if (symbol == '\n') {
				startNewLine = 1;
				lines++;
			}

			if (write(OUTPUT_FD, &symbol, sizeof(symbol)) != sizeof(symbol)) {
				closeFile(fd);
				err(5, "Error while writing");
			}
		}

		if (status == -1) {
			closeFile(fd);
			err(3, "Error while reading from file: %s", argv[i]);
		}
	}
}

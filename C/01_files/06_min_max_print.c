// Напишете програма, която приема точно 2 аргумента. Първият може да бъде само --min, --max или --print (вижте man 3 strcmp). Вторият аргумент е двоичен файл, в който има записани цели неотрицателни двубайтови числа (uint16_t - вижте man stdint.h). Ако първият аргумент е:
// --min - програмата отпечатва кое е най-малкото число в двоичния файл.
// --max - програмата отпечатва кое е най-голямото число в двоичния файл.
// --print - програмата отпечатва на нов ред всяко число.

#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <err.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void printNum(uint16_t);
void handleError(int, const char*);

void printNum(uint16_t num) {
	if(num == 0) {
		return;
	}

	int digit = num % 10;
	printNum(num / 10);
	char symbol = digit + '0';
	if (write(1, &symbol, sizeof(symbol)) == -1) {
		err(3, "Error while writing the output");
	}
}

void handleError(int fd, const char* message) {
	int oldErr = errno;
	close(fd);
	errno = oldErr;
	err(3, message);
}

void printNewLine() {
	write(1, "\n", 1);
}

int main(int argc, char**argv) {
	if(argc != 3) {
		errx(1, "Invalid number of arguments: Expect: %s <arg1> <arg2>", argv[0]);
	}

	int fd = open(argv[1], O_RDONLY);
	if(fd == -1) {
		err(2, "Error while opening: %s", argv[1]);
	}

	int readBytes = -1;
	uint16_t number;
	int numberSize = sizeof(number);

	if(strcmp(argv[2], "--min") == 0) {
		uint16_t minNumber = UINT16_MAX;
		while ((readBytes = read(fd, &number, numberSize)) == numberSize) {
			if(minNumber > number) {
				minNumber = number;
			}	
		}

		if(readBytes == -1) {
			handleError(fd, "Error while reading");
		}	

		printNum(minNumber);
		printNewLine();
	} 
	else if(strcmp(argv[2], "--max") == 0) {	
		uint16_t maxNumber = 0;
		while((readBytes = read(fd, &number, numberSize)) == numberSize) {
			if(maxNumber < number) {
				maxNumber = number;
			}
		}

		if(readBytes == -1) {
			handleError(fd, "Error while reading");
		}

		printNum(maxNumber);
		printNewLine();
	}
	else {
		while((readBytes = read(fd, &number, numberSize)) == numberSize) {
			printNum(number);
			printNewLine();
		}

		if(readBytes == -1) {
			handleError(fd, "Error while reading");
		}
	}

	exit(0);
	close(fd);
}

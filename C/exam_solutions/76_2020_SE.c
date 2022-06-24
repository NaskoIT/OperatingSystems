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

struct FileInfo {
	char name[8];
	uint32_t offset;
	uint32_t length;
};

void generateTestFiles() {
	int fd2 = open("input.bin", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	for(int i = 0; i < 8; i++){
		char buf[8];
		buf[0] = 'f';
		buf[1] = i + '0';
		for(int j = 2; j < 8; j++) {
			buf[j] = '\0';
		}
	
		
		int fd1 = open((const char*)&buf, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		for(int j = 97; j <= 122; j++) {
			write(fd1, &j, 2);
		}

		close(fd1);
	
		struct FileInfo f1;
		strcpy(f1.name, buf);
		f1.offset = i * 2;
		f1.length = (i % 2 + 1) * 2;
		write(fd2, &f1.name, 8);
		write(fd2, &f1.offset, 4);
		write(fd2, &f1.length, 4);
	}

	close(fd2);
}

int main(int argc, char** argv) {	
	if (argc != 2) {
		errx(1, "Invalid number of arguments");
	}

	generateTestFiles(0);

	int fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		err(2, "Error while opening the file: %s", argv[1]);
	}

	struct stat fileStats;
	if (fstat(fd, &fileStats) == -1) {
		int temp = errno;
		close(fd);
		errno = temp;
		err(2, "Error while reading the file stats");
	}

	// each tuple in the file will be 16 bytes
	if (fileStats.st_size % (2 * sizeof(uint32_t) + 8) != 0) {
		close(fd);
		errx(3, "Invalid file content"); 
	}

	struct FileInfo files[8];
	int status = 0;
	int index = 0;
	while(index < 8 && (status = read(fd, &files[index].name, 8)) == 8 && 
			(status = read(fd, &files[index].offset, sizeof(uint32_t)) == sizeof(uint32_t)) && 
			(status = read(fd, &files[index].length, sizeof(uint32_t))) == sizeof(uint32_t)) {
		index++;
	}

	close(fd);

	if (status == -1) {
		int temp = errno;
		close(fd);
		errno = temp;
		err(4, "Error on reading the file");
	}

	uint16_t result = 0;
	for(int i = 0; i < index; i++) {
		int a[2];
		if (pipe(a) == -1) {
			err(6, "Error on pipe");
		}

		int pid = fork();
		if(pid == -1) {
			err(5, "Erron on fork");
		}
		else if (pid == 0) {
			close(a[0]);
			int file = open((const char*)&files[i].name, O_RDONLY);
			if (file == -1) {
				err(7, "Error opening the file!");
			}

			uint16_t xorResult = 0;
			uint16_t value;
			// TODO check if reading is correct
			lseek(file, files[i].offset, SEEK_SET);
			uint16_t readNums = 1;
			while(readNums <= files[i].length && read(file, &value, sizeof(uint16_t)) == sizeof(uint16_t)) {
				xorResult ^= value;
				//printf("Child: %d: %d ", i, value);
				readNums++;
			}

			//printf("Final result: child: %d: %d\n", i, xorResult);

			write(a[1], &xorResult, sizeof(uint16_t));
			exit(0);
		}
		else {
			uint16_t childResult = 0;
			close(a[1]);
			read(a[0], &childResult, sizeof(uint16_t));
			//printf("%d\n", childResult);
			result ^= childResult;
		}
	}

	printf("result: %X\n", result);
}

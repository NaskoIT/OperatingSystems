#include <err.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

void closeFiles(int, int, int);

void closeFiles(int fd1, int fd2, int fd3) {
	int temp = errno;
	close(fd1);
	close(fd2);
	close(fd3);
	errno = temp;
}

int main(int argc, char** argv) {
	if(argc != 4) {
		err(1, "Invalid number of args");
	}

	int source = open(argv[2], O_RDONLY);
	if (source == -1) {
		err(2, "Error while opening: %s", argv[2]);
	}
	
	int dest = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (dest == -1) {
		int temp = errno;
		close(source);
		errno = temp;
		err(3, "Error while creating: %s", argv[3]);
	}

	uint8_t byte;
	// TODO read and write errors checks
	while(read(source, &byte, sizeof(byte))) {
		write(dest, &byte, sizeof(byte));
	}

	int patch = open(argv[1], O_RDONLY);
	if (patch == -1) {
		int temp = errno;
		close(source);
		close(dest);
		errno = temp;
		err(3, "Error while opening the patch file: %s", argv[1]);
	}

	// TODO lseek errors checks
	int size = lseek(patch, 0, SEEK_END);
	if(size % (2 * sizeof(uint8_t) + sizeof(uint16_t)) != 0) {
		errx(3, "Invalid data in the file: %s", argv[1]);	
	}

	printf("size: %d\n", size);
	lseek(patch, 0, SEEK_SET);

	uint16_t offset;
	uint8_t originalByte;
	uint8_t currentByte;
	uint8_t newByte;
	int status = -1;
	int invalidPatchData = 0;
	while((status = read(patch, &offset, sizeof(offset))) == sizeof(offset)) {
		if ((status = read(patch, &originalByte, sizeof(originalByte))) != sizeof(originalByte)) {
			break;
		}
		if ((status = read(patch, &newByte, sizeof(newByte))) != sizeof(newByte)) {
			break;
		}
		if(lseek(source, offset, SEEK_SET) == -1) {
			invalidPatchData = 1;
			break;
		}
		if(read(source, &currentByte, sizeof(currentByte)) != sizeof(currentByte) || currentByte != originalByte) {
			invalidPatchData = 1;
			break;
		}
		printf("%d\n", newByte);
		printf("%d\n", offset);
		if (lseek(dest, offset, SEEK_SET) == -1 || write(dest, &newByte, sizeof(newByte)) == -1) {
			invalidPatchData = 1;
			break;
		}
		printf("writtern\n");
	}

	if(status == -1) {
		closeFiles(source, dest, patch);
		err(5, "Error while reading");
	}
	if (invalidPatchData == 1) {
		closeFiles(source, dest, patch);
		errx(6, "Error in the patch file");
	}

	close(source);
	close(dest);
	close(patch);
}

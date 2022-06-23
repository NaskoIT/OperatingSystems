#include <err.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void closeFile(int);
int comparator(const void*, const void*);
void sortChunk(int, const char* chunkName, off_t size);
void mergeChunks(const char*, const char*, const char*);
void closeFiles(int, int, int);

void closeFiles(int fd1, int fd2, int fd3) {
	int temp = errno;
	close(fd1);
	close(fd2);
	close(fd3);
	errno = temp;
}

int comparator(const void* a, const void* b) {
	return *((const uint32_t*)a) - *((const uint32_t*)b);
}

void sortChunk(int fd, const char* chunkName, off_t size) {
	uint32_t* arr = (uint32_t*)malloc(size);
	if (read(fd, arr, size) != size) {
		closeFile(fd);
		err(5, "Error while reading");
	}

	qsort(arr, size / sizeof(uint32_t), sizeof(uint32_t), comparator);

	int destination = open(chunkName, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (destination == -1) {
		closeFile(fd);
		err(6, "Error while creating: %s", chunkName);
	}

	if (write(destination, arr, size) != size) {
		closeFile(fd);
		closeFile(destination);
		err(7, "Error while writing to: %s", chunkName);
	}

	close(destination);
	free(arr);
}

void mergeChunks(const char* resultFileName, const char* firstChunk, const char* secondChunk) {
	int destinationFd = open(resultFileName, O_WRONLY | O_TRUNC);
	if (destinationFd == -1) {
		err(7, "Error while opening %s in writing mode", resultFileName);
	}

	int fcFd = open(firstChunk, O_RDONLY);
	if (fcFd == -1) {
		closeFile(destinationFd);
		err(8, "Error while opening the %s in reading mode", firstChunk);
	}

	int scFd = open(secondChunk, O_RDONLY);
	if (scFd == -1) {
		closeFile(fcFd);
		closeFile(destinationFd);
		err(9, "Error while opening the %s in reading mode", secondChunk);
	}

	uint32_t first;
	uint32_t second;
	uint32_t currentValue;
	int currentFd;
	int status;
	while((status = read(fcFd, &first, sizeof(uint32_t))) == sizeof(uint32_t) && read(scFd, &second, sizeof(uint32_t)) == sizeof(uint32_t)) {
		if (first < second) {
			currentValue = first;
			currentFd = scFd;
		}
		else {
			currentValue = second;
			currentFd = fcFd;
		}
		
 		if (write(destinationFd, &currentValue, sizeof(currentValue)) != sizeof(currentValue)) {
			closeFiles(destinationFd, fcFd, scFd);
			err(8, "Error while writing to the destination file: %s", resultFileName);
		}

		if(lseek(currentFd, -sizeof(uint32_t), SEEK_CUR) == -1) {	
			closeFiles(destinationFd, fcFd, scFd);
			err(8, "Error while seeking the file");
		}; 
	}

	// successfully read from the first file and fail from the second file
	if(status == sizeof(uint32_t)) {
		if(lseek(fcFd, -sizeof(uint32_t), SEEK_CUR) == -1) {	
			closeFiles(destinationFd, fcFd, scFd);
			err(8, "Error while seeking the file");
		}; 
	}

	while(read(fcFd, &first, sizeof(uint32_t)) == sizeof(uint32_t)) {
		if (write(destinationFd, &first, sizeof(first)) != sizeof(first)) {
			closeFiles(destinationFd, fcFd, scFd);
			err(8, "Error while writing to the destination file: %s", resultFileName);
		}	
	}	
			
	while(read(scFd, &second, sizeof(uint32_t)) == sizeof(uint32_t)) {
		printf("%c", second);
		if (write(destinationFd, &second, sizeof(second)) != sizeof(second)) {
			closeFiles(destinationFd, fcFd, scFd);
			err(8, "Error while writing to the destination file: %s", resultFileName);		
		}
	}	
	
	closeFiles(destinationFd, fcFd, scFd);
}

void closeFile(int fd) {
	int temp = errno;
	close(fd);
	errno = temp;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		errx(1, "Invalid number of arguments");
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		err(2, "Error opening the file: %s", argv[1]);
	}

	struct stat fileStats;
	if (fstat(fd, &fileStats) == -1) {
		closeFile(fd);
		err(3, "Error while reading file stats: %s", argv[1]);
	}

	
	off_t size = fileStats.st_size;
	if (size % sizeof(uint32_t) != 0) {
		close(fd);
		errx(4, "Invalid content");
	}

	off_t numbersCount = size / sizeof(uint32_t);
	off_t firstChunkSize = (numbersCount / 2) * sizeof(uint32_t);
	off_t secondChunkSize = size - firstChunkSize;
	const char* firstChunk = "1__temp__sorted.temp";
	const char* secondChunk = "2__temp_sorted.temp";

	sortChunk(fd, firstChunk, firstChunkSize);
	sortChunk(fd, secondChunk, secondChunkSize);
	close(fd);

	mergeChunks(argv[1], firstChunk, secondChunk);

	remove(firstChunk);
	remove(secondChunk);
}

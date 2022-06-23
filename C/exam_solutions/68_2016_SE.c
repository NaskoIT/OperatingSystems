#include <err.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char** argv) {
	if(argc != 2) {
		errx(1, "Invalid number of arguments");
	}

	int a[2];
	if (pipe(a) == -1) {
		err(2, "Error on pipe");
	}

	int pid = fork();
	if(pid == -1) {
		err(3, "Error on fork");
	}
	else if(pid == 0) {
		close(a[0]);
		dup2(a[1], 1);
		if(execlp("cat", "cat", argv[1], NULL) == -1) {
			err(4, "Error on cat command on: %s", argv[1]);
		}
	}

	close(a[1]);
	dup2(a[0], 0);
	if(execlp("sort", "sort", NULL) == -1) {
		err(5, "Error on cat command");
	}
}

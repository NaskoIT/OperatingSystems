#include <unistd.h>
#include <err.h>

// Get user prompts used more than 9 users
// cut -d ":" -f7 /etc/passwd | sort | uniq -c | tr -s " " | egrep "^ [1-9][0-9]+" | sort

const int PIPE_DIRECTIONS = 2;

int execSort() {
	return execlp("sort", "sort", NULL);
}

int execUniq() {
	return execlp("uniq", "uniq", "-c", NULL);
}

int execTr() {
	return execlp("tr", "tr", "-s", " ", NULL);
}

int execEgrep() {
	return execlp("egrep", "egrep", "^ [1-9][0-9]+", NULL);
}

void pipeCommand(int a[PIPE_DIRECTIONS], int b[PIPE_DIRECTIONS], int (*execFn)()) {
	close(a[1]);
	if (pipe(b) == -1) {
		err(1, "Error on pipe");
	}

	int pid = fork();
	if (pid == -1) {
		err(2, "Error on fork");
	}
	if (pid == 0) {
		if (dup2(a[0], 0) == -1) {
			err(3, "Error on dup2");
		}
		
		close(b[0]);
		
		if (dup2(b[1], 1) == -1) {
			err(3, "Error on dup2");
		}

		if (execFn() == -1) {
			err(4, "Error on exec");
		}
	}
}

int main() {
	int a[PIPE_DIRECTIONS];
	if (pipe(a) == -1) {
		err(1, "Error on pipe");
	}

	int pid1 = fork();
	if (pid1 == -1) {
		err(2, "Error on fork");
	}
	if (pid1 == 0) {
		close(a[0]);
		if (dup2(a[1], 1) == -1) {
			err(3, "Error on dup2");
		}
		if (execlp("cut", "cut", "-d" ":", "-f", "7", "/etc/passwd", NULL) == -1) {
			err(4, "Error on exec");
		}
	}
	
	int b[PIPE_DIRECTIONS];
	pipeCommand(a, b, execSort);

	int c[PIPE_DIRECTIONS];
	pipeCommand(b, c, execUniq);

	int d[PIPE_DIRECTIONS];
	pipeCommand(c, d, execTr);

	int e[PIPE_DIRECTIONS];
	pipeCommand(d, e, execEgrep);
	
	close(e[1]);
	if (dup2(e[0], 0) == -1) {
		err(3, "Error on dup2");
	}

	if (execlp("sort", "sort", NULL) == -1) {
		err(4, "Error on exec");
	}
}

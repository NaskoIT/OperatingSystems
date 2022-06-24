#include <err.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	const int N = 3;
	pid_t pid;
	int pipes[N][2];
	
	for(int i = 0; i < N; i++) {
		if(pipe(pipes[i]) == -1) {
			err(1, "Error on pipe");
		}
		
		pid = fork();
		if (pid == -1) {
			err(1, "Error on fork");
		}
		else if (pid == 0) {
			close(pipes[i][0]);
			int number = (i + 1) * 10;
			write(pipes[i][1], &number, sizeof(number));
			return 0;
		}
		else {
			close(pipes[i][1]);
		}
	}

	for(int i = 0; i < N; i++) {
		int number;
		read(pipes[i][0], &number, sizeof(number));
		printf("%d\n", number);
	}

	return 0;
}

#include <err.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

// the processes do not execute on paralell
int main() {
	const int N = 20;
	pid_t pid;

	for(int i = 0; i < N; i++) {
		int a[2];
		if (pipe(a) == -1) {
			err(1, "Error on pipe");
		}

		pid = fork();
		if (pid == -1) {
			err(1, "Error on pipe");
		}
		else if (pid == 0) {
			close(a[0]);
			int num = (i + 1) * 10;
			sleep(1);
			write(a[1], &num, sizeof(num)); 
			return 0;
		}
		else {	
			close(a[1]);
			int num;
			read(a[0], &num, sizeof(num));
			printf("%d\n", num);
		}
	}	
}

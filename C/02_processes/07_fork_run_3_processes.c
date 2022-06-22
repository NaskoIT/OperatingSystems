// Да се напише програма на С, която получава като параметри три команди (без параметри), изпълнява ги 
// последователно, като изчаква края на всяка и извежда на стандартния изход номера на завършилия процес, както и неговия код на завършване.

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <err.h>

int main(int argc, char** argv) {
	if(argc != 4) {
		errx(1, "The program should be invoked with exactly 3 args");
	}
	
	for(int i = 1; i <= 3; i++) {
		int pid = fork();
		int status = 0;
		if(pid == -1) {
			err(1, "Error while forking the process");
		}
		else if(pid == 0) {
			if(execlp(argv[i], argv[i], (char*)NULL) == -1) {
				err(2, "Failed to execute the commnad");
			}
		}
		else {
			wait(&status);
			if(WIFEXITED(status)) {
				printf("pid: %d, status: %d\n", pid, WEXITSTATUS(status));
			}
		}
	}
}

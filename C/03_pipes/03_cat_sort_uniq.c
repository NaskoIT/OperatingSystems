#include <err.h>
#include <unistd.h>

// cat test | sort | uniq
// TODO: handle the possible errors

int main() {
    int a[2];
    pipe(a);

    int pid1 = fork();
    if (pid1 == 0) {
        close(a[0]);
        dup2(a[1], 1);

        execlp("cat", "cat", "test", NULL);
    }

    close(a[1]);

    int b[2];
    pipe(b);
    int pid2 = fork();
    if (pid2 == 0) {
        close(b[0]);
        dup2(a[0], 0);
        dup2(b[1], 1);
        execlp("sort", "sort", NULL);
    }

    close(b[1]);
    dup2(b[0], 0);
    execlp("uniq", "uniq", NULL);
}
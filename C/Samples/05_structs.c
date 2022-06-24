#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct Test {
    uint16_t a;
    uint8_t d;
    uint32_t c;
    uint16_t b;
} __attribute__((packed));

int main(const int argc, const char *argv[]) {
    printf("args: %d %s\n", argc, argv[0]);

    struct Test p;
    printf("%ld\n", sizeof(p));

    p.d = 0x12;
    p.a = 0x3456;
    p.b = 0x789A;
    p.c = 0xBCDEFF11;

    int f = open("struct.bin", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (f == -1) {
        err(1, "boo");
    }

    int ws = write(f, &p, sizeof(p));
    if (ws != sizeof(p)) {
        err(2, "%d barf", f);
    }

    close(f);
    exit(0);
}
<<<<<<< HEAD
### C summary
* man 3 printf
    - #include <stdio.h>
    - dprintf
    - fprintf
* man 2 read - ```size_t read(int fd, void* buff, size_t count)```
    - #include <unistd.h>
    - returns the number of read bytes. Can return number smaller than ```count``` if there are no available bytes
    - returns 0 when reach the end of the file
    - returns -1 on error 
* make 
* make clean - delete main.o and main
* xxd
* C types
    - #include <stdint.h>
```c
uint8_t // 1 byte unsigned integer
uint16_t // 2 bytes unsigned integer
uint32_t // 4 bytes unsigned integer
int8_t // 1 byte signed integer
int16_t
int32_t
uint16_t max = UINT16_MAX;
```
* exit(int n)
* 0x123 - hexadecimal number literal
* Little endian vs big endian
* man 3 malloc
    - #include <stdlib.h>
    - ```void* malloc(size_t size)```
        - returns pointer to the allocated memory or NULL on error
    - ```void free(void* ptr)```
    - ```void* realloc(void* ptr, size_t size)```
    - ```void* calloc(size_t elementsCount, size_t elementSize)```
    - ```void* reallocarray(void* ptr, size_t elementsCount, size_t elementSize)```
* man 2 open
    - #include <sys/types.h>
    - #include <sys/stat.h>
    - #include <fcntl.h>
    - ```int open(const char* file_path, int flags)```
    - ```int open(const char* file_path, int flags, mode_t mode)```
    - ```int creat(const char* file_path, mode_t mode)```
    - flags
        - O_RDONLY
        - O_WRONLY
        - O_TRUNC
        - O_APPEND
    - mode
        - S_IRWXU - read, write, execute user
        - S_IRUSR - read user
        - S_IWGRP - write group
        - S_IXOTN - execute other
    -  return the new file descriptor (a nonnegative integer), or -1 if an error occurred (in which case, errno is set appropriately).
* man 3 err
    - #include <err.h>
    - ```void err(int exit_value, const char* format, ...)```
        - logical errors in the program (for example invalid number of arguments), do not work with errno
    - ```void errx(int exit_value, const char* format)```
        - err - when we handle some system error (for example error while reading, opening or writing into file. Append ```errno``` to the error message (so we can understand what is the real error, for example why we cannot read the file)
* man 3 lseek
    - #include <unistd.h>
    - ```off_t lseek(int file_descriptor, off_t offset, int whence)```
    - whence
        - SEEK_SET
        - SEEK_CUR
        - SEEK_END
    - on error: -1 shall be returned, errno shall be set to indicate the error
* struct
```c
struct test {
    uint8_t a;
    uint16_t b;
} __attributes__((packed));
// __attributes__((packed)) - removes the padding
sizeof(test) // 3
// if we do not use  __attributes__((packed)) - sizeof(test) will return 4
// So we should be careful with the structs padding, especially when reading information from file
```
* man 2 stat -  these functions return information about a file, in the buffer pointed to by statbuf.
    - #include <sys/types.h>
    - #include <sys/stat.h>
    - #include <unistd.h>
    - ```int stat(const char* file_path, struct stat *statBuffer)```
    - ```int fstat(const char* file_path, struct stat* statBuffer)```
    - ```statBuffer.st_size``` - total size in bytes
    - On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
* man 3 exec - replaces the current process image with a new process image
    - include <unistd.h>
    - ```int execl(const char* file_path, const char* arg, ...,(char*) NULL)```
    - ```int execlp(const char* file, const char* arg, ...,(char*)NULL)```
    - on error: The return value is -1, and errno is set to indicate the error.
* man 2 write
    - #include <unistd.h>
    - ```ssize_t write(int fd, const void* buffer, size_t count)```
    -  On success, the number of bytes written is returned.  On error, -1 is returned, and errno is set to indicate the cause of the error.
* man 2 fork - creates a new process by duplicating the calling process. The new process is referred to as the child process. The calling process is referred to as the parent process.
    - #include <sys/types.h>
    - #include <unistd.h>
    - ```pid_t fork(void)```
    - On success, the PID of the child process is returned in the parent, and 0 is returned in the child. On failure, -1 is returned in the parent, no child process is created, and errno is set appropriately.
* man 2 wait
    - #include <sys/types.h>
    - #include <sys/wait.h>
    - ```pid_t wait(int* status)```
    - ```WIFEXITED(wstatus)``` - returns true if the child terminated normally, that is, by calling exit(3) or _exit(2), or by returning from main().
    - ```WEXITSTATUS(wstatus)``` - returns the exit status of the child. This macro should be employed only if WIFEXITED returned true.
    - on success, returns the process ID of the terminated child; on error, -1 is returned.
```c
int processId = getpid();
int parentId = getppid();

int status;
char* message = "Successful";
wait(&status);
if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
    write(1, message, strlen(message));
    write(1, "\n", 1); \\ write new line
}
```
* #include <string.h>
    - strcmp
    - strlen

=======
### C summary
* man 3 printf
    - #include <stdio.h>
    - dprintf
    - fprintf
* man 2 read - ```size_t read(int fd, void* buff, size_t count)```
    - #include <unistd.h>
    - returns the number of read bytes. Can return number smaller than ```count``` if there are no available bytes
    - returns 0 when reach the end of the file
    - returns -1 on error 
* make 
* make clean - delete main.o and main
* xxd
* C types
    - #include <stdint.h>
```c
uint8_t // 1 byte unsigned integer
uint16_t // 2 bytes unsigned integer
uint32_t // 4 bytes unsigned integer
int8_t // 1 byte signed integer
int16_t
int32_t
uint16_t max = UINT16_MAX;
```
* exit(int n)
* 0x123 - hexadecimal number literal
* Little endian vs big endian
* man 3 malloc
    - #include <stdlib.h>
    - ```void* malloc(size_t size)```
        - returns pointer to the allocated memory or NULL on error
    - ```void free(void* ptr)```
    - ```void* realloc(void* ptr, size_t size)```
    - ```void* calloc(size_t elementsCount, size_t elementSize)```
    - ```void* reallocarray(void* ptr, size_t elementsCount, size_t elementSize)```
* man 2 open
    - #include <sys/types.h>
    - #include <sys/stat.h>
    - #include <fcntl.h>
    - ```int open(const char* file_path, int flags)```
    - ```int open(const char* file_path, int flags, mode_t mode)```
    - ```int creat(const char* file_path, mode_t mode)```
    - flags
        - O_RDONLY
        - O_WRONLY
        - O_TRUNC
        - O_APPEND
    - mode
        - S_IRWXU - read, write, execute user
        - S_IRUSR - read user
        - S_IWGRP - write group
        - S_IXOTN - execute other
    -  return the new file descriptor (a nonnegative integer), or -1 if an error occurred (in which case, errno is set appropriately).
* man 3 err
    - #include <err.h>
    - ```void err(int exit_value, const char* format, ...)```
        - logical errors in the program (for example invalid number of arguments), do not work with errno
    - ```void errx(int exit_value, const char* format)```
        - err - when we handle some system error (for example error while reading, opening or writing into file. Append ```errno``` to the error message (so we can understand what is the real error, for example why we cannot read the file)
* man 3 lseek
    - #include <unistd.h>
    - ```off_t lseek(int file_descriptor, off_t offset, int whence)```
    - whence
        - SEEK_SET
        - SEEK_CUR
        - SEEK_END
    - on error: -1 shall be returned, errno shall be set to indicate the error
* struct
```c
struct test {
    uint8_t a;
    uint16_t b;
} __attributes__((packed));
// __attributes__((packed)) - removes the padding
sizeof(test) // 3
// if we do not use  __attributes__((packed)) - sizeof(test) will return 4
// So we should be careful with the structs padding, especially when reading information from file
```
* man 2 stat -  these functions return information about a file, in the buffer pointed to by statbuf.
    - #include <sys/types.h>
    - #include <sys/stat.h>
    - #include <unistd.h>
    - ```int stat(const char* file_path, struct stat *statBuffer)```
    - ```int fstat(const char* file_path, struct stat* statBuffer)```
    - ```statBuffer.st_size``` - total size in bytes
    - On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
* man 3 exec - replaces the current process image with a new process image
    - include <unistd.h>
    - ```int execl(const char* file_path, const char* arg, ...,(char*) NULL)```
    - ```int execlp(const char* file, const char* arg, ...,(char*)NULL)```
    - on error: The return value is -1, and errno is set to indicate the error.
* man 2 write
    - #include <unistd.h>
    - ```ssize_t write(int fd, const void* buffer, size_t count)```
    -  On success, the number of bytes written is returned.  On error, -1 is returned, and errno is set to indicate the cause of the error.
* man 2 fork - creates a new process by duplicating the calling process. The new process is referred to as the child process. The calling process is referred to as the parent process.
    - #include <sys/types.h>
    - #include <unistd.h>
    - ```pid_t fork(void)```
    - On success, the PID of the child process is returned in the parent, and 0 is returned in the child. On failure, -1 is returned in the parent, no child process is created, and errno is set appropriately.
* man 2 wait
    - #include <sys/types.h>
    - #include <sys/wait.h>
    - ```pid_t wait(int* status)```
    - ```WIFEXITED(wstatus)``` - returns true if the child terminated normally, that is, by calling exit(3) or _exit(2), or by returning from main().
    - ```WEXITSTATUS(wstatus)``` - returns the exit status of the child. This macro should be employed only if WIFEXITED returned true.
    - on success, returns the process ID of the terminated child; on error, -1 is returned.
```c
int processId = getpid();
int parentId = getppid();

int status;
char* message = "Successful";
wait(&status);
if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
    write(1, message, strlen(message));
    write(1, "\n", 1); \\ write new line
}
```
* #include <string.h>
    - strcmp
    - strlen

>>>>>>> c0f03b21449747029bcb138b035889fd95759cff

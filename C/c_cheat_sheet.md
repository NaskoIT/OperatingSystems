### Reading, sorting, writing
```c
int fd = open("filename", O_RDONLY); 
struct stat fileStats;
fstat(fd, &fileStats);
int size = fileStats.st_size;
if (size % sizeof(uint32_t) != 0) {
    err(1, "Invalid file content");
}

uint32_t* arr = (uint32_t)malloc(size);
read(fd, arr, size);

qsort(arr, size / sizeof(uint32_t), sizeof(uint32_t), comparator);

int fd2 = open("destination_file_name", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
write(fd2, arr, size);

free(arr);
close(fd);
close(fd2);
```

### Read and write using buffer
```c
int fd = open(...); // read mode
int fd2 = open(...); // write mode
char buffer[4096];
int read_size = 0;
while((read_size = read(fd, &buffer, sizeof(buffer))) > 0) {
    write(fd2, &buffer, read_size);
}
```

### Working with strings
```c
char* test = "nasko.it";
int len = strlen(test); //8

// char *strcat(char *dest, const char *src);
strcat(dirpath, "/");

// char *strcpy(char *dest, const char *src);
strcpy(test, "atanas");

// int strcmp(const char *s1, const char *s2);
// 0, if the s1 and s2 are equal;
// a negative value if s1 is less than s2;
// a positive value if s1 is greater than s2.
int result = strcmp("nasko", "atanas"); // positive value
```

### Check on files and directories
```c
// W_OK, R_OK, X_OK, F_OK (existence)
// checks if a directory is writable
if(access(dirpath, W_OK) == -1) {
    err(3,"dir: '%s' is not writable", dirpath);
}

// Check is directory
struct stat buffer;
stat(dirpath, &buffer);
if (!S_ISDIR(buffer.st_mode)) { // not directory }
if (stat.st_mode & S_IRUSR) { // user has read permissions }
if (stat.st_mode & S_IWUSR) { // user has write permissions}
```

### Helpers
* atoi()
* sprintf()
* dprintf()
* <stdint.h>
* __attributes__(packed)
* Shift + K - open the man page
* in normal mode * - highlight the word under the cursor
* :%s/word/new_word
* gg=G


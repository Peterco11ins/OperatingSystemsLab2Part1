#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>     // fork, getpid, write

#define MAX_COUNT 200
#define BUF_SIZE  100

int main(void) {
    pid_t pid;
    int i;
    char buf[BUF_SIZE];

    fork();                 // after this call there are TWO processes
    pid = getpid();         // each process has its own PID

    for (i = 1; i <= MAX_COUNT; i++) {
        sprintf(buf, "This line is from pid %d, value %d\n", (int)pid, i);
        write(1, buf, (unsigned)strlen(buf));   // unbuffered stdout
    }

    return 0;
}
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>     // fork, getpid
#include <sys/wait.h>   // waitpid

#define MAX_COUNT 200

void ChildProcess(void);
void ParentProcess(void);

int main(void) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        ChildProcess();
    } else {
        ParentProcess();
        // Optional: wait so the parent prints "done" after child
        int status;
        waitpid(pid, &status, 0);
    }
    return 0;
}

void ChildProcess(void) {
    int i;   // declare variable at top
    for (i = 1; i <= MAX_COUNT; i++) {
        printf("   This line is from child, value = %d\n", i);
    }
    printf("   *** Child process is done ***\n");
}

void ParentProcess(void) {
    int i;   // declare variable at top
    for (i = 1; i <= MAX_COUNT; i++) {
        printf("This line is from parent, value = %d\n", i);
    }
    printf("*** Parent is done ***\n");
}
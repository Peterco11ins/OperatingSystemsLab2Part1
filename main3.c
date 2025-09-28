#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>      // fork, getpid, getppid, sleep
#include <sys/types.h>   // pid_t
#include <sys/wait.h>    // wait, WEXITSTATUS

void child_process(void);

int main(void) {
    int i;          // declare loop counter here
    pid_t pid;

    // create exactly 2 children
    for (i = 0; i < 2; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            return 1;
        }
        if (pid == 0) {
            child_process();
            _exit(0); // safety: ensure child exits
        }
    }

    // parent waits for both children
    for (i = 0; i < 2; i++) {
        int status = 0;
        pid_t completed = wait(&status);
        if (completed == -1) {
            perror("wait");
            return 1;
        }
        if (WIFEXITED(status)) {
            printf("Child pid %d completed with exit status %d\n",
                   completed, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child pid %d terminated by signal %d\n",
                   completed, WTERMSIG(status));
        } else {
            printf("Child pid %d ended (status=0x%x)\n", completed, status);
        }
    }
    return 0;
}

void child_process(void) {
    pid_t pid = getpid();
    pid_t ppid = getppid();

    int k;  // loop counter declared outside the for loop

    // seed RNG per process
    srandom((unsigned)(pid ^ (pid >> 16)));

    // each child sleeps and wakes twice
    for (k = 0; k < 2; k++) {
        int sleep_secs = 1 + (int)(random() % 10);  // 1..10
        printf("Child pid %d sleeping for %d second(s)…\n", pid, sleep_secs);
        fflush(stdout);
        sleep(sleep_secs);
        printf("Child pid %d is awake! Where is my parent %d?\n", pid, ppid);
    }

    exit(0);
}


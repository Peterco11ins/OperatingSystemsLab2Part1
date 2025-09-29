#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>      // fork, getpid, getppid, sleep
#include <sys/types.h>   // pid_t
#include <sys/wait.h>    // wait, WEXITSTATUS

void child_process(void);

int main(void) {
    int i;          // loop counter
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
            _exit(0); // ensure child terminates
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
            printf("Child Pid: %d has completed with exit status %d\n",
                   completed, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child Pid: %d terminated by signal %d\n",
                   completed, WTERMSIG(status));
        } else {
            printf("Child Pid: %d ended abnormally (status=0x%x)\n",
                   completed, status);
        }
    }
    return 0;
}

void child_process(void) {
    pid_t pid = getpid();
    pid_t ppid = getppid();
    int k, loops, sleep_secs;

    // seed RNG uniquely per process
    srandom((unsigned)(pid ^ (pid >> 16)));

    // random number of iterations, up to 30
    loops = 1 + (int)(random() % 30);

    for (k = 0; k < loops; k++) {
        sleep_secs = 1 + (int)(random() % 10);  // 1–10 seconds
        printf("Child Pid: %d is going to sleep for %d second(s)!\n",
               pid, sleep_secs);
        fflush(stdout); // flush so it prints before sleeping
        sleep(sleep_secs);
        printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n",
               pid, ppid);
    }

    exit(0);
}


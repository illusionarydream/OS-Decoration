#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    pid_t forkid;
    forkid = fork();
    switch (forkid) {
        case -1:
            printf("Error: Failed to fork.\n");
            break;
        case 0:
            // Child process
            execl("./MyCopy", "MyCopy", argv[1], argv[2], NULL);
            break;
        default:
            wait(NULL);
            break;
    }
    return 0;
}
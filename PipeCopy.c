#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct timeval start, end;

    gettimeofday(&start, NULL);

    int mypipe[2];
    if (pipe(mypipe)) {
        fprintf(stderr, "Pipe failed.\n");
        return -1;
    }

    pid_t forkid_read;
    pid_t forkid_write;
    forkid_read = fork();

    switch (forkid_read) {
        case -1:
            printf("Error: Failed to fork.\n");
            break;
        case 0: {
            clock_t start_, end_;
            start_ = clock();

            FILE *src;

            // Child process
            ssize_t write(int pipefd, const void *buf, size_t count);

            // Open source file
            src = fopen(argv[1], "r");
            // Check for file error
            if (src == NULL) {
                printf("Error: Could not open file '%s'.\n", argv[1]);
                exit(-1);
            }

            char ch;
            while ((ch = fgetc(src)) != EOF)
                write(mypipe[1], &ch, 1);

            close(mypipe[1]);

            fclose(src);

            gettimeofday(&end, NULL);
            long run_time_in_microseconds;
            run_time_in_microseconds = end.tv_usec - start.tv_usec;
            printf("Writer: executable time for quick sort single threaded is %dmicroseconds.\n", run_time_in_microseconds);

            break;
        }

        default: {
            forkid_write = fork();
            close(mypipe[1]);

            if (forkid_write == 0) {
                FILE *dest;

                // Child process
                ssize_t read(int pipefd, void *buf, size_t count);

                // Open destination file
                dest = fopen(argv[2], "w+");

                // Check for file error
                if (dest == NULL) {
                    printf("Error: Could not open file '%s'.\n", argv[2]);
                    exit(-1);
                }
                char ch;
                while (read(mypipe[0], &ch, 1) > 0) {
                    fputc(ch, dest);
                }

                close(mypipe[0]);
                fclose(dest);

                gettimeofday(&end, NULL);
                long run_time_in_microseconds;
                run_time_in_microseconds = end.tv_usec - start.tv_usec;
                printf("Reader: executable time for quick sort single threaded is %dmicroseconds.\n", run_time_in_microseconds);

            } else {
                close(mypipe[0]);

                waitpid(forkid_read, NULL, 0);
                waitpid(forkid_write, NULL, 0);

                gettimeofday(&end, NULL);
                long run_time_in_microseconds;
                run_time_in_microseconds = end.tv_usec - start.tv_usec;
                printf("Father: executable time for quick sort single threaded is %dmicroseconds.\n", run_time_in_microseconds);
            }
            break;
        }
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void make_copy(FILE *src, FILE *dest) {
    char buffer[1024];
    char ch;
    int num = 0;
    while ((ch = fgetc(src)) != EOF) {
        buffer[num] = ch;
        num++;
    }

    for (int i = 0; i < num; i++)
        fputc(buffer[i], dest);
}

int main(int argc, char *argv[]) {
    clock_t start, end;

    start = clock();

    FILE *src;
    // Open source file
    src = fopen(argv[1], "r");
    // Check for file error
    if (src == NULL) {
        printf("Error: Could not open file '%s'.\n", argv[1]);
        exit(-1);
    }

    FILE *dest;
    // Open destination file
    dest = fopen(argv[2], "w+");
    // Check for file error
    if (dest == NULL) {
        printf("Error: Could not open file '%s'.\n", argv[2]);
        fclose(src);
        exit(-1);
    }

    make_copy(src, dest);

    fclose(dest);

    end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", elapsed_time);
    return 0;
}
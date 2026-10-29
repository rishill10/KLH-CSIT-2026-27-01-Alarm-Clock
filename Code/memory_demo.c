#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int global_value = 10;

int main(void) {
    int *heap_value = malloc(sizeof(int));
    if (!heap_value) {
        perror("malloc");
        return 1;
    }

    *heap_value = 20;

    printf("Before fork: PID=%d, global=%d, heap=%d\n",
           (int)getpid(), global_value, *heap_value);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        free(heap_value);
        return 1;
    }

    if (pid == 0) {
        global_value = 99;
        *heap_value = 88;
        printf("Child:  PID=%d, global=%d, heap=%d\n",
               (int)getpid(), global_value, *heap_value);
        free(heap_value);
        return 0;
    }

    waitpid(pid, NULL, 0);
    printf("Parent: PID=%d, global=%d, heap=%d\n",
           (int)getpid(), global_value, *heap_value);

    free(heap_value);
    return 0;
}

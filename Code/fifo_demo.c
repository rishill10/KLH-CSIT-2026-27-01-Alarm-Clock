#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME "alarm_fifo"

int main(void) {
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        /* It may already exist; continue. */
    }

    printf("FIFO receiver waiting on %s ...\n", FIFO_NAME);

    int fd = open(FIFO_NAME, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char buffer[256];
    ssize_t n = read(fd, buffer, sizeof(buffer) - 1);

    if (n > 0) {
        buffer[n] = '\0';
        printf("Received through FIFO: %s\n", buffer);
    }

    close(fd);
    unlink(FIFO_NAME);
    return 0;
}

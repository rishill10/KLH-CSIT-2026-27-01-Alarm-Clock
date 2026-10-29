#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_NAME "alarm_fifo"

int main(void)
{
    printf("====================================\n");
    printf("        CO-3 FIFO IPC SENDER\n");
    printf("====================================\n\n");

    printf("Opening FIFO for writing...\n");

    int fd = open(FIFO_NAME, O_WRONLY);

    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    const char *message =
        "Hello from FIFO sender - IPC message received!";

    printf("Sending message through FIFO...\n");

    ssize_t n = write(fd, message, strlen(message));

    if (n < 0)
    {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Message sent successfully.\n");
    printf("Bytes written: %zd\n", n);

    close(fd);

    printf("FIFO sender finished.\n");

    return 0;
}

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILE_NAME "file_demo.txt"

int main(void)
{
    int fd;
    char buffer[200];

    printf("====================================\n");
    printf("       CO-5 FILE I/O DEMONSTRATION\n");
    printf("====================================\n\n");

    /* -------------------------------
       OPEN FILE FOR WRITING
       ------------------------------- */

    printf("[1] Opening file for writing...\n");

    fd = open(
        FILE_NAME,
        O_WRONLY | O_CREAT | O_TRUNC,
        0644
    );

    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    printf("    File opened successfully.\n");
    printf("    File Descriptor = %d\n\n", fd);


    /* -------------------------------
       WRITE TO FILE
       ------------------------------- */

    const char *message =
        "CO-5 File I/O Demo\n"
        "Demonstrating open(), write(), read(), and close().\n";

    printf("[2] Writing data to file...\n");

    ssize_t bytes_written =
        write(
            fd,
            message,
            strlen(message)
        );

    if (bytes_written < 0)
    {
        perror("write");
        close(fd);
        return 1;
    }

    printf("    Bytes written = %zd\n\n", bytes_written);


    /* -------------------------------
       CLOSE FILE
       ------------------------------- */

    printf("[3] Closing file...\n");

    close(fd);

    printf("    File closed successfully.\n\n");


    /* -------------------------------
       OPEN FILE FOR READING
       ------------------------------- */

    printf("[4] Opening file for reading...\n");

    fd = open(
        FILE_NAME,
        O_RDONLY
    );

    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    printf("    File opened successfully.\n");
    printf("    File Descriptor = %d\n\n", fd);


    /* -------------------------------
       READ FROM FILE
       ------------------------------- */

    printf("[5] Reading data from file...\n\n");

    ssize_t bytes_read =
        read(
            fd,
            buffer,
            sizeof(buffer) - 1
        );

    if (bytes_read < 0)
    {
        perror("read");
        close(fd);
        return 1;
    }

    buffer[bytes_read] = '\0';

    printf("----- FILE CONTENT -----\n");
    printf("%s", buffer);
    printf("------------------------\n\n");

    printf("    Bytes read = %zd\n\n", bytes_read);


    /* -------------------------------
       CLOSE FILE
       ------------------------------- */

    printf("[6] Closing file...\n");

    close(fd);

    printf("    File closed successfully.\n\n");


    printf("====================================\n");
    printf("       FILE I/O DEMO COMPLETED\n");
    printf("====================================\n");

    return 0;
}

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define MAX_ALARMS 50
#define LOG_FILE "alarm_log.txt"

typedef struct {
    int id;
    pid_t pid;
    unsigned int delay;
    int active;
} Alarm;

static Alarm alarms[MAX_ALARMS];
static int alarm_count = 0;
static int next_id = 1;

static void write_log(const char *event, int id, pid_t pid, unsigned int delay) {
    int fd = open(LOG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) { perror("open"); return; }

    char line[256];
    int n = snprintf(line, sizeof(line),
                     "%ld | %s | id=%d | pid=%d | delay=%u\n",
                     (long)time(NULL), event, id, (int)pid, delay);
    if (n > 0) (void)write(fd, line, (size_t)n);
    close(fd);
}

static void alarm_handler(int signo) {
    (void)signo;
    const char msg[] = "\n*** ALARM TRIGGERED ***\n";
    (void)write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

static void run_alarm_child(int id, unsigned int delay) {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = alarm_handler;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        _exit(1);
    }

    printf("Alarm %d started in child PID %d. Waiting %u seconds...\n",
           id, (int)getpid(), delay);
    fflush(stdout);

    alarm(delay);
    pause();
    _exit(0);
}

static int find_alarm(int id) {
    for (int i = 0; i < alarm_count; i++)
        if (alarms[i].id == id) return i;
    return -1;
}

static void set_alarm(void) {
    if (alarm_count >= MAX_ALARMS) {
        printf("Maximum number of alarms reached.\n");
        return;
    }

    unsigned int delay;
    printf("Enter delay in seconds: ");
    if (scanf("%u", &delay) != 1 || delay == 0) {
        printf("Invalid delay.\n");
        while (getchar() != '\n');
        return;
    }

    int id = next_id++;
    fflush(stdout); /* Prevent duplicated buffered output after fork(). */
    pid_t pid = fork();

    if (pid < 0) { perror("fork"); return; }

    if (pid == 0) run_alarm_child(id, delay);

    alarms[alarm_count++] = (Alarm){id, pid, delay, 1};
    write_log("SET", id, pid, delay);
    printf("Alarm %d created. Child PID = %d\n", id, (int)pid);
}

static void view_alarms(void) {
    if (alarm_count == 0) {
        printf("No alarms created in this run.\n");
        return;
    }

    printf("\n%-6s %-10s %-10s %-18s\n", "ID", "PID", "DELAY", "STATUS");
    printf("------------------------------------------------\n");

    for (int i = 0; i < alarm_count; i++) {
        printf("%-6d %-10d %-10u %-18s\n",
               alarms[i].id, (int)alarms[i].pid, alarms[i].delay,
               alarms[i].active ? "ACTIVE" : "DONE/CANCELLED");
    }
}

static void cancel_alarm(void) {
    int id;
    printf("Enter alarm ID to cancel: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        while (getchar() != '\n');
        return;
    }

    int index = find_alarm(id);
    if (index == -1) { printf("Alarm not found.\n"); return; }
    if (!alarms[index].active) { printf("Alarm is already inactive.\n"); return; }

    if (kill(alarms[index].pid, SIGTERM) == -1) {
        perror("kill");
        return;
    }

    (void)waitpid(alarms[index].pid, NULL, 0);
    alarms[index].active = 0;

    write_log("CANCEL", alarms[index].id,
              alarms[index].pid, alarms[index].delay);
    printf("Alarm %d cancelled.\n", id);
}

static void reap_finished_children(void) {
    int status;

    for (int i = 0; i < alarm_count; i++) {
        if (!alarms[i].active) continue;

        pid_t result = waitpid(alarms[i].pid, &status, WNOHANG);

        if (result == alarms[i].pid) {
            alarms[i].active = 0;
            write_log("TRIGGERED", alarms[i].id,
                      alarms[i].pid, alarms[i].delay);
            printf("\n[Manager] Alarm %d has finished.\n", alarms[i].id);
        }
    }
}

static void show_log(void) {
    int fd = open(LOG_FILE, O_RDONLY);

    if (fd < 0) {
        if (errno == ENOENT) { printf("No log file yet.\n"); return; }
        perror("open");
        return;
    }

    char buffer[1024];
    ssize_t n;

    printf("\n===== ALARM LOG =====\n");
    while ((n = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[n] = '\0';
        printf("%s", buffer);
    }
    close(fd);
}

int main(void) {
    int choice;

    printf("====================================\n");
    printf("       LINUX / POSIX ALARM CLOCK\n");
    printf("====================================\n");
    printf("Manager PID: %d\n", (int)getpid());

    while (1) {
        reap_finished_children();

        printf("\n1. Set alarm\n");
        printf("2. View alarms\n");
        printf("3. Cancel alarm\n");
        printf("4. View alarm log\n");
        printf("5. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: set_alarm(); break;
            case 2: view_alarms(); break;
            case 3: cancel_alarm(); break;
            case 4: show_log(); break;
            case 5:
                printf("Cleaning up active alarms...\n");
                for (int i = 0; i < alarm_count; i++) {
                    if (alarms[i].active) {
                        kill(alarms[i].pid, SIGTERM);
                        waitpid(alarms[i].pid, NULL, 0);
                    }
                }
                printf("Goodbye.\n");
                return 0;
            default: printf("Choose 1-5.\n");
        }
    }
}

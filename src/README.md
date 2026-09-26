
# Linux/POSIX Alarm Clock - OS Project

## Main project
`alarm_clock.c` is the main demonstration project.

It demonstrates:
- CO-1: system calls, user-space program, terminal/shell execution
- CO-2: process creation and management using fork(), PID, waitpid()
- CO-3: POSIX signals using SIGALRM, sigaction(), kill()
- CO-5: low-level file I/O using open(), read(), write(), close()

The main program supports:
1. Set multiple alarms (each alarm is a child process)
2. View alarms
3. Cancel an alarm
4. View an alarm event log
5. Exit and clean up child processes

## macOS
The main program uses standard Unix/POSIX APIs available on macOS. The project title/presentation can still say "Linux-based" if your course requires that wording, but say that development/testing was performed on macOS and the APIs are POSIX/Unix APIs. Do not claim an Ubuntu-only feature was tested on macOS.

## Compile
clang alarm_clock.c -o alarm_clock
./alarm_clock

## CO-6 demonstration
clang thread_demo.c -o thread_demo -pthread
./thread_demo

## CO-4 / Copy-on-Write demonstration
clang memory_demo.c -o memory_demo
./memory_demo

## CO-3 FIFO demonstration
clang fifo_demo.c -o fifo_demo
./fifo_demo

In another terminal:
echo "SET 10" > alarm_fifo

## Presentation scope
The main Alarm Clock is the actual integrated project. The other files are focused demonstrations/extensions for course outcomes; they should not be presented as if they are all one integrated runtime unless you integrate them later.

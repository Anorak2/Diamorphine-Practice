#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

void handle_signal(int sig) {
    if (sig == 31) {
        printf("Received signal 31 in the child process.\n");
    }
}

int main() {
    pid_t pid;
    char input;

    // Set up signal handler for signal 31
    signal(31, handle_signal);

    // Driver program: wait for user input to fork
    printf("Press any key to fork a child process...\n");
    input = getchar();  // Wait for any input from the user

    // Fork the child process
    pid = fork();

    if (pid < 0) {
        // If fork failed
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child process started.\n");

        // First, wait for 25 seconds before sending signal 31 to itself
        printf("Child will wait 25 seconds before sending signal 31...\n");
        sleep(25);

        // Send signal 31 to itself
        printf("Sending signal 31 to itself...\n");
        kill(getpid(), 31);

        // Wait for another 15 seconds before terminating
        printf("Child will now wait 15 seconds before terminating...\n");
        sleep(15);

        // Child process terminates
        printf("Child process terminating.\n");
        exit(0);
    } else {
        // Parent process waits for the child to terminate
        wait(NULL);
        printf("Parent process: Child has terminated.\n");
		exit(0);
    }

    return 0;
}


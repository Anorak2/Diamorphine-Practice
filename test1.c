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

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        printf("Child process started.\n");

        printf("Child will wait before sending signal 31...\n");
        sleep(15);

        printf("Child is going invisible\n");
        kill(getpid(), 31);

        printf("Child will now wait before becoming visible again\n");
        sleep(15);

        kill(getpid(), 31);

        printf("Child will now wait before terminating\n");
        sleep(15);

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


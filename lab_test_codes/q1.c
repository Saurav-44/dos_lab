#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        // Error in fork
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
	printf("Child Process: PID = %d\n", getpid());
        while (1) {
            sleep(1); // Sleep for 1 second to simulate some work
        }
    } else {
        // Parent process
	printf("Parent Process: PID = %d\n", getpid());
	wait(NULL);
        printf("Child process has finished.\n");
    }

    return 0;
}


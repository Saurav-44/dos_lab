#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  

    if (pid < 0) {
        
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        
	printf("Child Process: PID = %d\n", getpid());
        while (1) {
            sleep(1); 
        }
    } else {
        
	printf("Parent Process: PID = %d\n", getpid());
	wait(NULL);
        printf("Child process has finished.\n");
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function to generate Fibonacci series
void generateFibonacci(int *arr, int length) {
    arr[0] = 0;
    if (length > 1) {
        arr[1] = 1;
        for (int i = 2; i < length; i++) {
            arr[i] = arr[i - 1] + arr[i - 2];
        }
    }
}

int main() {
    int length;
    printf("Enter the length of the Fibonacci series: ");
    scanf("%d", &length);

    if (length <= 0) {
        printf("Length must be greater than 0.\n");
        return 1;
    }

    int fibArray[length]; // Array to hold Fibonacci numbers
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) { 
        // Child process
        close(pipefd[0]); // Close unused read end
        generateFibonacci(fibArray, length);
        write(pipefd[1], fibArray, length * sizeof(int));
        close(pipefd[1]); // Close write end
        exit(0);
    } else { 
        // Parent process
        close(pipefd[1]); // Close unused write end
        wait(NULL); // Wait for child to complete
        read(pipefd[0], fibArray, length * sizeof(int));
        close(pipefd[0]); // Close read end

        // Display the Fibonacci series
        printf("Fibonacci series:\n");
        for (int i = 0; i < length; i++) {
            printf("%d ", fibArray[i]);
        }
        printf("\n");

        // Find and display prime Fibonacci numbers
        printf("Prime Fibonacci numbers in the series:\n");
        for (int i = 0; i < length; i++) {
            if (isPrime(fibArray[i])) {
                printf("Position %d: %d\n", i + 1, fibArray[i]);
            }
        }
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define MAX 1024

void copyFileContent(const char *source, const char *destination) {
    char buffer[MAX];
    int srcFd = open(source, O_RDONLY);
    if (srcFd < 0) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    int destFd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destFd < 0) {
        perror("Error opening destination file");
        close(srcFd);
        exit(EXIT_FAILURE);
    }

    ssize_t bytesRead;
    while ((bytesRead = read(srcFd, buffer, MAX)) > 0) {
        if (write(destFd, buffer, bytesRead) != bytesRead) {
            perror("Error writing to destination file");
            close(srcFd);
            close(destFd);
            exit(EXIT_FAILURE);
        }
    }

    close(srcFd);
    close(destFd);
}


void displayFileContent(const char *filename) {
    char buffer[MAX];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, MAX, file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
}

void displaySortedReverseContent(const char *filename) {
    char *lines[MAX];
    char buffer[MAX];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int lineCount = 0;
    while (fgets(buffer, MAX, file) != NULL) {
        lines[lineCount] = strdup(buffer);
        lineCount++;
    }
    fclose(file);

    for (int i = 0; i < lineCount - 1; i++) {
        for (int j = i + 1; j < lineCount; j++) {
            if (strcmp(lines[i], lines[j]) < 0) {
                char *temp = lines[i];
                lines[i] = lines[j];
                lines[j] = temp;
            }
        }
    }

    // Display sorted lines
    for (int i = 0; i < lineCount; i++) {
        printf("%s", lines[i]);
        free(lines[i]);
    }
}

int main() {
    pid_t pid;
    const char *file1 = "file1.txt";
    const char *file2 = "file2.txt";

    for (int i = 1; i <= 3; i++) {
        pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Child process
            printf("Child %d created: PID = %d, PPID = %d\n", i, getpid(), getppid());

            if (i == 1) {
                copyFileContent(file1, file2);
                printf("Child 1: Content copied from %s to %s\n", file1, file2);
            } else if (i == 2) {
                printf("Child 2: Displaying content of %s:\n", file2);
                displayFileContent(file2);
            } else if (i == 3) {
                printf("Child 3: Displaying sorted content of %s in reverse order:\n", file2);
                displaySortedReverseContent(file2);
            }

            exit(0);
        } else { // Parent process
            sleep(1);
        }
    }

    // Parent process waits for all children to finish
    while (wait(NULL) > 0)
        ;

    printf("Parent process (PID = %d): All child processes have completed.\n", getpid());
    return 0;
}

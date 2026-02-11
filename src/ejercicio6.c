#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

static void die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
   
    if (argc != 5) {
        fprintf(stderr, "Uso: %s comando1 arg1 comando2 arg2\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd[2];
    if (pipe(fd) == -1) die("pipe");

    pid_t pid = fork();
    if(pid < 0) die("fork");

    if (pid == 0) {
        if (dup2(fd[0], STDIN_FILENO) == -1) die("dup2 (hijo)");

        close(fd[0]);
        close(fd[1]);

        char *args2[] = { argv[3], argv[4], NULL };
        execvp(args2[0], args2);
        die("execvp (comando2)");
    } else {
        if (dup2(fd[1], STDOUT_FILENO) == -1) die("dup2 (padre)");

        close(fd[0]);
        close(fd[1]);


        char *args1[] = { argv[1], argv[2], NULL };
        execvp(args1[0], args1);
        die("execvp (comando1)");
    }

    return 0;
}

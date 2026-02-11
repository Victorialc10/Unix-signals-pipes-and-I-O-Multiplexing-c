#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

volatile sig_atomic_t borrar = 1;

void manejador(int sig) {
    if (sig == SIGUSR1) {
        borrar = 0;
    }
}

int main(int argc, char *argv[]) {
    struct sigaction sa;
    sigset_t mask, suspend_mask;
    int secs;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <segundos>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    secs = atoi(argv[1]);

    sa.sa_handler = manejador;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGALRM, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    alarm(secs);
    printf("Borrado programado en %d segundos\n", secs);

    sigemptyset(&suspend_mask);

    sigsuspend(&suspend_mask);

    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    if (borrar) {
        printf("Tiempo agotado. Borrando ejecutable...\n");
        if (unlink(argv[0]) == -1) {
            perror("unlink");
        }
    } else {
        printf("Borrado cancelado por SIGUSR1\n");
    }

    return 0;
}

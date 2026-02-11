#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

volatile sig_atomic_t cont_int = 0;
volatile sig_atomic_t cont_tstp = 0;
volatile sig_atomic_t total = 0;

void manejador(int sig) {
    if (sig == SIGINT) {
        cont_int++;
    } else if (sig == SIGTSTP) {
        cont_tstp++;
    }
    total++;
}

int main(void) {
    struct sigaction sa;

    sa.sa_handler = manejador;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTSTP, &sa, NULL);

    printf("Esperando señales (Ctrl+C = SIGINT, Ctrl+Z = SIGTSTP)\n");

    while (total < 10) {
        pause();
    }

    printf("\nPrograma finalizado\n");
    printf("SIGINT recibidas: %d\n", cont_int);
    printf("SIGTSTP recibidas: %d\n", cont_tstp);

    return 0;
}

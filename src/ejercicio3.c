#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void) {
    sigset_t bloqueadas, pendientes;
    int sleep_secs;

    char *env = getenv("SLEEP_SECS");
    if (env == NULL) {
        fprintf(stderr, "SLEEP_SECS no definida\n");
        exit(EXIT_FAILURE);
    }
    sleep_secs = atoi(env);

    sigemptyset(&bloqueadas);
    sigaddset(&bloqueadas, SIGINT);
    sigaddset(&bloqueadas, SIGTSTP);

    sigprocmask(SIG_BLOCK, &bloqueadas, NULL);

    printf("SIGINT y SIGTSTP bloqueadas. Durmiendo %d segundos...\n", sleep_secs);
    sleep(sleep_secs);

    sigpending(&pendientes);

    if (sigismember(&pendientes, SIGINT)) {
        printf("Se recibió SIGINT durante el sleep\n");
    }

    if (sigismember(&pendientes, SIGTSTP)) {
        printf("Se recibió SIGTSTP durante el sleep\n");
        printf("Desbloqueando SIGTSTP. El proceso se detendrá ahora.\n");

        sigset_t desbloquear;
        sigemptyset(&desbloquear);
        sigaddset(&desbloquear, SIGTSTP);
        sigprocmask(SIG_UNBLOCK, &desbloquear, NULL);
    }

    printf("Programa finalizando normalmente\n");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static void die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(void) {
   
    int p_h[2], h_p[2];
    char buffer[256];
    char confirm;
    int contador = 0;

    if (pipe(p_h) == -1) die("pipe");
    if (pipe(h_p) == -1) die("pipe");

    pid_t pid = fork();
    if(pid < 0) die("fork");

    if (pid > 0) {

        close(p_h[0]);
        close(h_p[1]);

        while (1) {
            printf("Padre: escribe un mensaje: ");
            fgets(buffer, 256, stdin);

            write(p_h[1], buffer, strlen(buffer));

            read(h_p[0], &confirm, 1);

            if (confirm == 'q') {
                printf("Padre: recibido 'q', terminando\n");
                break;
            }
        }

        close(p_h[1]);
        close(h_p[0]);

    } else {
        close(p_h[1]);
        close(h_p[0]);

        while(1){
            read(p_h[0], buffer, 256);
            printf("Hijo recibe: %s", buffer);

            sleep(1);

            contador++;
            if(contador == 10){
                confirm = 'q';
                write(h_p[1], &confirm, 1);
                break;
            }
            else{
                confirm = 'l';
                 write(h_p[1], &confirm, 1);
            }
        }
        close(p_h[0]);
        close(h_p[1]);
        exit(0);        
    }

    return 0;
}

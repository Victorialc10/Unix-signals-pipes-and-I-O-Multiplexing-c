#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 256

/* First:
mkfifo fifo1
mkfifo fifo2

*/

int abrir_fifo(const char *nombre) {
    int fd = open(nombre, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    return fd;
}

int main(void) {
    int fd1, fd2;
    char buffer[BUF_SIZE];

    fd1 = abrir_fifo("fifo1");
    fd2 = abrir_fifo("fifo2");

    while (1) {
        fd_set set;
        int maxfd;
        ssize_t n;

        FD_ZERO(&set);
        FD_SET(fd1, &set);
        FD_SET(fd2, &set);

        maxfd = (fd1 > fd2 ? fd1 : fd2) + 1;

        if (select(maxfd, &set, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        /* FIFO 1 */
        if (FD_ISSET(fd1, &set)) {
            n = read(fd1, buffer, BUF_SIZE - 1);
            if (n == 0) {
                close(fd1);
                fd1 = abrir_fifo("fifo1");
            } else if (n > 0) {
                buffer[n] = '\0';
                printf("[fifo1] %s", buffer);
            }
        }

        /* FIFO 2 */
        if (FD_ISSET(fd2, &set)) {
            n = read(fd2, buffer, BUF_SIZE - 1);
            if (n == 0) {
                close(fd2);
                fd2 = abrir_fifo("fifo2");
            } else if (n > 0) {
                buffer[n] = '\0';
                printf("[fifo2] %s", buffer);
            }
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s <mensaje>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd = open("mi_fifo", O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    write(fd, argv[1], strlen(argv[1]));
    write(fd, "\n", 1);

    close(fd);
    return 0;
}

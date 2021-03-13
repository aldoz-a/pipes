// writer.c - main processo figlio
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "data.h"

// funzione main()
int main(int argc, char *argv[])
{
    // apro il file fifo (named pipe) in modo scrittura
    printf("processo %d partito\n", getpid());
    int fd;
    if ((fd = open(FIFO_PATH, O_WRONLY)) == -1) {
        // errore di apertura
        printf("%s: non posso aprire il file fifo (%s)\n", argv[0], strerror(errno));
        exit(EXIT_FAILURE);
    }

    // loop di scrittura messaggi per il reader
    Data my_data;
    my_data.index = 0;
    do {
        // test index per forzare l'uscita
        if (my_data.index == N_MESSAGES) {
            // il processo chiude il file fifo ed esce per indice raggiunto
            printf("processo %d terminato (text=%s index=%ld)\n", getpid(), my_data.text, my_data.index);
            close(fd);
            exit(EXIT_SUCCESS);
        }

        // compongo il messaggio e lo invio
        my_data.index++;
        snprintf(my_data.text, sizeof(my_data.text), "un-messaggio-di-test:%ld", my_data.index);
    } while (write(fd, &my_data, sizeof(Data)) != -1);

    // il processo chiude il file fifo ed esce per altro motivo (errore)
    printf("processo %d terminato con errore (%s)\n", getpid(), strerror(errno));
    close(fd);
    exit(EXIT_FAILURE);
}

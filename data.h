#ifndef DATA_H
#define DATA_H

// path del file fifo (named pipe)
#define FIFO_PATH   "myfifo"

// numero di messaggi da scambiare per il benchmark
#define N_MESSAGES  2000000

// struttura Data per i messaggi
typedef struct {
    unsigned long index;        // indice dei dati
    char          text[1024];   // testo dei dati
} Data;

#endif /* DATA_H */

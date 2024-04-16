#include <czmq.h>
#include <stdio.h>

#define SERVER_ADDR "localhost"

int main () {
    const char *server_address = "tcp://" SERVER_ADDR ":3000";

    zsock_t *sock = zsock_new(ZMQ_PULL);
    if (!sock) {
        printf("Error al crear el socket\n");
        return -1;
    }

    // Conectar el socket al servidor
    int rc = zsock_connect(sock, "%s", server_address);
    if (rc != 0) {
        printf("Error al conectar el socket al servidor\n");
        zsock_destroy(&sock);
        return -1;
    }

    printf("Worker conectado al servidor en %s\n", server_address);

    while (!zsys_interrupted) {
        char *msg = zstr_recv(sock);
        if (!msg) {
            printf("Error al recibir el mensaje\n");
            break;
        }
        printf("Procesado \"%s\"\n", msg);
        free(msg);
    }

    zsock_destroy(&sock);
    return 0;
}
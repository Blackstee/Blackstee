#include <stdio.h>
#include <stdlib.h>

#include "server.h"
#include "http.h"
#include "musicians.h"
#include "socket.h"


int main(void) {

    const int sPort = 5000;
    lib_init();
    socket_t * server_sock = socket_new();
    if (socket_bind(server_sock, sPort) == SOCKET_ERR)
    {
        printf("Port %i can't be binded\n", sPort);
        exit(1);
    } else
        printf("Binded on port %i\n", sPort);
    socket_listen(server_sock);

    char buf[10000];
    socket_t * client = NULL;

    while (1) {
        printf("Clients are being accepted\n");
        client = socket_accept(server_sock);
        if (NULL == client) {
            printf("NULL client\n");
            exit(1);
        }
        int readStatus = socket_read(client, buf, sizeof(buf));
        if (0 >= readStatus) {
            printf("Skipping empty request.\n");
            socket_close(client);
            socket_free(client);
            continue;
        }
        printf(">> Got request (read %i):\n`%s`\n", readStatus, buf);

        http_request_t request = http_request_parse(buf);

            if (strcmp(request.uri, "/") == 0)
              server_homepage(client);
            else
               if (strcmp(request.uri, "/musicians") == 0 || strcmp(request.uri, "/musicians/") == 0)
                  server_allMusicians(client, &request);
               else
                   if (strstr(request.uri, "/musicians/") == request.uri)
                      server_musicianById(client, &request, request.uri);
                   else
                     server_notFound(client);
    }
    socket_free(server_sock);
    lib_free();
    return 0;
}

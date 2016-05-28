#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <windows.h>
#include <sqlite3.h>
#include<ctype.h>
#include<winsock2.h>


#include "db_manager.h"
#include "fs.h"
#include "http.h"
#include "list.h"
#include "socket.h"
#include "server.h"


int main()
{
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
               if (strcmp(request.uri, "/info") == 0 || strcmp(request.uri, "/info/") == 0)
                  server_info (client);
               else
                 if (strcmp(request.uri, "/external") == 0)
                    server_external(client);
                 else
                        if (strcmp(request.uri, "/database") == 0)
                       server_homepage(client);
                       // server_database (client);
                       else
                        if
                        (strstr(request.uri, "/files/") == request.uri)
                           server_files(client, &request, request.uri);
                 else  server_notFound(client);
    }
    socket_free(server_sock);
    lib_free();
    return 0;
}

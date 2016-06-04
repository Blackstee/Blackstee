#include <stdio.h>
#include <stdlib.h>

#include "Web.h"
#include "http.h"
#include "Resource.h"
#include "socket.h"
#include <string.h>


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
    mus_arr_t * mus_arr = mus_arr_t_new();
    musician_t * musicians[3];
    for (int i = 0; i < sizeof(musicians) / sizeof(musicians[0]); i++)
		musicians[i] = musician_t_new();
	musician_t_add_info(musicians[0], 0, "Peter", "Petrovich", "1988-05-05", 2000, 4.3, "guitarist", "rock");
	musician_t_add_info(musicians[1], 1, "Gadya", "Petrovich", "1968-04-06", 1998, 4.6, "drummer", "classic");
	musician_t_add_info(musicians[2], 2, "Ivan", "Petrovich", "1958-03-08",1967, 4.1, "pianist", "pop");
	for (int i = 0; i < sizeof(musicians) / sizeof(musicians[0]); i++)
		mus_arr_t_add_back(mus_arr, musicians[i]);

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
              server_json_homepage(client);
            else
               if (strcmp(request.uri, "/api/musicians") == 0 || strcmp(request.uri, "/api/musicians/") == 0)
                  server_json_allMusicians(client, &request, mus_arr);
               else
                   if (strstr(request.uri, "/api/musicians/") == request.uri)
                      server_json_musicianById(client, &request, request.uri, mus_arr);
                      else
                        if (strcmp(request.uri, "/api") == 0)
                           server_html_homepage(client);
                           else
                            if (strcmp(request.uri, "/musicians") == 0 || strcmp(request.uri, "/musicians/") == 0)
                               server_html_allMusicians(client, &request, mus_arr);
                               else
                                  if (strstr(request.uri, "/musicians/") == request.uri)
                                     server_html_musicianById(client, &request, request.uri, mus_arr);
                                     else
                                        if (strcmp(request.uri, "/new_musician") == 0 || strcmp(request.uri, "/new_musician/"))
                                            server_html_new_musician(mus_arr, client);
                   else
                     server_notFound(client);
    }
    socket_free(server_sock);
    lib_free();
    return 0;
}

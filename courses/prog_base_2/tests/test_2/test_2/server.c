#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "server.h"
#include "http.h"
#include "info.h"
#include "socket.h"
#include "list.h"


//=======================================HOMEPAGE=================================
void server_homepage(socket_t * client)
{
    char homeBuf[10240];
    const char * htmlText =
        "<head>"
            "<title>Musician's server</title></head>"
        "<body>"
            "<h1>Hello! It's a homepage</h1>"
        "</body>";
    sprintf(homeBuf,
        "HTTP/1.1 200 OK\n"
        "Content-Type: text/html\n"
        "Content-Length: %zu\n"
        "Connection: keep-alive\n"
        "\n%s", strlen(htmlText), htmlText);
    socket_write_string(client, homeBuf);
    socket_close(client);
}
//=======================================for info======================================

void server_info (socket_t * client)
{
	char buffer[1024];
	char * Info = info_toJSON("Nastya Shapovalova", "KP-51", 15);
	sprintf(buffer,
		"HTTP/1.1 200 OK\n"
		"Content-Type: application/json\n"
		"Content-Length: %d\n"
		"Connection: keep-alive\r\n\r\n"
		"%s", strlen(Info), Info);
	socket_write_string(socket, buffer);
}

//=====================================server not found===========================
void server_notFound(socket_t * client)
 {
    char replyBuf[1024];
    const char * htmlText = "<h1>404 Page Not Found!</h1>";
    sprintf(replyBuf,
        "HTTP/1.1 404 ERROR \n"
        "Content-Type: text/html\n"
        "Content-Length: %zu\n"
        "\n%s", strlen(htmlText), htmlText);
    socket_write_string(client, replyBuf);
    socket_close(client);
}

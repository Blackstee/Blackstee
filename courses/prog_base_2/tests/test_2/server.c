#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "server.h"
#include "http.h"
#include "info.h"
#include "socket.h"
#include "list.h"
#include "db_manager.h"
#include "musicians.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define PORT 5000

//==========================client===================================

void send_request1(SOCKET recvSocket, const char * host_name)
{
    char request[200];
    sprintf(request, "GET /test/var/15?format=json HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);  // add Host header with host_name value
    send(recvSocket, request, strlen(request), 0);
}

void rec_answer (SOCKET recvSocket, char * buffer)
{
    int numrcv = recv(recvSocket, buffer, 1000, 0);
	if (numrcv == SOCKET_ERROR)
	{
		printf("ERROR: recvfrom unsuccessful\r\n");
		int status = closesocket(recvSocket);
		if (status == SOCKET_ERROR)
			printf("ERROR: closesocket unsuccessful\r\n");
		status = WSACleanup();
		if (status == SOCKET_ERROR)
			printf("ERROR: WSACleanup unsuccessful\r\n");
		system("pause");
		return;
	}
}

static SOCKET Socket_create()
{
    SOCKET Socket;
    puts("Creating socket...");
    if((Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    puts("Socket created.");
    return Socket;
}

char * getString(SOCKET Socket, char* reply)
{
    char stringJSON[40];
    char* str;
    reply = strstr(reply, "Content-Length:");
    str = strtok(reply, "\n");
    str = strtok(NULL, "\n");
    str = strtok(NULL, "\n");
    strcpy(stringJSON, str);
    stringJSON[strlen(stringJSON)] = '\0';
    return stringJSON;
}

char * get_data ()
{
    SOCKET Socket;
    struct sockaddr_in recvSockAddr;
    struct hostent * rHost;
    char* ip;
   const char * host_name = "pb-homework.appspot.com";
    char buffer[1000];
    memset(buffer,0,1000);
    Socket = Socket_create();
    rHost = gethostbyname(host_name);
    ip = inet_ntoa(*(struct in_addr *)*rHost->h_addr_list);
	printf("IP address is: %s\n", ip);
    memset(&recvSockAddr, 0, sizeof(recvSockAddr));
    recvSockAddr.sin_addr.s_addr = inet_addr(ip);
    recvSockAddr.sin_family = AF_INET;
    recvSockAddr.sin_port = htons(80);
    if(connect(Socket, (struct sockaddr *)&recvSockAddr, sizeof(recvSockAddr)) == SOCKET_ERROR)
    {
        puts("Socket connect error");
        closesocket(Socket);
        WSACleanup();
        return;
    }
   send_request1(Socket, host_name);
    //Receiving the answer
    rec_answer (Socket, buffer);
    puts(buffer);
    char stringJSON[100];
    strcpy(stringJSON, getString(Socket, buffer));
    return stringJSON;
}

//=====================================external===================================

void server_external(socket_t * client)
{
     char buffer [1024];
     const char * external = get_data ();
     sprintf(buffer,
		"HTTP/1.1 200 OK\n"
		"Content-Type: application/json\n"
		"Content-Length: %d\n"
		"Connection: keep-alive\r\n\r\n"
		"%s", strlen(external), external);
	socket_write_string(client, buffer);
}

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

info_t * info_t_new (void)
{
    info_t * info = malloc (sizeof(info_t));
    info->student = "Nastya Shapovalova";
    info->group = "KP-51";
    info->variant = 15;
    return info;
}

void info_t_free (info_t * info)
{
    free (info);
}

void server_info (socket_t * socket)
{
	char buffer[1024];
	info_t * info = info_t_new ();
	const char * Info = info_toJSON(info);
	puts (Info);
	info_t_free (info);
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


//==================================datbase==============
/*
void server_database(socket_t * client)
{
    const char * dbFile = "data.db";
    musician_t musicianList[50];
    db_t * db = db_new(dbFile);
    sqlite3_stmt * stmt = NULL;
    int count  = db_countMusicians(db);
    for (int i = 0; i < count; i++)
    {
        _fillMusician(stmt, &musicianList[count]);
    }
    musician_printList(musicianList, count);
    db_free(db);
}*/

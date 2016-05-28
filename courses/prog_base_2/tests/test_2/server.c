#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "server.h"
#include "http.h"
#include "info.h"
#include "socket.h"
#include "list.h"
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480 // How much is printed out to the screen


 SOCKET sockett_new(void)
 {
     SOCKET recvSocket  = socket(AF_INET , SOCK_STREAM,  IPPROTO_TCP);
     if( recvSocket == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    printf("Socket created.\n");
    return recvSocket;
}

void con_to_serv (SOCKET recvSocket, SOCKADDR_IN recvSockAddr)
{
 if(connect(recvSocket,(SOCKADDR*)&recvSockAddr,sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        printf("ERROR: socket could not connect\r\n");
        closesocket(recvSocket);
        WSACleanup();
    }
}

void send_request1(SOCKET recvSocket, const char * host_name)
{
    char request[200];
    sprintf(request, "GET /test/var/15?format=json HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);  // add Host header with host_name value
    send(recvSocket, request, strlen(request), 0);
}

void rec_answer (SOCKET recvSocket, char * buffer)
{
    int numrcv = recv(recvSocket, buffer, MAXBUFLEN, NO_FLAGS_SET);
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



SOCKADDR_IN get_Addr(char * ip)
{
    SOCKADDR_IN recvSockAddr;
    memset(&recvSockAddr, 0, sizeof(recvSockAddr));
    recvSockAddr.sin_port=htons(PORT); // specify the port portion of the address
    recvSockAddr.sin_family=AF_INET; // specify the address family as Internet
    recvSockAddr.sin_addr.s_addr= inet_addr(ip); // specify ip address
    return recvSockAddr;
}

int get_data ()
{
    WSADATA Data;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;
    int status;
    struct hostent * remoteHost;
    char * ip;
    const char * host_name = "pb-homework.appspot.com";
    char buffer[MAXBUFLEN];
    memset(buffer,0,MAXBUFLEN);

    // Initialize Windows Socket DLL
    printf ("Initializing Socket");
    status = WSAStartup(MAKEWORD(2, 2), &Data);
    if(status != 0)
    {
        printf("ERROR: WSAStartup unsuccessful\r\n");
        return 0;
    }
    printf ("Initialized");

	// Get IP address from host name
	remoteHost = gethostbyname(host_name);
	ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
	printf("IP address is: %s.\n", ip);
	recvSockAddr = get_Addr (ip);
    //Creating new socket
    recvSocket = sockett_new ();
    //Connecting
    con_to_serv (recvSocket, recvSockAddr);

    //Sending request 1
    send_request1(recvSocket, host_name);

    //Receiving the answer
    rec_answer (recvSocket, buffer);

    //Looking for answer
    printf ("\n The result is: %s\n", buffer);
    //Closing socket
    closesocket(recvSocket);

    WSACleanup();

    getchar();

    return 0;
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

//=====================================external===================================

void server_external(socket_t * client)
{
    int n = get_data();
    printf ("%i", n);
     /*char buffer [1024];
     const char * external = get_data ();
     sprintf(buffer,
		"HTTP/1.1 200 OK\n"
		"Content-Type: application/json\n"
		"Content-Length: %d\n"
		"Connection: keep-alive\r\n\r\n"
		"%s", strlen(external), external);
	socket_write_string(client, buffer);*/
}

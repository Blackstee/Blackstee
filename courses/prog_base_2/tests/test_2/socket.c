#include <winsock2.h>
#include "socket.h"
//#pragma comment(lib,"ws2_32.lib") //Winsock Library
//#define NO_FLAGS_SET 0
//#define PORT 80
//#define MAXBUFLEN 20480 // How much is printed out to the screen

struct socket_s {
    SOCKET winsock;
};

static socket_t *
socket_new_winsock(SOCKET winsocket) {
    socket_t * self = malloc(sizeof(struct socket_s));
    self->winsock = winsocket;
    return self;
}

socket_t *
socket_new(void) {
    SOCKET winsock = socket(AF_INET, SOCK_STREAM, 0);
    // == INVALID_SOCKET; WSAGetLastError()
    socket_t * self = socket_new_winsock(winsock);
    return self;
}

void
socket_free(socket_t * self) {
    closesocket(self->winsock);
    free(self);
}

const char *
socket_getIPAddress(socket_t * self) {
    return "(null)";  // @todo
}

int
socket_getPortNumber(socket_t * self) {
    return -1;  // @todo
}

int
socket_bind(socket_t * self, int portNumber) {
    struct sockaddr_in serveraddr = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(portNumber)
    };
    int status = bind(self->winsock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    // @todo == SOCKET_ERROR
    return status;
}

int
socket_listen(socket_t * self) {
    listen(self->winsock, 10);  // @todo param
    return 0; // @todo ?
}

socket_t *
socket_accept(socket_t * self) {
    struct sockaddr_in clientaddr;
    int size = sizeof(struct sockaddr_in);
    SOCKET winsock = accept(self->winsock, (struct sockaddr *)&clientaddr, &size);
    if (INVALID_SOCKET == winsock) {
        return NULL;
    }
    socket_t * socket = socket_new_winsock(winsock);
    return socket;
}

int
socket_connect(socket_t * self, const char * ipaddress, int portNumber) {
    struct sockaddr_in serveraddr = {
        .sin_addr.s_addr = inet_addr(ipaddress),
        .sin_family = AF_INET,
        .sin_port = htons(portNumber)
    };
    int status = connect(self->winsock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    // @todo if < 0
    return status;
}

int
socket_read(socket_t * self, char * recvBuff, int recvBuffSize) {
    int recvSize = recv(self->winsock, recvBuff, recvBuffSize, 0);
    // @todo == SOCKET_ERROR
    recvBuff[recvSize] = '\0';
    return recvSize;
}

int
socket_write(socket_t * self, const char * msg, int msgSize) {
    int status = send(self->winsock, msg, msgSize, 0);
    // @todo < 0
    return status;
}

int
socket_write_string(socket_t * self, const char * msg) {
    return socket_write(self, msg, strlen(msg));
}

void
socket_close(socket_t * self) {
    closesocket(self->winsock);
}

/* STATIC */

static WSADATA wsa;

void
lib_init(void) {
    WSAStartup(MAKEWORD(2, 2), &wsa);
    // @todo check status != 0
}

void
lib_free(void) {
    WSACleanup();
}
/*
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
		return(1);
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
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480 // How much is printed out to the screen


 SOCKET socket_new(void)
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
    sprintf(request, "GET /var/4 HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);  // add Host header with host_name value
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

void send_request2(SOCKET recvSocket, const char * host_name, char * buffer)
{
    char request[200];
    char word[50];
    strcpy( word,strstr(buffer,"secret"));
    sprintf(request, "GET /var/4?%s HTTP/1.1\r\nHost:%s\r\n\r\n",word, host_name);  // add Host header with host_name value
    send(recvSocket, request, strlen(request), 0);
}

void send_request3(SOCKET recvSocket, const char* host_name, char * word){
	char request[200];
	char imp [50];
	printf("The max-length word is: %s\n", word);
	sprintf(imp, "result=%s", word);
	sprintf(request, "POST %s/var/4 HTTP/1.1\r\nContent-length: %d\r\n\r\n%s", host_name, strlen(imp), imp);
    send(recvSocket, request, strlen(request), 0);
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


char * Max_word(char mes [100]){
   char * message = strstr (mes,"\r\n\r\n");
    int i;
    char max_word [300];
    max_word [0] = 0;
    char *wordd = &max_word;
    char word [300];
    word [0] = 0;
    char *one_w = &word;
    int j = 0;
    for (i = 0; i < strlen (message); i++)
        {
            if (!isspace(message[i]))
            {
                one_w[j] = message[i];
                j++;
                one_w [j] = '\0';
            } else {
                if (strlen(one_w) >= strlen (wordd))
                   {
                       wordd [0] = '\0';
                       strcat (wordd, one_w);
                   }
                    one_w [0] = '\0';
                    j = 0;
            }
        }
        wordd[strlen(wordd)] = '\0';
    return wordd;
}


int main(int argc , char *argv[])
{
    WSADATA Data;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;
    int status;
    int numrcv = 0;
    struct hostent * remoteHost;
    char * ip;
    char string [100];
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
    recvSocket = socket_new ();

    //Connecting
    con_to_serv (recvSocket, recvSockAddr);

    //Sending request 1
    send_request1(recvSocket, host_name);

    //Receiving the answer
    rec_answer (recvSocket, buffer);

    //Sending request 2
    send_request2(recvSocket,host_name, buffer);

    //Receiving the answer
    rec_answer (recvSocket, buffer);
    //Function
    strcpy(string, Max_word (buffer));

    //Sending request 3
    send_request3(recvSocket,host_name, string);

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

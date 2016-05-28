#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "http.h"
//#include "musicians.h"
#include "socket.h"
//=====================Homepage=============
void server_homepage(socket_t * client);

//=====================Info=================
void server_info (socket_t * client);

//=====================not found============
void server_notFound(socket_t * client);

#endif // SERVER_H_INCLUDED

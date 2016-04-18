#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "http.h"
#include "musicians.h"
#include "socket.h"

musician_t musicians_arr[];

error_t * error_t_new (void);
void error_t_free (error_t * err);
void error_t_add_err (error_t * err, int status1, char * error1);

void server_sendJson(socket_t * socket, error_t * err);

int get_size_mus_arr(void);
void server_homepage(socket_t * client);
void server_allMusicians(socket_t * client, http_request_t * req);
void server_musicianById(socket_t * client, http_request_t * req, const char * pathBuf);
void server_notFound(socket_t * client);


#endif // SERVER_H_INCLUDED

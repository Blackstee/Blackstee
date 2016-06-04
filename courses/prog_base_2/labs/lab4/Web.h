#ifndef WEB_H_INCLUDED
#define WEB_H_INCLUDED

#include "http.h"
#include "Resource.h"
#include "socket.h"

//==================for json errors===========
error_t * error_t_new (void);
void error_t_free (error_t * err);
void error_t_add_err (error_t * err, int status1, char * error1);
void server_sendJson(socket_t * socket, error_t * err);

//===================homepages==============
void server_html_homepage(socket_t * client);
void server_json_homepage(socket_t * client);


//===================all musicians===========
void server_html_allMusicians(socket_t * client, http_request_t * req, mus_arr_t * self);
void server_json_allMusicians(socket_t * client, http_request_t * req, mus_arr_t * self);


//===================musician by id==========
void server_html_musicianById(socket_t * client, http_request_t * req, const char * pathBuf, mus_arr_t * self);
void server_json_musicianById(socket_t * client, http_request_t * req, const char * pathBuf, mus_arr_t * self);

//==================new musician==============
void server_html_new_musician (mus_arr_t * mus_arr, socket_t * client);

//====================not found==============
void server_notFound(socket_t * client);
void server_html_error (socket_t * client, char * line);


#endif // WEB_H_INCLUDED

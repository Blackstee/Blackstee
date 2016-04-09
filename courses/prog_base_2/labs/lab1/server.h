#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

typedef enum server_status
{
    SERVER_OK,
    NO_SENDER,
    NO_RECIPIENT,
    WRONG_INPUT_ID,
    NO_CLIENT,
    NO_MESSAGE
} server_status;

typedef struct server_s server_t;

server_t * server_new (int id);

void server_t_free (server_t * serv);

int server_t_get_count_of_clients (server_t * serv);
int server_t_get_status (server_t * serv);
int server_t_get_name (server_t * serv);


#endif // SERVER_H_INCLUDED

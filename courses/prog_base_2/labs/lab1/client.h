#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

typedef enum client_status
{
        CLIENT_OK,
        EMPTY_SERVER,
        UNORIGIN_NAME,
        WRONG_NAME,
        FULL_SERVER,
        ERROR,
        SENDER_OK,
        RECIPIENT_OK

}client_status;

typedef struct client_s client_t;

client_t * client_new (server_t * serv, int id);

void client_t_free (server_t * serv, client_t * cl);

int client_t_check_id (server_t * serv, int id);
void client_t_send_mes (server_t * serv, client_t * sender, client_t * recipient, char message [50]);
void client_t_print_mes (server_t * serv, client_t * cl);
int client_t_check_serv (server_t * serv, client_t * cl);
int client_t_get_name (server_t * serv, client_t * client);
int client_t_get_name_of_serv (server_t * serv, client_t * client);
int client_t_get_count_mes (server_t * serv, client_t * client);
int client_t_get_status (server_t * serv, client_t * client);


#endif // CLIENT_H_INCLUDED

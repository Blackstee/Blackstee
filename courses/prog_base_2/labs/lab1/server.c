#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "server.h"

#define COUNT_MES 50
#define MAX_CLIENTS 20
#define MAX_MESSAGES 20

struct client_s
{
    int name_of_client;
    char messages [1000];
    char ** Mess;
    int count_mess;
    int name_of_server;
    client_status * status;
};

struct server_s
 {
     int name;
     int count_clients;
     server_status * status;
     client_t * clients [MAX_CLIENTS];
 };

 server_t * server_new (int id)
 {
     server_t * serv = malloc (sizeof ( struct server_s));
     if (id > 0 && id < 1000000)
     serv->status = CLIENT_OK;
     else serv->status = WRONG_INPUT_ID;
     serv->name = id;
     serv->count_clients = 0;
     return serv;
 }

 void server_t_free (server_t * serv)
 {
     free (serv->status);
     free (serv->clients);
     free (serv);
 }

 client_t * client_new (server_t * serv, int id_client)
 {
     client_t * cl = malloc (sizeof (struct client_s));
     if (serv != NULL && client_t_check_id (serv, id_client) == 1 && (serv->count_clients + 1) < MAX_CLIENTS)
        {
        cl->Mess = malloc(120*100*sizeof(char));
        strcpy(cl->Mess,"\0");
        cl->status = CLIENT_OK;
        cl->name_of_client = id_client;
        cl->count_mess = 0;
        cl->name_of_server = serv->name;
        serv->clients[serv->count_clients] = client_t_get_name(serv, cl);
        serv->count_clients++;
        }
        else if (serv == NULL) cl->status = EMPTY_SERVER;
        else if (client_t_check_id (serv, id_client) == 0) cl->status = UNORIGIN_NAME;
        else if (client_t_check_id (serv, id_client) == 2) cl->status = WRONG_NAME;
        else if ((serv->count_clients + 1) > MAX_CLIENTS) cl->status = FULL_SERVER;
        else cl->status = ERROR;
        return cl;
 }

 void client_t_free (server_t * serv, client_t * cl)
 {
     if (cl == NULL)
     serv->status = NO_CLIENT;
     serv->count_clients--;
     free(cl->Mess);
     free (cl->status);
     free (cl);
 }

 int client_t_check_id (server_t * serv, int id)
 {
     int i;
     if (id < 0 || id > 10000000)
        return 2;
     for (i = 0; i < serv->count_clients + 1; i++)
         if (id == serv->clients[i])
            return 0;
      return 1;
 }

 int server_t_get_count_of_clients (server_t * serv)
 {
     return serv->count_clients;
 }

 int server_t_get_status (server_t * serv)
 {
     return serv->status;
 }

 int server_t_get_name (server_t * serv)
 {
     return serv->name;
 }

 void client_t_send_mes (server_t * serv, client_t * sender, client_t * recipient, char message [50])
 {
     int id = client_t_get_name(serv, sender);
     if (message == NULL || strlen(message)>100)
        serv->status = NO_MESSAGE;
     else
     if ( client_t_check_serv (serv, sender)== 0 || sender == NULL)
        serv->status = NO_SENDER;
     else
     if ( client_t_check_serv (serv, recipient)== 0 || recipient == NULL)
        serv->status = NO_RECIPIENT;
        else
        {
            serv->status  = SERVER_OK;
            sender->status = SENDER_OK;
            recipient->status = RECIPIENT_OK;
            strcpy (recipient->Mess[recipient->count_mess], message);
            recipient->count_mess++;
           // sender->name_of_client = id;
        }
 }

 void client_t_print_mes (server_t * serv, client_t * cl)
 {
     int i;
    printf ("The messages to client with name %d:\n", client_t_get_name(serv, cl));
     for (i = 0; i < cl->count_mess; i++)
             puts (cl->Mess[i]);
     if (serv != NULL && cl != NULL && client_t_check_serv (serv, cl) == 1)
     cl->status = CLIENT_OK;
     else cl->status = ERROR;
 }

int client_t_check_serv (server_t * serv, client_t * cl)
{
    int i;
    int id = client_t_get_name(serv, cl);
    for (i = 0; i < serv->count_clients + 1; i++)
         if (id == serv->clients[i])
            return 1;
    return 0;
}

int client_t_get_name (server_t * serv, client_t * client)
{
    return client->name_of_client;
}

int client_t_get_name_of_serv (server_t * serv, client_t * client)
{
    return client->name_of_server;
}

int client_t_get_count_mes (server_t * serv, client_t * client)
{
    return client->count_mess;
}

int client_t_get_status (server_t * serv, client_t * client)
{
    return client->status;
}

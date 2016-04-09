#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>

#include "server.h"
#include "client.h"


// unit-test functions

//right input
static void new_value_status (void **state)
{
    server_t *serv1  = server_new (23456);
    assert_int_equal(server_t_get_status(serv1), 0);
    server_t_free (serv1);
}
//wrong input
static void new_oneServer_status (void **state)
{
    server_t * serv1 = server_new (-4567);
    assert_int_equal(server_t_get_status(serv1), 3);
    server_t_free (serv1);
}
//checking number of clients - Empty
static void new_value_zeroCount(void **state)
{
    server_t * serv1 = server_new(567432);
    assert_int_equal(server_t_get_count_of_clients(serv1), 0);
    server_t_free(serv1);
}
//checking number of clients  - One Client
static void add_oneClient_countOne(void **state)
{
    server_t * serv1 = server_new(567432);
    client_t * cl1 = client_new(serv1, 867);
    assert_int_equal(server_t_get_count_of_clients(serv1), 1);
    client_t_free(serv1, cl1);
    server_t_free(serv1);
}
//checking number of clients  - Two Clients
static void add_twoClients_countTwo(void **state)
{
    server_t * serv1 = server_new(567432);
    client_t * cl1 = client_new(serv1, 867);
    client_t * cl2 = client_new(serv1, 886);
    assert_int_equal(server_t_get_count_of_clients(serv1), 1);
    client_t_free(serv1, cl1);
    client_t_free(serv1, cl2);
    server_t_free(serv1);
}
//checking number of clients  - Two Clients - free One Client = One Client
static void free_twoClients_countOne (void ** state)
{
    server_t * serv1 = server_new(567432);
    client_t * cl1 = client_new(serv1, 867);
    client_t * cl2 = client_new(serv1, 868);
    client_t_free(serv1, cl1);
    assert_int_equal(server_t_get_count_of_clients(serv1), 1);
    client_t_free(serv1, cl2);
    server_t_free(serv1);
}
//checking the name of server
static void name_oneServer_id (void **state)
{
    server_t * serv1 = server_new (4567);
    assert_int_equal(server_t_get_name(serv1), 4567);
    server_t_free(serv1);
}
//checking the name of client
static void name_oneClient_id (void **state)
{
    server_t * serv1 = server_new (66786);
    client_t * cl1 = client_new (serv1, 111);
    assert_int_equal (client_t_get_name(serv1, cl1), 111);
    client_t_free(serv1, cl1);
    server_t_free(serv1);
}
//wrong input (name of client)
static void name_oneClient_error (void **state)
{
    server_t * serv1 = server_new (66786);
    client_t * cl1 = client_new (serv1, -111);
    assert_int_equal (client_t_get_status(serv1, cl1), 3);
    client_t_free(serv1, cl1);
    server_t_free(serv1);
}
//unoriginal name (the same name of client)
static void name_twoClients_statussameid (void **state)
{
    server_t * serv1 = server_new (66786);
    client_t * cl1 = client_new (serv1, 232);
    client_t * cl2 = client_new (serv1, 232);
    assert_int_equal (client_t_get_status(serv1, cl2), 2);
    client_t_free(serv1, cl1);
    client_t_free(serv1, cl2);
    server_t_free(serv1);
}
//sending message (check status)
static void sendmess_twoClientsandMessage_statusserver (void **state)
{
    server_t * serv1 = server_new(567432);
    client_t * cl1 = client_new(serv1, 867);
    client_t * cl2 = client_new(serv1, 886);
    client_t_send_mes(serv1, cl1, cl2, "Hello");
    assert_int_equal(server_t_get_status(serv1), 0);
    client_t_free(serv1, cl1);
    client_t_free(serv1, cl2);
    server_t_free(serv1);
}
//sending message (wrong sender)
static void sendmess_wrongSenderRecipientandMessage_status (void **state)
{
    server_t * serv1 = server_new(567432);
    client_t * cl1 = client_new(serv1, 867);
    client_t * cl2 = client_new(serv1, 886);
    server_t * serv2 = server_new (8765);
    client_t * cl3 = client_new (serv2, 458);
    client_t_send_mes(serv1, cl3, cl2, "Hello");
    assert_int_equal(server_t_get_status(serv1), 1);
    client_t_free(serv1, cl1);
    client_t_free(serv1, cl2);
    server_t_free(serv1);
}
//sending message (wrong recipient)
static void sendmess_wrongRecipientSenderandMessage_status (void **state)
{
    server_t * serv1 = server_new(567432);
    client_t * cl1 = client_new(serv1, 867);
    client_t * cl2 = client_new(serv1, 886);
    server_t * serv2 = server_new (8765);
    client_t * cl3 = client_new (serv2, 458);
    client_t_send_mes(serv1, cl1, cl3, "Hello");
    assert_int_equal(server_t_get_status(serv1), 2);
    client_t_free(serv1, cl1);
    client_t_free(serv1, cl2);
    server_t_free(serv1);
}
//sending message (wrong message)
static void sendmess_wrongMessageTwoClients_status (void **state)
{
    server_t * serv1 = server_new(567432);
    client_t * cl1 = client_new(serv1, 867);
    client_t * cl2 = client_new(serv1, 886);
    client_t_send_mes(serv1, cl1, cl2, NULL);
    assert_int_equal(server_t_get_status(serv1), 5);
    client_t_free(serv1, cl1);
    client_t_free(serv1, cl2);
    server_t_free(serv1);
}
//sending message (status)
static void sendmess_TwoClients_statusclient (void ** state)
{
    server_t * serv1 = server_new(567432);
    client_t * cl1 = client_new(serv1, 867);
    client_t * cl2 = client_new(serv1, 886);
    client_t_send_mes(serv1, cl1, cl2, "HELLO!");
    assert_int_equal(client_t_get_status(serv1, cl1), 0);
    client_t_free(serv1, cl1);
    client_t_free(serv1, cl2);
    server_t_free(serv1);
}
//printing messages (status)
static void printmess_oneClient_status (void ** state)
{
    server_t * serv1 = server_new(567432);
    client_t * cl1 = client_new(serv1, 867);
    client_t * cl2 = client_new(serv1, 886);
    client_t_send_mes(serv1, cl1, cl2, "HELLO!");
    client_t_print_mes (serv1, cl2);
    assert_int_equal(client_t_get_status(serv1, cl2), 0);
    client_t_free(serv1, cl1);
    client_t_free(serv1, cl2);
    server_t_free(serv1);
}
int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_value_status),
        cmocka_unit_test(new_value_zeroCount),
        cmocka_unit_test(add_oneClient_countOne),
        cmocka_unit_test(add_twoClients_countTwo),
        cmocka_unit_test(free_twoClients_countOne),
        cmocka_unit_test(name_oneServer_id),
        cmocka_unit_test(new_oneServer_status),
        cmocka_unit_test(name_oneClient_id),
        cmocka_unit_test(name_oneClient_error),
        cmocka_unit_test(name_twoClients_statussameid),
        cmocka_unit_test(sendmess_twoClientsandMessage_statusserver),
        cmocka_unit_test(sendmess_wrongSenderRecipientandMessage_status),
        cmocka_unit_test(sendmess_wrongRecipientSenderandMessage_status),
        cmocka_unit_test(sendmess_wrongMessageTwoClients_status),
        cmocka_unit_test(sendmess_TwoClients_statusclient),
        cmocka_unit_test(printmess_oneClient_status),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

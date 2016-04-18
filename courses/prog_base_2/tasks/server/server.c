#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "server.h"
#include "http.h"
#include "musicians.h"
#include "socket.h"

musician_t musicians_arr[] = {
	{
		.id = 0,
		.name = "Viktor",
		.surname = "Coj",
		.birthdate = "1962-06-21",
		.year = 1990,
		.rating = 4.95,
		.band.style = "rock",
		.band.role = "singer",
	},
	{
		.id = 1,
		.name = "Freddie",
		.surname = "Mercury",
		.birthdate = "1946-09-05",
		.year = 1991,
		.rating = 4.9,
		.band.style = "rock",
		.band.role = "singer",
	},
	{
		.id = 2,
		.name = "Michael",
		.surname = "Jackson",
		.birthdate = "1958-08-29",
		.year = 2009,
		.rating = 4.8,
		.band.style = "pop",
		.band.role = "singer",
	}
};

error_t * error_t_new (void)
{
    error_t * err = malloc (sizeof(struct error_s));
    err->status = "Ok";
    err->error = "No Error";
    return err;
}

void error_t_free (error_t * err)
{
    free (err);
}

void error_t_add_err (error_t * err, int status1, char * error1)
{
    err->status = status1;
    err->error = error1;
    return err;
}
int get_size_mus_arr(void)
{
	return sizeof(musicians_arr) / sizeof(musicians_arr[0]);
}

void server_sendJson(socket_t * socket, error_t * err){
	char buffer[1024];

	char * Error = error_toJSON(&err);
	sprintf(buffer,
		"HTTP/1.1 200 OK\n"
		"Content-Type: application/json\n"
		"Content-Length: %d\n"
		"Connection: keep-alive\r\n\r\n"
		"%s", strlen(Error), Error);
	socket_write_string(socket, buffer);
}

void server_homepage(socket_t * client)
{
    char homeBuf[10240];
    const char * htmlText =
        "<head>"
            "<title>Musician's server</title></head>"
        "<body>"
            "<h1>Hello! It's a homepage</h1>"
            "<div><a href='/musicians'>All musicians</a></div>"
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

void server_allMusicians(socket_t * client, http_request_t * req)
{
    char strbuf[10240];

    if (strcmp(req->method, "GET") == 0)
    {
        char * allMusiciansJson = musician_listToJSON(musicians_arr, (sizeof(musicians_arr) / sizeof(musicians_arr[0])));

        sprintf(strbuf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %zu\n"
            "Connection: keep-alive\n"
            "\n%s", strlen(allMusiciansJson), allMusiciansJson);
        free(allMusiciansJson);
    } else
    {
        char * error = "Error!";
		sprintf(strbuf,
			"HTTP/1.1 404 ERROR \n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"\n%s", strlen(error), error);
    }
    socket_write_string(client, strbuf);
    socket_close(client);
}

void server_musicianById(socket_t * client, http_request_t * req, const char * pathBuf)
{
    const char * pattern = "/musicians/";
    char * c = NULL;
    const char * Text = " \0";
    char strbuf[10240];
    error_t * err = error_t_new ();
    int count = get_size_mus_arr ();
    long musIndex = strtol(pathBuf + strlen(pattern), &c, 10);
    if (musIndex < 0 || musIndex >= count) {
        error_t_add_err(err, NULL, "Wrong Index of musician");
        server_sendJson(client, &err);
        return;
    }
    if (strcmp (req->method, "GET") == 0)
    {
        const char * musJson = musician_toJSON(&musicians_arr[musIndex]);
        sprintf(strbuf,
        "HTTP/1.1 200 OK\n"
        "Content-Type: application/json\n"
        "Content-Length: %zu\n"
        "Connection: keep-alive\n"
        "\n%s", strlen(musJson), musJson);
        free(musJson);
    }
    else
        if (strcmp (req->method, "POST") == 0)
    {
        musicians_arr[musIndex] = musician_empty();
        musicians_arr[musIndex].id = musIndex;
        const char * str = http_request_getArg(req, "name");
        if (strlen(str) > 0 && strlen (str) < 20)
        {
            musicians_arr[musIndex].name = str;
            str = http_request_getArg(req, "surname");
            if (strlen(str) > 0 && strlen (str) < 20)
             {
                musicians_arr[musIndex].surname = str;
                str = http_request_getArg (req, "birthdate");
                if (strlen(str) > 0)
                {
                    if (atoi(str) > 1800 && atoi(str) < 2000)
                    {
                        char text [10] = " ";
                        strcpy(text, str);
                        char * string = strtok(text, "-");
                        string  = strtok(NULL, "-");
                        if (atoi(string) > 0 && atoi (string) < 32)
                        {
                           string = strtok (NULL, "-");
                           if (atoi(string) > 0 && atoi (string) < 13)
                              {
                                  musicians_arr [musIndex].birthdate = http_request_getArg(req, "birthdate");
                                  str = http_request_getArg(req, "year");
                                  if (strlen(str) > 0 && atoi(str) > 1850 && atoi (str) < 2016)
                                   {
                                       musicians_arr[musIndex].year = atoi(str);
                                       str = http_request_getArg (req, "rating");
                                       if (strlen(str) > 0 && atof (str) >= 0.0 && atof (str) <= 5.0)
                                       {
                                          musicians_arr[musIndex].rating = atof (str);
                                          str = http_request_getArg(req, "style");
                                          if (strlen(str) > 0 && strlen (str) < 20)
                                          {
                                              musicians_arr[musIndex].band.style = str;
                                              str = http_request_getArg(req, "role");
                                              if (strlen(str) > 0 && strlen (str) < 20)
                                            {
                                                   musicians_arr[musIndex].band.role = str;
                                                   Text = musician_toJSON(&musicians_arr);
                                                   printf("New musician:\n%s\n", Text);
                                                   sprintf(strbuf,
                                                   "HTTP/1.1 200 OK\n"
                                                   "Content-Type: application/json\n"
                                                   "Content-Length: %zu\n"
                                                   "Connection: keep-alive\n"
                                                   "\n%s", strlen(Text), Text);
                                                   free(Text);
                                            } else
                                            {
                                                error_t_add_err(err, NULL, "Wrong role");
                                                server_sendJson(client, &err);
                                            }
                                          } else
                                            {
                                                error_t_add_err(err, NULL, "Wrong style");
                                                server_sendJson(client, &err);
                                            }
                                       } else
                                        {
                                                error_t_add_err(err, NULL, "Wrong rating");
                                                server_sendJson(client, &err);
                                        }
                                   } else
                                       {
                                                error_t_add_err(err, NULL, "Wrong year of death");
                                                server_sendJson(client, &err);
                                       }
                              } else
                               {
                                                error_t_add_err(err, NULL, "Wrong month of birthdate");
                                                server_sendJson(client, &err);
                                }
                         } else
                         {
                                                error_t_add_err(err, NULL, "Wrong day of birthdate");
                                                server_sendJson(client, &err);
                         }
                    } else
                    {
                                                error_t_add_err(err, NULL, "Wrong year of birthdate");
                                                server_sendJson(client, &err);
                    }
                 } else
                 {
                                                error_t_add_err(err, NULL, "Wrong birthdate ");
                                                server_sendJson(client, &err);
                  }
              } else
                 {
                                                error_t_add_err(err, NULL, "Wrong surname");
                                                server_sendJson(client, &err);
                 }
            } else
            {
                                                error_t_add_err(err, NULL, "Wrong name");
                                                server_sendJson(client, &err);
            }
    } else
     {
        if (strcmp(req->method, "DELETE") == 0)
            {
                 musicians_arr[musIndex] = musician_empty();
		         musicians_arr[musIndex].id = musIndex;
		         if (musicians_arr[musIndex].year == 0)
		         error_t_add_err(err, NULL, "Deleted successfully, no errors");
		         else error_t_add_err (err, NULL, "Deleted unsuccessfully, Error");
                 server_sendJson(client, &err);
        	}
        	else
            {
                error_t_add_err(err, NULL, "Wrong method");
                server_sendJson(client, &err);
            }
    }
    socket_write_string(client, strbuf);
    socket_close(client);
}

void server_notFound(socket_t * client) {
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

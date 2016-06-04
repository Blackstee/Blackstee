#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Web.h"
#include "http.h"
#include "Resource.h"
#include "socket.h"

//=========================ERRORS FOR JSON===================================
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

//=======================================HOMEPAGES====================================

void server_json_homepage(socket_t * client)
{
    char homeBuf[10240];
    const char * htmlText =
        "<head>"
            "<title>Musician's server</title></head>"
        "<body>"
            "<h1>Hello! It's a homepage</h1>"
            "<div><a href='/api/musicians'>All musicians</a></div>"
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

void server_html_homepage(socket_t * client)
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

//======================================ALL MUSICIANS=====================================
void server_json_allMusicians(socket_t * client, http_request_t * req, mus_arr_t * self)
{
    char strbuf[10240];
    const char * Text = " \0";
    error_t * err = error_t_new ();
    if (strcmp(req->method, "GET") == 0)
    {
        char * allMusiciansJson = musician_listToJSON(self, mus_arr_t_get_size(self));
        sprintf(strbuf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %zu\n"
            "Connection: keep-alive\n"
            "\n%s", strlen(allMusiciansJson), allMusiciansJson);
        free(allMusiciansJson);
    } else
    if (strcmp (req->method, "POST") == 0)
    {
        musician_t * newmus = musician_t_new();
        const char * str = http_request_getArg(req, "name");
        if (strlen(str) > 0 && strlen (str) < 20)
        {
            newmus->name = str;
            str = http_request_getArg(req, "surname");
            if (strlen(str) > 0 && strlen (str) < 20)
             {
                newmus->surname = str;
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
                                  newmus->birthdate = http_request_getArg(req, "birthdate");
                                  str = http_request_getArg(req, "year");
                                  if (strlen(str) > 0 && atoi(str) > 1850 && atoi (str) < 2016)
                                   {
                                       newmus->year = atoi(str);
                                       str = http_request_getArg (req, "rating");
                                       if (strlen(str) > 0 && atof (str) >= 0.0 && atof (str) <= 5.0)
                                       {
                                          newmus->rating = atof (str);
                                          str = http_request_getArg(req, "style");
                                          if (strlen(str) > 0 && strlen (str) < 20)
                                          {
                                              newmus->band.style = str;
                                              str = http_request_getArg(req, "role");
                                              if (strlen(str) > 0 && strlen (str) < 20)
                                            {
                                                   newmus->band.role = str;
                                                   newmus->id = mus_arr_t_get_free_id(self);
                                                   mus_arr_t_add_by_index(self, newmus, newmus->id);
                                                   Text = musician_toJSON(newmus);
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
    }
    else
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

void server_html_allMusicians(socket_t * client, http_request_t * req, mus_arr_t * self)
{
    char strbuf[10240];
    const char * Text = " \0";
    if (strcmp(req->method, "GET") == 0)
    {
        char * allMusiciansJson = musician_listToHTML(self);
        puts (allMusiciansJson);
        char link [100];
        strcpy(link, "<h2 align = \"center\"><a href=\"/new_musician\" ><i>New musician</i></a></h2>");
        sprintf(strbuf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %zu\n"
            "Connection: keep-alive\n"
            "\n%s%s", (strlen(allMusiciansJson) + strlen (link)), allMusiciansJson, link);
        free(allMusiciansJson);
    } else
    if (strcmp (req->method, "POST") == 0)
    {
        musician_t * newmus = musician_t_new();
        const char * str = http_request_getArg(req, "name");
        if (strlen(str) > 0 && strlen (str) < 20)
        {
            newmus->name = str;
            str = http_request_getArg(req, "surname");
            if (strlen(str) > 0 && strlen (str) < 20)
             {
                newmus->surname = str;
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
                                  newmus->birthdate = http_request_getArg(req, "birthdate");
                                  str = http_request_getArg(req, "year");
                                  if (strlen(str) > 0 && atoi(str) > 1850 && atoi (str) < 2016)
                                   {
                                       newmus->year = atoi(str);
                                       str = http_request_getArg (req, "rating");
                                       if (strlen(str) > 0 && atof (str) >= 0.0 && atof (str) <= 5.0)
                                       {
                                          newmus->rating = atof (str);
                                          str = http_request_getArg(req, "style");
                                          if (strlen(str) > 0 && strlen (str) < 20)
                                          {
                                              newmus->band.style = str;
                                              str = http_request_getArg(req, "role");
                                              if (strlen(str) > 0 && strlen (str) < 20)
                                            {
                                                   newmus->band.role = str;
                                                   newmus->id = mus_arr_t_get_free_id(self);
                                                   mus_arr_t_add_by_index(self, newmus, newmus->id);
                                                   Text = musician_toHTML(newmus);
                                                   printf("New musician:\n%s\n", Text);
                                                   sprintf(strbuf,
                                                   "HTTP/1.1 200 OK\n"
                                                   "Content-Type: text/html\n"
                                                   "Content-Length: %zu\n"
                                                   "Connection: keep-alive\n"
                                                   "\n%s", strlen(Text), Text);
                                                   free(Text);
                                            } else
                                            {
                                                server_html_error(client, "Wrong role");
                                            }
                                          } else
                                            {
                                                server_html_error(client, "Wrong style");
                                            }
                                       } else
                                        {
                                               server_html_error(client, "Wrong rating");
                                        }
                                   } else
                                       {
                                               server_html_error(client, "Wrong year");
                                       }
                              } else
                               {
                                      server_html_error(client, "Wrong month of birthdate");
                                }
                         } else
                         {
                             server_html_error(client, "Wrong day of birthdate");
                         }
                    } else
                    {
                          server_html_error(client, "Wrong year of birthdate");
                    }
                 } else
                 {
                        server_html_error(client, "Wrong birthdate");
                  }
              } else
                 {
                        server_html_error(client, "Wrong surname");
                 }
            } else
            {
                 server_html_error(client, "Wrong name");
            }
    }
    else
    {
        server_html_error(client, "Wrong musician");
    }
    socket_write_string(client, strbuf);
    socket_close(client);
}

//===================================MUSICIAN BY ID=========================================

void server_json_musicianById(socket_t * client, http_request_t * req, const char * pathBuf, mus_arr_t * self)
{
    char buffer [1024];
    char file_name [20];
    strcpy (file_name, &pathBuf[15]);
    puts (file_name);
    int musIndex = atoi (file_name);
    const char * Text = " \0";
    char strbuf[10240];
    error_t * err = error_t_new ();
    int count = mus_arr_t_get_size(self);
    if (musIndex < 0 || musIndex >= count)
        {
        error_t_add_err(err, NULL, "Wrong Index of musician");
        server_sendJson(client, &err);
        return;
    }
    if (strcmp (req->method, "GET") == 0)
    {
        musician_t * cur = mus_get (self, musIndex);
        char * musJson = musician_toJSON(cur);
        sprintf(strbuf,
        "HTTP/1.1 200 OK\n"
        "Content-Type: application/json\n"
        "Content-Length: %zu\n"
        "Connection: keep-alive\n"
        "\n%s", strlen(musJson), musJson);
        free(musJson);
    }
    else
     {
        if (strcmp(req->method, "DELETE") == 0)
            {
                 musician_t * deleted = mus_delete (self, musIndex);
		         if (deleted == NULL)
		         error_t_add_err(err, NULL, "Deleted unsuccessfully, error");
		         else error_t_add_err (err, NULL, "Deleted successfully, no errors");
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


void server_html_musicianById(socket_t * client, http_request_t * req, const char * pathBuf, mus_arr_t * self)
{
    char buffer [1024];
    char file_name [20];
    strcpy (file_name, &pathBuf[11]);
    puts (file_name);
    int musIndex = atoi (file_name);
    printf ("INDEEEX: %i", musIndex);
    const char * Text = " \0";
    char strbuf[10240];
    error_t * err = error_t_new ();
    int count = mus_arr_t_get_size(self);
    if (musIndex < 0 || musIndex >= count)
        {
        error_t_add_err(err, NULL, "Wrong Index of musician");
        server_sendJson(client, &err);
        return;
    }
    if (strcmp (req->method, "GET") == 0)
    {
        musician_t * cur = mus_get (self, musIndex);
        char * musJson = musician_toHTML(cur);
        char link[1024];
		char linkURL[100];
		sprintf(linkURL,"\"http://127.0.0.1:5000/musicians/%d\"",musIndex);
		sprintf(link,
			"<br/><a href=\"#\" onclick=\"doDelete()\"><h2 align = \"center\"><i>Delete</i></h2></a>"
			"<body><script>"
			"function doDelete() {"
			"var xhttp = new XMLHttpRequest();"
			"xhttp.open(\"DELETE\", %s, true);"
			"xhttp.send();}"
			"</script></body>",
			linkURL);
        sprintf(strbuf,
        "HTTP/1.1 200 OK\n"
        "Content-Type:text/html\n"
        "Content-Length: %zu\n"
        "Connection: keep-alive\n"
        "\n%s%s", (strlen(musJson) + strlen(link)), musJson, link);
        free(musJson);
    }
    else
     {
        if (strcmp(req->method, "DELETE") == 0)
            {
                 musician_t * deleted = mus_delete (self, musIndex);
		         if (deleted == NULL)
		         error_t_add_err(err, NULL, "Deleted unsuccessfully, error");
		         else error_t_add_err (err, NULL, "Deleted successfully, no errors");
                 server_sendJson(client, &err);
                 char * del = musician_toHTML(deleted);
		         char * delText = "Investor deleted successfully!";
		         sprintf(strbuf,
			   "HTTP/1.1 200 OK\n"
			   "Content-Type: text/html\n"
			   "Content-Length: %zu\n"
			   "Connection: keep-alive\n"
			   "\n%s", strlen(delText), delText);
		      free(delText);
		     free(del);
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

//================================ NOT FOUND ======================================
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

//=================================ERRORS==========================================
void server_html_error (socket_t * client, char * line)
{
    char replyBuf [1024];
    sprintf(replyBuf,
        "HTTP/1.1 ERROR \n"
        "Content-Type: text/html\n"
        "Content-Length: %zu\n"
        "\n%s", strlen(line), line);
    socket_write_string(client, replyBuf);
    socket_close(client);
}
//==================================NEW MUSICIAN====================================
void server_html_new_musician (mus_arr_t * mus_arr, socket_t * client)
{
    char strbuf[10240];
	char line[1000];
    strcpy (line, "<html><head><title>New musician</title><h2 align  = \"center\"><strong>New musician</strong></h2></head><body><form action=\"http://127.0.0.1:5000/musicians\" method=\"POST\" align = \"center\">"
	"First name:<br><input type=\"text\" name=\"name\" value='John'><br>"
	"Last name:<br><input type=\"text\" name=\"surname\" value='Lennon'><br>"
	"Birthdate:<br><input type=\"text\" name=\"birthdate\" value=\"1940-10-09\"><br>"
	"Year of death:<br><input type=\"text\" name=\"year\" value=\"1980\"><br>"
    "Rating:<br><input type=\"text\" name=\"rating\" value=\"5.0\"><br>"
    "Band:<br><input type=\"text\" name=\"style\" value=\"rock\"><br><br>"
    "<input type=\"text\" name=\"role\" value=\"singer\"><br><br>"
	"<input type=\"submit\" value='Send POST request' /></form></body></html>");
	sprintf(strbuf,
		"HTTP/1.1 200 OK\n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"Connection: keep-alive\n"
		"\n%s", strlen(line), line);

	socket_write_string(client, strbuf);
	socket_close(client);
}

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"
#include "routing.h"

#include "http_status.h"

void listUsers(int client_socket)
{
    char json[300];
    snprintf(json, sizeof(json),
             "{"
             "   \"index\": \"hello\""
             "}");
    if (response(client_socket, HTTP_STATUS_OK, json) < 0)
    {
        perror("something happenned...\n");
        response(client_socket, HTTP_STATUS_INTERNAL_SERVER_ERROR, NULL);
    }
}

void createUser(int client_socket)
{
    char json[300];
    snprintf(json, sizeof(json),
             "{"
             "   \"index\": \"users created\""
             "}");
    if (response(client_socket, HTTP_STATUS_OK, json) < 0)
    {
        perror("something happenned...\n");
        response(client_socket, HTTP_STATUS_INTERNAL_SERVER_ERROR, NULL);
    }
}

void handler_second(int client_socket)
{
    char json[300];
    snprintf(json, sizeof(json),
             "{"
             "   \"index\": \"hello\""
             "}");
    if (response(client_socket, HTTP_STATUS_OK, json) < 0)
    {
        perror("something happenned...\n");
        response(client_socket, HTTP_STATUS_INTERNAL_SERVER_ERROR, NULL);
    }
}

int main()
{

    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10);

    RouteNode *root = newNode("/");

    addRouteNode(root, "/users", "GET", listUsers);
    addRouteNode(root, "/users/create", "POST", createUser);
    addRouteNode(root, "/users/create/something", "POST", NULL);

    start(&server, root);
    free(root);
    return 0;
}
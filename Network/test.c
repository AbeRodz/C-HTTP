#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "Server.h"
#include "HTTP_status.h"
#include "Routing.h"

void presentation(int port)
{
    printf(YEL "_________   ______  _______________________\n" RESET);
    printf(YEL "__  ____/   ___  / / /__  __/__  __/__  __ \\\n" RESET);
    printf(YEL "_  / _________  /_/ /__  /  __  /  __  /_/ /\n" RESET);
    printf(YEL "/ /___/_____/  __  / _  /   _  /   _  ____/\n" RESET);
    printf(YEL "\\____/      /_/ /_/  /_/    /_/    /_/\n" RESET);
    printf(RED "Fast, portable and simple HTTP server!\n" RESET);
    printf("Server running on port: " GRN "%d\n" RESET, port);
}

void launch(struct Server *server, RouteConfig *config)
{
    char buffer[30000];
    char json[300];
    snprintf(json, sizeof(json),
             "{"
             "   \"received_data\": \"hello\""
             "}");
    int address_length = sizeof(server->address);
    int new_socket;
    presentation(server->port);
    while (1)
    {
        new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
        read(new_socket, buffer, 30000);
        printf("%s\n", buffer);
        printf("%s\n", json);
        // Extract HTTP method and URL path from the incoming request
        char http_method[10];
        char requested_url[256];
        sscanf(buffer, "%9s %255s", http_method, requested_url);

        if (route_handler(http_method, requested_url, config, &new_socket) < 0)
        {
            if (response(new_socket, HTTP_STATUS_NOT_FOUND, "Not Found") < 0)
            {
                close(new_socket);
            }
        }
        close(new_socket);
    }
}

int main()
{
    RouteConfig config = initialize_routes();
    printf("DEFINED ROUTE; %s\n ", config.routes->path);
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10, launch);
    printf("DEFINED ROUTE; %s\n ", config.routes->path); // nulls out here due to constructor.
    server.launch(&server, &config);
}
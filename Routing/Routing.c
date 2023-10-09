
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Routing.h"
#include "Network/Server.h"
#include "HTTP_status/HTTP_status.h"

void index_handler(int client_socket)
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
// Defines routes
RouteConfig initialize_routes()
{
    // Define your routes
    Route routes[] = {
        {"GET", "/something", index_handler},
        {"GET", "/users/:id", handler_second},
        //{"GET", "/products/:code", index_handler},
        // Add more routes here
    };

    RouteConfig config = {
        .routes = routes,
        .num_routes = sizeof(routes) / sizeof(Route),
    };

    return config;
}
// handles routing and calls the appropiate route.
int route_handler(const char *http_method, const char *requested_path, RouteConfig *config, int *socket)
{
    for (int i = 0; i < config->num_routes; i++)
    {

        Route *route = &config->routes[i];
        int match = match_path(route->path, requested_path);
        int comp = strcmp(route->method, http_method);
        if (comp == 0 && match == 0)
        {
            route->handler(*socket);
            return 0;
        }
    }
    return -1;
}

// path matcher
// review this code
int match_path(const char *route_path, const char *requested_path)
{
    while (*route_path != '\0' && *requested_path != '\0')
    {
        if (*route_path == *requested_path || *route_path == ':' || *route_path == '?')
        {
            if (*route_path == ':')
            {
                while (*requested_path != '/' && *requested_path != '?' && *requested_path != '\0')
                {
                    requested_path++;
                }
            }
            else if (*route_path == '?')
            {
                while (*requested_path != '/' && *requested_path != '\0')
                {
                    requested_path++;
                }
            }
            else
            {
                route_path++;
                requested_path++;
            }
        }
        else
        {
            return -1;
        }
    }
    return *route_path == '\0' && *requested_path == '\0';
}
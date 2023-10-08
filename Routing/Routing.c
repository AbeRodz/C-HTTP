
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
// Defines routes
RouteConfig initialize_routes()
{
    // Define your routes
    Route routes[] = {
        {"GET", "/", index_handler}
        //{"GET", "/users/:id", user_handler},
        //{"GET", "/products/:code", product_handler},
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
        if (route != NULL)
        {
            if (route->path != NULL)
            {
                printf("CURRENT ROUTE: %s\n", route->path);
            }
            else
            {
                printf("RDEFINED ROUTE; %s", config->routes[i].path);
                printf("Route path is NULL\n");
            }
        }
        else
        {
            printf("Invalid route\n");
        }

        if (strcmp(route->method, http_method) == 0 && match_path(route->path, requested_path))
        {
            route->handler(*socket);
            return 0;
        }
    }
    return -1;
}

// path matcher
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
    }
    return -1;
}
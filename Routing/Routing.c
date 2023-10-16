
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <regex.h>
#include "Routing.h"
#include "Network/Server.h"

// TODO
int parse_route_params(const char *route_pattern, const char *path, char *param)
{
    // Extract parameter value using placeholders
    int matched = sscanf(path, route_pattern, param);
    return matched == 1;
}
// handles routing and calls the appropiate route handler or returns an error.
int route_handler(const char *http_method, const char *requested_path, RouteNode *config, int *socket)
{

    RouteNode *path = pathFinder(config, requested_path);
    if (path == NULL)
    {
        return -1;
    }

    if (strcmp(path->method, http_method) < 0)
    {
        return 1;
    }
    if (path->handler != NULL)
    {
        path->handler(*socket);
        return 0;
    }
    return -1;
}

RouteNode *pathFinder(RouteNode *root, const char *path)
{

    RouteNode *current = root;

    while (*path != '\0')
    {
        const char *segment = path;
        int i = 0;

        while (*path != '/' && *path != '\0')
        {
            path++;
        }

        current = findChild(current, segment);

        if (current == NULL)
        {
            return NULL;
        }

        if (*path == '/')
        {
            path++;
        }
    }

    return current;
}
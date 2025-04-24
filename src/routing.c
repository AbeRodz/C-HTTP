
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <regex.h>
#include "routing.h"
#include "server.h"

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

RouteNode *newNode(const char *character)
{

    RouteNode *node = (RouteNode *)malloc(sizeof(RouteNode));
    node->character = character;
    node->handler = NULL;
    node->method = NULL;
    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        node->children[i] = NULL;
    }
    node->childrenCount = 0;

    return node;
};

void addRouteNode(RouteNode *root, const char *route, const char *method, void (*handler)(int))
{
    RouteNode *node = root;
    const char *path = route;

    while (*path != '\0')
    {
        const char *segment = path;
        int i = 0;

        // Extract the requested path
        while (*path != '/' && *path != '\0')
        {
            path++;
        }

        RouteNode *child = findChild(node, segment);

        if (child == NULL)
        {
            child = newNode(segment);
            addChild(node, child);
        }

        node = child;

        if (*path == '/')
        {
            path++;
        }
    }

    // Set the HTTP method and handler on the node
    node->method = method;
    node->handler = handler;
}

void addChild(RouteNode *parent, RouteNode *child)
{
    if (parent->childrenCount < MAX_CHILDREN)
    {
        parent->children[parent->childrenCount] = child;
        parent->childrenCount++;
    }
}

RouteNode *findChild(RouteNode *node, const char *segment)
{

    for (int i = 0; i < node->childrenCount; i++)
    {
        if (strcmp(node->children[i]->character, segment) == 0)
        {
            return node->children[i];
        }
    }
    return NULL;
}

// helper function to free memory from each node.
void freeRouteTree(RouteNode *node) {
    if (node == NULL) return;
    for (int i = 0; i < node->childrenCount; ++i) {
        freeRouteTree(node->children[i]);
    }
    free(node);
}
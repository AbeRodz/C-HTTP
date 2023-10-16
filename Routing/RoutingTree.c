
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Routing.h"

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
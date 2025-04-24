#ifndef ROUTING_H
#define ROUTING_H
#include <regex.h>

#define MAX_SEG_LENGTH 32
#define MAX_CHILDREN 128

// RouteNode is based on a trie data structure, that represents a route.
typedef struct RouteNode RouteNode;

struct RouteNode
{
    const char *character;             // URL path (e.g., "/users/:id")
    const char *method;                // HTTP method (e.g., "GET", "POST")
    void (*handler)(int);              // Request handler function
    RouteNode *children[MAX_CHILDREN]; // max amount of childrens in a node.
    int childrenCount;                 // quantity of childrens in a node.
};
/// @brief Creates a new Node on the trie.
/// @param character  (const char *)
/// @return (RouteNode) A new Node.
RouteNode *newNode(const char *character);

/// @brief Adds a new route onto an existing Trie.
/// @param root (RouteNode) A trie instance of RouteNode.
/// @param route (const char *) A string representing a new Node.
/// @param method (const char *) The HTTP method defined for this Node.
/// @param handler  (void (*handler)(int)) The route handler function.
void addRouteNode(RouteNode *root, const char *route, const char *method, void (*handler)(int));

/// @brief Finds the path or route defined on a Node.
/// @param node (RouteNode) A trie instance of RouteNode.
/// @param path (const char *) The requested path by the client, to be searched.
/// @return (RouteNode) The defined Node that contains the requested path.
RouteNode *pathFinder(RouteNode *node, const char *path);

/// @brief Adds a child onto a Node.
/// @param parent (RouteNode) A parent Node.
/// @param child (RouteNode) A defined Node to set as a children.
void addChild(RouteNode *parent, RouteNode *child);

/// @brief Finds a children RouteNode in a parent Node.
/// @param node Parent Node to search.
/// @param segment (const char *) A path to be searched.
/// @return (RouteNode) The children RouteNode.
RouteNode *findChild(struct RouteNode *node, const char *segment);

/// @brief
/// @param http_method  (const char *) The HTTP method defined for this Node.
/// @param requested_path (const char *) The requested path by the client, to be searched.
/// @param config  (RouteNode) A trie instance of RouteNode.
/// @param socket (int *) The socket running.
/// @return (int) An error defined as an int.
int route_handler(const char *http_method, const char *requested_path, RouteNode *config, int *socket);


/// @brief Frees a children RouteNode in a parent Node recursively.
/// @param node Parent Node to search.
void freeRouteTree(RouteNode *node);
#endif /* ROUTING_H */
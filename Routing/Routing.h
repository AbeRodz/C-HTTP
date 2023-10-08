#ifndef ROUTING_H
#define ROUTING_H

// Define a structure to represent a route
typedef struct
{
    const char *method;   // HTTP method (e.g., "GET", "POST")
    const char *path;     // URL path (e.g., "/users/:id")
    void (*handler)(int); // Request handler function
} Route;

// Define a structure to hold your route configuration
typedef struct
{
    Route *routes;  // Array of routes
    int num_routes; // Number of routes
} RouteConfig;

RouteConfig initialize_routes();

int route_handler(const char *http_method, const char *requested_path, RouteConfig *config, int *socket);
int match_path(const char *route_path, const char *requested_path);
#endif /* ROUTING_H */
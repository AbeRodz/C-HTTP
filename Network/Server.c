#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "Server.h"
// #include "Routing/Routing.h"
#include "HTTP_status/HTTP_status.h"
// Define HTTP response headers
const char *http_response_headers = "HTTP/1.1 %d %s\r\n"
                                    "Content-Type: application/json\r\n"
                                    "Content-Length: %zu\r\n"
                                    "\r\n";
// Constructor of an http server
struct Server server_constructor(int domain, int service, int protocol, unsigned long interface,
                                 int port, int backlog)
{
    struct Server server;
    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.interface = interface;
    server.port = port;
    server.backlog = backlog;
    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(interface);

    server.socket = socket(domain, service, protocol);
    int true = 1;
    setsockopt(server.socket, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int));
    if (server.socket == 0)
    {
        perror("failed to connect socket...\n");
        exit(1);
    }
    if (bind(server.socket, (struct sockaddr *)&server.address,
             sizeof(server.address)) < 0)
    {
        perror("failed to bind socket...\n");
        exit(1);
    };

    if ((listen(server.socket, server.backlog)) < 0)
    {
        perror("failed to listen...\n");
        exit(1);
    }
    // server.launch = *launch;

    return server;
};

// Function to send data with buffering
int send_with_buffer(int client_socket, const char *data, size_t length)
{
    // Define a buffer size suitable for your application
    size_t buffer_size = 1024;
    char buffer[buffer_size];

    size_t bytes_sent = 0;
    while (bytes_sent < length)
    {
        size_t bytes_to_send = length - bytes_sent;
        if (bytes_to_send > buffer_size)
        {
            bytes_to_send = buffer_size;
        }

        memcpy(buffer, data + bytes_sent, bytes_to_send);

        if (send(client_socket, buffer, bytes_to_send, 0) < 0)
        {
            return -1;
        }
        bytes_sent += bytes_to_send;
    }
    return 0;
}

// Function to create an HTTP response
int response(int client_socket, int status_code, const char *json_data)
{
    // Calculate the content length
    size_t content_length = strlen(json_data);
    const char *http_status_text = get_http_status_text(status_code);
    // Create the HTTP response header
    char response_header[1024];
    snprintf(response_header, sizeof(response_header), http_response_headers, status_code, http_status_text, content_length);

    // Send the response header
    if (send(client_socket, response_header, strlen(response_header), 0) < 0)
    {
        perror("couldn't send headers...\n");
        return -1;
    }
    if (send_with_buffer(client_socket, json_data, content_length) < 0)
    {
        perror("couldn't send payload...\n");
        return -1;
    }

    return 0;
}

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

void start(struct Server *server, RouteConfig config)
{
    char buffer[30000];
    char json[300];
    snprintf(json, sizeof(json),
             "{"
             "   \"received_data\": \"hello\""
             "}");
    int address_length = sizeof(server->address);
    int new_socket;
    // Route *route = &config->routes[0];
    for (int i = 0; i < config.num_routes; i++)
    {
        printf("Route: Method=%s, Path=%s\n", config.routes[i].method, config.routes[i].path);
        // Call the associated request handler function
        // config.routes[i].handler(123); // Passing a dummy context value
    }
    for (int i = 0; i < config.num_routes; i++)
    {
        Route route = config.routes[i];
        if (&route != NULL)
        {
            printf("config is not NULL\n");
            printf("%s %d\n", route.path, config.num_routes);
            if (route.method != NULL)
            {
                printf("CURRENT ROUTE: %s\n", route.method);
            }
            else
            {
                printf("RDEFINED ROUTE; %s", route.path);
                printf("Route path is NULL\n");
            }
        }
        else
        {
            printf("Invalid route\n");
        }
    }

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

        if (route_handler(http_method, requested_url, &config, &new_socket) < 0)
        {
            if (response(new_socket, HTTP_STATUS_NOT_FOUND, "{"
                                                            "   \"error\": \"not found\""
                                                            "}") < 0)
            {
                close(new_socket);
            }
        }
        close(new_socket);
    }
}
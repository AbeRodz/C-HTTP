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
struct Server server_constructor(int domain, int service, int protocol, unsigned long interface, int port, int backlog, void (*launch)(struct Server *server, RouteConfig *config))
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
    server.launch = launch;

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
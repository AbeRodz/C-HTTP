// Server.h

#ifndef Server_h
#define Server_h

#include <netinet/in.h> // Include the correct header for sockaddr_in
#include <sys/socket.h> // Include the correct header for socket-related functions
#include "routing.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

struct Server {
    int domain;
    int service;
    int protocol;
    unsigned long interface;
    int port;
    int backlog;
    struct sockaddr_in address;
    int socket;
};

struct Server server_constructor(int domain, int service, int protocol, unsigned long interface,
                                 int port, int backlog);
void start(struct Server * server, RouteNode * config);
int response(int client_socket, int status_code, const char * json_data);
int send_with_buffer(int client_socket, const char * data, size_t length);

#endif /* Server_h */

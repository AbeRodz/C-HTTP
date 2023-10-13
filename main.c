#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "Network/Server.h"
#include "Routing/Routing.h"

int main()
{

    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10);

    RouteConfig config = initialize_routes();
    start(&server, &config);
}
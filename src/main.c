#include "http.h"
#include "server.h"
#include "utils.h"
#include <signal.h>
#include <stdlib.h>

#define DEFAULT_PORT 8080

volatile sig_atomic_t stop;

void int_handler(int sig) { stop = 1; }

int main(int argc, char *argv[])
{
    // Handle Ctrl+C for shutdown
    signal(SIGINT, int_handler);

    // Default port
    int port = DEFAULT_PORT;

    // Command line argument parsing for the port
    if (argc > 1)
    {
        port = atoi(argv[1]);
        if (port <= 0 || port > 65535)
        {
            log_error("Invalid port number. Using default port %d.",
                      DEFAULT_PORT);
            port = DEFAULT_PORT;
        }
    }

    log_info("Starting HTTP server on port %d...", port);

    // Start the server
    if (start_server(port, &stop) != 0)
    {
        log_error("Failed to start server.");
        return EXIT_FAILURE;
    }

    log_info("Server stopped.");
    return EXIT_SUCCESS;
}

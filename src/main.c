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
    /*
     * These lines are necessary to ensure SA_RESTART isn't enabled
     * Which is enabled by default on linux
     * If it is enabled, it won't allow shutdown while blocked in accept()
     * And we don't want to wait for a request after pressing Ctrl+C
     */
    struct sigaction sa;
    sa.sa_handler = int_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        log_perror("sigaction failed");
        return EXIT_FAILURE;
    }

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

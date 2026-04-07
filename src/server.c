#include "server.h"
#include "http.h"
#include "utils.h"
#include <arpa/inet.h>
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_PENDING_CONNECTIONS 10
#define BUFFER_SIZE 4096

int start_server(int port, volatile sig_atomic_t *stop_flag)
{
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        log_perror("socket failed");
        return -1;
    }

    // Set socket options to allow reuse of address and port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt)))
    {
        log_perror("setsocket failed");
        close(server_fd);
        return -1;
    }

    // Bind the socket to the network address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Listen on any interface
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        log_perror("bind failed");
        close(server_fd);
        return -1;
    }

    // Start listening for incoming connections
    if (listen(server_fd, MAX_PENDING_CONNECTIONS) < 0)
    {
        log_perror("listen failed");
        close(server_fd);
        return -1;
    }

    log_info("Server listening on port %d...", port);

    // Accept connections in a loop
    while (!(*stop_flag))
    {
        int client_socket;
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        client_socket = accept(server_fd, (struct sockaddr *)&client_addr,
                               &client_addr_len);

        if (*stop_flag)
        {
            // If woken up by a signal while blocked in accept()
            log_info("Accept interrupted, shutting down.");
            break;
        }

        if (client_socket < 0)
        {
            // If not interrupted, it's a real error
            if (errno != EINTR)
            {
                log_perror("accept failed");
            }
            else
            {
                log_info("Accept interrupted by signal.");
            }
            continue; // Try accepting again
        }

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
        log_info("Connection accepted from %s:%d", client_ip,
                 ntohs(client_addr.sin_port));

        // Handle the client connection
        handle_client_connection(client_socket);

        // Close the client client socket
        close(client_socket);
        log_info("Connection from %s:%d closed.", client_ip,
                 ntohs(client_addr.sin_port));
    }

    // Close the server socket
    close(server_fd);
    log_info("Server socket closed.");
    return 0;
}

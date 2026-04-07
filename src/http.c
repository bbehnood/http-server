#include "http.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

// Function to handle client connections
void handle_client_connection(int client_socket)
{
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_read;

    // Receive the HTTP request
    bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_read < 0)
    {
        log_perror("recv failed");
        return;
    }
    if (bytes_read == 0)
    {
        log_info("Client disconnected.");
        return;
    }

    buffer[bytes_read] = '\0'; // Null-terminate the received data
    log_debug("Received request:\n%s", buffer);

    // Parse the request
    parse_http_request(buffer, bytes_read);

    // Prepare and send the response
    send_http_response(client_socket);
}

// Placeholder: Parse the incoming HTTP request
void parse_http_request(const char *request_data, ssize_t data_len)
{
    // TODO: Implement robust HTTP request parsing

    log_debug("Parsing HTTP request (implement this!)...");
}

// Placeholder: Prepare and send an HTTP response
void send_http_response(int client_socket)
{
    const char *response_body = "Hello from your C server!";
    char response_header[BUFFER_SIZE];

    snprintf(
        response_header, sizeof(response_header),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n" // Tell the client we'll close the connection
        "\r\n",                 // End of headers
        strlen(response_body));

    if (send(client_socket, response_header, strlen(response_header), 0) < 0)
    {
        log_perror("send failed for header");
    }

    if (send(client_socket, response_body, strlen(response_body), 0) < 0)
    {
        log_perror("send failed for body");
    }

    log_debug("Sent HTTP response.");
}

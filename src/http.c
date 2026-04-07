#include "http.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

// Function to handle client connections
void handle_client_connection(int client_socket)
{
    HttpRequest request;
    int parsed_result;

    parsed_result = parse_http_request(client_socket, &request);

    if (parsed_result > 0)
    {
        if (send_http_response(client_socket, &request) < 0)
        {
            log_error("Failed to send response to client %d", client_socket);
        }
    }
    else if (parsed_result == 0)
    {
        log_info("Client %d disconnected before request could be fully read.",
                 client_socket);
    }
    else
    {
        log_error(
            "Error parsing request from client %d. Sending error response.",
            client_socket);
        // TODO: send a 400 Bad Request here
    }

    close(client_socket);
}

// Placeholder: Parse the incoming HTTP request
int parse_http_request(int client_socket, HttpRequest *request)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    // Clear the request structure
    memset(request, 0, sizeof(HttpRequest));
    memset(buffer, 0, sizeof(buffer));

    // Read data from the client
    bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received < 0)
    {
        log_perror("recv failed");
        return -1; // Error
    }
    if (bytes_received == 0)
    {
        log_info("Client disconnected");
        return 0; // Client disconnected
    }

    buffer[bytes_received] = '\0'; // Ensure Null-termination

    log_debug("Received request:\n%s", buffer);

    // Find the end of the first line
    char *request_line_end = strstr(buffer, "\r\n");
    if (request_line_end == NULL)
    {
        log_error("Malformed request: No CRLF found");
        // TODO: send a 400 Bad Request here
        return -1;
    }
    // Null-terminate the request line to use sscanf
    *request_line_end = '\0';

    // Use sscanf to parse the request line
    if (sscanf(buffer, "%15s %255s %31s", request->method, request->uri,
               request->version) != 3)
    {
        log_error("Malformed request line: %s", buffer);
        // TODO: send a 400 Bad Request here
        *request_line_end = '\r';
        return -1;
    }
    *request_line_end = '\r';

    log_debug("Parsed Method: %s, URI: %s, Version: %s", request->method,
              request->uri, request->version);

    // TODO: Parse headers and body
    // TODO: Handle request buffer potentially being too small

    return 1; // Successfully parsed something
}

// Placeholder: Prepare and send an HTTP response
int send_http_response(int client_socket, const HttpRequest *request)
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

    log_debug("Sending response header:\n%s", response_header);

    if (send(client_socket, response_header, strlen(response_header), 0) < 0)
    {
        log_perror("send failed for header");
        return -1;
    }

    if (send(client_socket, response_body, strlen(response_body), 0) < 0)
    {
        log_perror("send failed for body");
        return -1;
    }

    log_debug("Sent HTTP response.");
    return 0;
}

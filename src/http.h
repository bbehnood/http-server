#ifndef HTTP_H
#define HTTP_H

#include <sys/types.h>

// Struct to hold parsed request data
typedef struct
{
    char method[16];
    char uri[256];
    char version[32];
} HttpRequest;

/**
 * @brief Handles the full lifecycle of a client connection.
 * Receives an HTTP request, parses it, and sends an http response.
 *
 * @param client_socket The file descriptor for the connected client socket.
 */
void handle_client_connection(int client_socket);

/**
 * @brief Parses the raw HTTP request data.
 * This is a placeholder; detailed implementation is needed.
 *
 * @param request_data Pointer to the buffer containing the request .
 * @param data_len Length of the data in the buffer.
 */
int parse_http_request(int client_socket, HttpRequest *request);

/**
 * @brief Prepares and sends an HTTP response to the client.
 * This is a placeholder; detailed implementation is needed.
 *
 * @param client_socket The file descriptor for the client socket.
 */
int send_http_response(int client_socket, const HttpRequest *request);

#endif // !HTTP_H

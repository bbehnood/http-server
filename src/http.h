#ifndef HTTP_H
#define HTTP_H

#include <sys/types.h>

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
void parse_http_request(const char *request_data, ssize_t data_len);

/**
 * @brief Prepares and sends an HTTP response to the client.
 * This is a placeholder; detailed implementation is needed.
 *
 * @param client_socket The file descriptor for the client socket.
 */
void send_http_response(int client_socket);

#endif // !HTTP_H

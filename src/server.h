#ifndef SERVER_H
#define SERVER_H

#include <signal.h>

/**
 * @brief Starts the HTTP server.
 *
 * @param port The port number to listen on.
 * @param stop_flag A pointer to a volatile sig_atomic_t flag that signals
 * shutdown.
 * @return 0 on success, -1 on failure.
 */
int start_server(int port, volatile sig_atomic_t *stop_flag);

#endif // !SERVER_H

#ifndef UTILS_H
#define UTILS_H

#include <errno.h>
#include <stdarg.h>

// Define DEBUG_MODE during compilation (e.g., using CMake's
// add_compile_definitions) to enable verbose logging. Example:
// add_compile_definitions(DEBUG_MODE)

/**
 * @brief Logs an informational message if DEBUG_MODE is defined.
 */
#define log_debug(format, ...) log_message("DEBUG", format, ##__VA_ARGS__)

/**
 * @brief Logs an info message if DEBUG_MODE is defined.
 */
#define log_info(format, ...) log_message("INFO", format, ##__VA_ARGS__)

/**
 * @brief Logs an error message to stderr (always shown).
 */
void log_error(const char *format, ...);

/**
 * @brief Logs a perror message (including system error description).
 */
void log_perror(const char *msg);

/**
 * @brief Generic logging function.
 * @param level The log level string (e.g., "INFO", "DEBUG").
 * @param format The format string for the message.
 */
void log_message(const char *level, const char *format, ...);

#endif // !UTILS_H

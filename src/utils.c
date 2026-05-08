#include "utils.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define LOG_BUFFER_SIZE 256

// Simple logging implementation
void log_message(const char *level, const char *format, ...)
{
#ifdef DEBUG_MODE
    char buffer[LOG_BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char timestamp[30];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &tm);

    fprintf(stdout, "[%s] [%s] %s\n", timestamp, level, buffer);
    fflush(stdout);
#endif
}

void log_error(const char *format, ...)
{
    char buffer[LOG_BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char timestamp[30];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &tm);

    fprintf(stderr, "[ERROR] [%s] %s\n", timestamp, buffer);
    fflush(stderr);
}

void log_perror(const char *msg)
{
#ifndef DEBUG_MODE
    char error_buffer[LOG_BUFFER_SIZE];
    snprintf(error_buffer, sizeof(error_buffer), "%s: %s", msg,
             strerror(errno));
    log_error("%s", error_buffer);
#else
    // In debug mode, use perror for more detailed system errors
    perror(msg);
#endif
}

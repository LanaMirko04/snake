/*
 * SLog (Shitty Logging) - slog.h
 * (c) 2023 Lana Mirko
 *
 */

#ifndef __SLOG_H__
#define __SLOG_H__

#include <stdio.h>

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumeration representing different log levels.
 */
enum slog_level_e {
  LV_INFO   = 0x01, /**< Informational messages */
  LV_DEBUG  = 0x02, /**< Debugging messages */
  LV_WARN   = 0x04, /**< Warning messages */
  LV_ERROR  = 0x08, /**< Error messages */
  LV_ALL    = 0x0F  /**< All log levels */
};

/**
 * @brief Global variables for controlling logging behavior.
 * @private
 */
extern FILE *__log_file; /**< File pointer for logging */
extern int __log_level; /**< Current log level */

/**
 * @def SLOG_INIT(path, log_level)
 * @brief Initializes the logging system.
 *
 * This function initializes the logging system and sets the log file path and
 * log level.
 *
 * @param path The path to the log file.
 * @param log_level The logging level (combination of slog_level_e flags).
 */
#define SLOG_INIT(path, log_level) __slog_init(path, log_level)

/**
 * @def SLOG_INFO(message, ...)
 * @brief Logs an informational message.
 *
 * @param message The format string for the log message.
 * @param ... Additional parameters to be formatted into the message.
 *
 * Example usage:
 * @code
 * SLOG_INFO("Received message: %s", message);
 * @endcode
 */
#define SLOG_INFO(message, ...) \
  __slog_log(LV_INFO, BOLD GREEN "[INFO]" RESET " %s:%d -> " message "\n", \
      __FILE__, __LINE__ __VA_OPT__(,) __VA_ARGS__)

/**
 * @def SLOG_DEBUG(message, ...)
 * @brief Logs a debugging message.
 *
 * @param message The format string for the log message.
 * @param ... Additional parameters to be formatted into the message.
 */
#define SLOG_DEBUG(message, ...) \
  __slog_log(LV_DEBUG, BOLD BLUE "[DEBUG]" RESET " %s:%d -> " message "\n", \
      __FILE__, __LINE__ __VA_OPT__(,) __VA_ARGS__)

/**
 * @def SLOG_WARN(message, ...)
 * @brief Logs a warning message.
 *
 * @param message The format string for the log message.
 * @param ... Additional parameters to be formatted into the message.
 */
#define SLOG_WARN(message, ...) \
  __slog_log(LV_WARN, BOLD YELLOW "[WARNING]" RESET " %s:%d -> " message "\n", \
      __FILE__, __LINE__ __VA_OPT__(,) __VA_ARGS__)

/**
 * @def SLOG_ERROR(message, ...)
 * @brief Logs an error message.
 *
 * @param message The format string for the log message.
 * @param ... Additional parameters to be formatted into the message.
 */
#define SLOG_ERROR(message, ...) \
  __slog_log(LV_ERROR, BOLD RED "[ERROR]" RESET " %s:%d -> " message "\n", \
      __FILE__, __LINE__ __VA_OPT__(,) __VA_ARGS__)

/**
 * @brief Initializes the logging system.
 *
 * This function is used internally by the SLOG_INIT macro to initialize
 * the logging system and set the log file path and log level.
 *
 * @param path The path to the log file.
 * @param log_level The logging level (combination of slog_level_e flags).
 * @private
 */
extern void __slog_init(const char *path, int log_level);

/**
 * @brief Closes the log file.
 *
 * This function is called automatically when the program exits.
 * @private
 */
extern void __slog_close_file(void);

/**
 * @brief Opens the log file at the specified path.
 *
 * This function is used internally by the SLOG_INIT macro to open the log file
 * at the specified path (if path is not NULL).
 *
 * @param path The path to the log file.
 * @private
 */
extern void __slog_open_file(const char *path);

/**
 * @brief Logs a message at the specified log level.
 *
 * This function is used internally by the logging macros to log messages
 * at different log levels.
 *
 * @param level The log level (combination of slog_level_e flags).
 * @param format The format string for the log message.
 * @param ... Additional parameters to be formatted into the message.
 * @private
 */
extern void __slog_log(enum slog_level_e level, char *format, ...);

/**
 * @brief Removes ANSI color codes from a string.
 *
 * This function is used internally to remove ANSI color codes from a string
 * when writing to the log file or to a pipe.
 *
 * @param str The input string containing color codes.
 * @return A new string with color codes removed.
 * @private
 */
char* __slog_remove_color(char *str);

#ifdef __cplusplus
}
#endif

#endif


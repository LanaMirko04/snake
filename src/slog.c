/*
 * SLog (Shitty Logging) - slog.h
 * (c) 2023 Lana Mirko
 *
 * */

/* Define POSIX source */
#define _POSIX_C_SOURCE 200809L

/* ANSI C headers */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
/* POSIX headers */
#include <unistd.h>
/* Local headers */
#include "slog.h"

FILE *__log_file = NULL;
int __log_level = { 0 };

void __slog_init(const char *path, int log_level) {
  if (path != NULL) {
    __slog_open_file(path);
  }

  __log_level = log_level;
}

void __slog_close_file(void) {
  if (__log_file != NULL) {
    fclose(__log_file);
    __log_file = NULL;
  }
}

void __slog_open_file(const char *path) {
  if (__log_file != NULL)
    return;

  __log_file = fopen(path, "w");
  if (__log_file == NULL) {
    fprintf(stderr, "I can't open '%s': %s", path, strerror(errno));
    exit(EXIT_FAILURE);
  }

  atexit(__slog_close_file);
}

void __slog_log(enum slog_level_e level, char *format, ...) {
  va_list args;
  va_start(args, format);
  _Bool use_file = __log_file != NULL;
  _Bool use_color = !isatty(fileno(stdout));
  char *clean_format = NULL;

  if (use_file || use_color) {
    clean_format = __slog_remove_color(format);
  }

  switch (level) {
    case LV_INFO:
      if (__log_level & LV_INFO) {
        vfprintf(use_file ? __log_file : stdout,
            use_file || use_color ? clean_format  : format, args);
      }
      break;

    case LV_WARN:
      if (__log_level & LV_WARN) {
        vfprintf(use_file ? __log_file : stdout,
            use_file || use_color ? clean_format  : format, args);
      }
      break;

    case LV_DEBUG:
      if (__log_level & LV_DEBUG) {
        vfprintf(use_file ? __log_file : stdout,
            use_file || use_color ? clean_format  : format, args);
      }
      break;

    case LV_ERROR:
      if (__log_level & LV_ERROR) {
        vfprintf(use_file ? __log_file : stderr,
            use_file || use_color ? clean_format  : format, args);
      }
      break;

    case LV_ALL:
    default:
      break;
  }

  if (clean_format != NULL) {
    free(clean_format);
  }

  va_end(args);
}

char* __slog_remove_color(char *str) {
  char *clean_str = malloc(strlen(str) + 1);
  int i = 0, j = 0;

  while (str[i] != '\0') {
    if (str[i] == '\033') {
      while (str[i] != 'm')
        i++;
    } else {
      clean_str[j] = str[i];
      j++;
    }
    i++;
  }
  clean_str[j] = '\0';

  return clean_str;
}

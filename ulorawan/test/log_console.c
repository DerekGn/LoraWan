#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>

#include "log_hal.h"

static const char *level_strings[] = {
  "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

static const char *level_colors[] = {
  "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
};

void log_hal_log(enum log_hal_log_level level, const char *file, int line,
                 const char *fmt, ...)
{
  char buf[16];
  va_list vl;

  time_t t = time(NULL);
 
  buf[strftime(buf, sizeof(buf), "%H:%M:%S", localtime(&t))] = '\0';

  va_start(vl, fmt);

  fprintf(
    stderr, 
    "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ",
    buf,
    level_colors[level],
    level_strings[level],
    file,
    line);

  vfprintf(stderr, fmt, vl);
  fprintf(stderr, "\n");
  fflush(stderr);
  
  va_end(vl);
}
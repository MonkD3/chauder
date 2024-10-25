#ifndef __CHAUDER_LOG
#define __CHAUDER_LOG

#include <stdio.h>

#define _LOG(lvl, fmt, ...)                                                             \
    do {                                                                                \
        fprintf(stderr, "[" lvl "-%s:%d]" fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    } while (0);

#define CRITICAL_ERROR(fmt, ...) _LOG("CRITIAL ERROR", fmt, ##__VA_ARGS__);

#if VERBOSE > 0
#define ERROR(fmt, ...) _LOG("ERROR", fmt, ##__VA_ARGS__);
#else
#define ERROR(fmt, ...)
#endif

#if VERBOSE > 1
#define WARNING(fmt, ...) _LOG("WARNING", fmt, ##__VA_ARGS__);
#else
#define WARNING(fmt, ...)
#endif

#if VERBOSE > 2
#define INFO(fmt, ...) _LOG("INFO", fmt, ##__VA_ARGS__);
#else
#define INFO(fmt, ...)
#endif

#if VERBOSE > 3
#define DEBUG(fmt, ...) _LOG("DEBUG", fmt, ##__VA_ARGS__);
#else
#define DEBUG(fmt, ...)
#endif

#endif  // __CHAUDER_LOG

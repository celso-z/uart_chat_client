#ifndef TIME_H_
#define TIME_H_
#include <inttypes.h>

#define DAY_SECONDS 86400
#define HOUR_SECONDS 3600

uint32_t get_timestamp();
char *get_formatted_timestamp(uint32_t timestamp);

#endif

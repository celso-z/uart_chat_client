#ifndef CHECKSUM_H_
#define CHECKSUM_H_
#include <stdint.h>
#include <stddef.h>

int get_checksum(uint8_t *digest, char *hexdigest, const uint8_t *data, size_t databytes);

#endif

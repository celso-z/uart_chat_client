#ifndef PROTOCOL_H_
#define PROTOCOL_H_
#include <inttypes.h>

typedef struct {
    char *msg; //52 bits = 51 char + '\0'
    uint16_t orig_addr; //endereço da origem da comunicação 
    uint16_t dest_addr; //endereço de destino da comunicação
    uint32_t timestamp; //timestamp y2k
    char *checksum;     //checksum (id) 32 bits
}package_t;

int send_message(char *msg, uint16_t orig_addr, uint16_t dest_addr);

package_t *get_message();
#endif

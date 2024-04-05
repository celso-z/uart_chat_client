#ifndef PROTOCOL_H_
#define PROTOCOL_H_
#include <inttypes.h>

typedef struct {
    char msg[49]; //49 bits = 48 char + '\0'
    uint8_t orig_addr; //endereço da origem da comunicação 
    uint8_t dest_addr; //endereço de destino da comunicação
    uint32_t timestamp; //timestamp y2k
    char checksum[9];     //checksum (id) 32 bits
}package_t;

int send_message(char *msg, uint8_t orig_addr, uint8_t dest_addr);

package_t *get_message();
#endif

#include "./io.h"
#include "./protocol.h"
#include "./time.h"
#include <stdlib.h>
#include "./curses.h"

int send_message(char* msg, uint8_t orig_addr, uint8_t dest_addr){
    package_t *pkg = malloc(PACKET_SIZE);    
    if(pkg == NULL) return -1;
    //pkg->checksum = malloc(sizeof(char) * 65);
    //if(pkg->checksum == NULL) return -1;
    if(get_checksum(NULL, pkg->checksum, (uint8_t *)pkg, (size_t) 64) == -1) return -1;
    pkg->checksum[8] = '\0';
    pkg->orig_addr = orig_addr;
    pkg->dest_addr = dest_addr;
    pkg->timestamp = get_timestamp();
    for(int i = 0; i < 48; i++){
        pkg->msg[i] = msg[i];
    }
    pkg->msg[48] = '\0';
    if(serialize_package(pkg) == -1) return -1;
    free(pkg);
    
    return 0;
}

package_t *decode_package(void *raw_data){
    package_t *result = (package_t *)raw_data;
    return result;
}

package_t *get_package(){
    void *raw_data = deserialize_package();
    if(!raw_data) return NULL;
    package_t *p = decode_package(raw_data);
    display_canvas *t = init_screen();
    display_message(p, t);
    getch();
    end_screen(t);
    
    return p;
}

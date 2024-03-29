#include "./io.h"
#include "./protocol.h"
#include "./time.h"
#include <stdlib.h>

int send_message(char* msg, uint16_t orig_addr, uint16_t dest_addr){
    package_t *pkg = malloc(sizeof(uint32_t) * 16);    
    if(pkg == NULL) return -1;
    pkg->orig_addr = orig_addr;
    pkg->dest_addr = dest_addr;
    pkg->timestamp = get_y2k_timestamp();
    for(int i = 0; i < 51; i++){
        pkg->msg[i] = msg[i];
    }
    pkg->msg[51] = '\0';
    if(encode_package(pkg) == -1) return -1;
    free(pkg);
    
    return 0;
}

package_t *decode_package(void *raw_data){
    package_t *result = (package_t *)raw_data;
    return result;
}

package_t get_package(){
    void *raw_data = deserialize_package();
    if(!raw_data) return NULL;
    package_t = decode_package(raw_data);
    return package_t;
}

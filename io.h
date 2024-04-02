#ifndef IO_H_
#define IO_H_
#define PACKET_SIZE 64

void connection_init();
void *deserialize_package();
int serialize_package(void *pkg);

#endif

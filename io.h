#ifndef IO_H_
#define IO_H_
#define PACKAGE_SIZE 512

void connection_init();
void *deserialize_package();
int serialize_package(void *pkg);

#endif

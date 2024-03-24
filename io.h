#ifndef IO_H_
#define IO_H_
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <stdint.h>
    
#define BAUDRATE B9600
#define MODEMDEVICE "/dev/ttyUSB0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1
#define PACKAGE_SIZE 64

void connection_init();
void *get_package();
int send_package(void *pkg);

#endif

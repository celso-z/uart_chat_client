#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <inttypes.h>
    
#define BAUDRATE B9600
#define MODEMDEVICE "/dev/ttyUSB0"
#define _POSIX_SOURCE 1  POSIX compliant source 
#define FALSE 0
#define TRUE 1

#include "./io.h"
        
        
void signal_handler_IO (int status);   /* definition of signal handler */
int fd = -1;
struct termios oldtio;


void connection_init(){
    int c;
    struct termios oldtio,newtio;
    struct sigaction saio;           /* definition of signal action */
        
    /* open the device to be non-blocking (read will return immediatly) */
    fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd <0) {perror(MODEMDEVICE); exit(-1); }
        
    /* install the signal handler before making the device asynchronous */
    saio.sa_handler = signal_handler_IO;
    saio.sa_flags = 0;
    saio.sa_restorer = NULL;
    sigaction(SIGIO,&saio,NULL);
          
    /* allow the process to receive SIGIO */
    fcntl(fd, F_SETOWN, getpid());
    /* Make the file descriptor asynchronous (the manual page says only 
   O_APPEND and O_NONBLOCK, will work with F_SETFL...) */
    fcntl(fd, F_SETFL, FASYNC);
    
    tcgetattr(fd,&oldtio); /* save current port settings */
    /* set new port settings for canonical input processing */
    newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;
    newtio.c_cc[VMIN] = PACKET_SIZE - 1; /* Colocar aqui um valor macro do tamanho exato do pacote*/
    newtio.c_cc[VTIME]=0;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);
}

void *deserialize_package(){
    int res;
    void *pkg = malloc(PACKET_SIZE);
    if(pkg == NULL) return NULL;
    res = read(fd,pkg,PACKET_SIZE);
    return (void *) pkg;
}

int serialize_package(void *pkg){
    int res;
    if(pkg == NULL) return -1;
    res = write(fd, pkg, PACKAGE_SIZE);
    if(res != 64) return -1;
    return 0;
}
        
/***************************************************************************
* signal handler. sets wait_flag to FALSE, to indicate above loop that     *
* characters have been received.                                           *
***************************************************************************/
        
void signal_handler_IO (int status)
{
    printf("received SIGIO signal.\n");
    get_package();
}

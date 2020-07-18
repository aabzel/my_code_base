#ifndef TCP_SERVER_H
#define TCP_SERVER_H

//https://www.binarytides.com/winsock-socket-programming-tutorial/
//https://www.binarytides.com/winsock-socket-programming-tutorial/
#ifdef __cplusplus
extern "C" {
#endif

#include "custom_type.h"

bool launch_tcp_server (uint16_t tcpServerPort);

#ifdef __cplusplus
}
#endif

#endif /* TCP_SERVER_H */

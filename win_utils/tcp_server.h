#ifndef TCP_SERVER_H
#define TCP_SERVER_H

// https://www.binarytides.com/winsock-socket-programming-tutorial/
// https://www.binarytides.com/winsock-socket-programming-tutorial/
#ifdef __cplusplus
extern "C" {
#endif

#include "custom_type.h"

#define DEPLOY_TCP_SERVER

typedef struct {
    char userName[100];
    uint8_t mac_addr[6];
    uint16_t serverPort;
    uint32_t serverIP;
    char serverIPstr[100];
} ComputerServerParams_t;

typedef struct xDeviceInstance_t {
    char holderName[100];
    char deviceName[30];
    char spotTimeStr[300];
    uint8_t holderMac[8];
    // spot time
    uint32_t holderIp;
    uint64_t serialNumber;
    bool isbusy;
} xConnection_t;

extern ComputerServerParams_t serverPC;

bool launch_tcp_server (uint16_t tcpServerPort);

#ifdef __cplusplus
}
#endif

#endif /* TCP_SERVER_H */

#ifndef SCAN_SERIAL_PORT_H
#define SCAN_SERIAL_PORT_H

//https://www.xanthium.in/Serial-Port-Programming-using-Win32-API

#ifdef __cplusplus
extern "C" {
#endif

#include "custom_type.h"

#define MAX_COM_NUM 20

#define DEBUG_FAILED_OPENS 0

typedef enum {
    CAN_FLASHER = 1,
    UNDEF_DEVICE = 0
}deciceId_t;

typedef struct xConnection_t {
    char comPortName [30];
    char deviceName [30];
    bool isExistPort;
    bool isExistDevice;
    uint64_t serialNumber;
    uint16_t deviceID;
} xConnection_t;

extern xConnection_t deviceList [MAX_COM_NUM];

const char *dev_id_name(deciceId_t deviceID);
bool scan_serial (void);
bool print_device_list (void);
bool com_send_str (HANDLE hComm, char *txBuffer, uint32_t txBuffLen);
uint16_t parse_product (char *inStr, uint16_t inStrLen);
uint64_t parse_serial(char *inStr, uint16_t inStrLen, uint64_t *serialNUmber);

#ifdef __cplusplus
}
#endif

#endif /* SCAN_SERIAL_PORT_H */

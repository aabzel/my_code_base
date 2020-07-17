#include "scan_serial_port.h"

#include <stdio.h>
#include <windows.h>

#include "convert.h"
#include "str_ops.h"

xConnection_t deviceList [MAX_COM_NUM];

static bool com_set_params (HANDLE hComm) {
    bool res = false;
    // Initializing DCB structure
    DCB dcbSerialParams =
        { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    BOOL status = GetCommState (hComm, &dcbSerialParams);
    dcbSerialParams.BaudRate = 460800;  // Setting BaudRate = 460800
    dcbSerialParams.ByteSize = 8;         // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT;         // Setting StopBits = 1
    dcbSerialParams.Parity = NOPARITY;  // Setting Parity = None
    SetCommState (hComm, &dcbSerialParams);
    if (status) {
        res = true;
    }
    return res;
}

static bool com_set_timeout (HANDLE hComm) {
    bool res = false;
    COMMTIMEOUTS timeouts =
        { 0 };
    timeouts.ReadIntervalTimeout = 900; // in milliseconds
    timeouts.ReadTotalTimeoutConstant = 900; // in milliseconds
    timeouts.ReadTotalTimeoutMultiplier = 900; // in milliseconds
    timeouts.WriteTotalTimeoutConstant = 900; // in milliseconds
    timeouts.WriteTotalTimeoutMultiplier = 900; // in milliseconds
    SetCommTimeouts (hComm, &timeouts);
    return res;
}

bool com_send_str (HANDLE hComm, char *txBuffer, uint32_t txBuffLen) {
    bool res = false;
    BOOL status;
    DWORD dNoOfBytesWritten = 0;
    status = WriteFile (hComm, txBuffer, (DWORD) txBuffLen, &dNoOfBytesWritten, NULL);
    if (dNoOfBytesWritten == txBuffLen) {
        if (status) {
            res = true;
        }
    }

    return res;
}

static bool com_receive_remain (HANDLE hComm, uint32_t *outRealRxArrayLen) {
    bool res = false;
    if (NULL != outRealRxArrayLen) {
        *outRealRxArrayLen = 0;
        char tempChar;
        DWORD numberBytesRead;
        uint32_t BytesReadCnt = 0;
        bool loopRun = true;
        while (loopRun) {
            ReadFile (hComm,           //Handle of the Serial port
                &tempChar,       //Temporary character
                sizeof(tempChar),       //Size of TempChar
                &numberBytesRead,    //Number of bytes read
                NULL);
#if DEDUG_RX_CHAR
            printf ("%c", tempChar);
#endif
            if (0 < numberBytesRead) {
                loopRun = true;
            } else {
                loopRun = false;
            }
            BytesReadCnt++;
        };
        if (0 < BytesReadCnt) {
            *outRealRxArrayLen = BytesReadCnt;
            res = true;
        }
    }
    return res;
}

static bool com_receive_str (HANDLE hComm, char *outRxArray, uint32_t capasityRxArray, uint32_t *outRealRxArrayLen) {
    bool res = false;
    if ((0 < capasityRxArray) && (NULL != outRxArray)) {
        *outRealRxArrayLen = 0;
        char tempChar;
        DWORD numberBytesRead;
        uint32_t BytesReadCnt = 0;
        bool loopRun = true;
        while (loopRun) {
            ReadFile (hComm,           //Handle of the Serial port
                &tempChar,       //Temporary character
                sizeof(tempChar),       //Size of TempChar
                &numberBytesRead,    //Number of bytes read
                NULL);
#if DEDUG_RX_CHAR
            printf ("%c", tempChar);
#endif
            if (0 < numberBytesRead) {
                if (BytesReadCnt < capasityRxArray) {
                    outRxArray [BytesReadCnt] = tempChar;    // Store Tempchar into buffer
                }
            } else {
                loopRun = false;
            }
            BytesReadCnt++;
        };
        if (0 < BytesReadCnt) {
            *outRealRxArrayLen = BytesReadCnt;
            res = true;
        }
    }
    return res;
}

bool scan_serial (void) {
    bool res = false;
    char comNameStr [20] = "";
    uint8_t comPortNum;
    for (comPortNum = 0; comPortNum <= MAX_COM_NUM; comPortNum++) {

        snprintf (comNameStr, sizeof(comNameStr), "COM%u", comPortNum);
#if DEBUG_FAILED_OPENS
        printf ("\n try [%s]...", comNameStr);
#endif
        HANDLE hComm;
        hComm = CreateFile (comNameStr,                //port name
            GENERIC_READ | GENERIC_WRITE, //Read/Write
            0,                            // No Sharing
            NULL,                         // No Security
            OPEN_EXISTING,                         // Open existing port only
            0,            // Non Overlapped I/O
            NULL);        // Null for Comm Devices
#if DEBUG_FAILED_OPENS
        printf ("\n hComm [%p]", hComm);
#endif
        if (hComm == INVALID_HANDLE_VALUE) {
#if DEBUG_FAILED_OPENS
            printf ("\n  Error in opening serial port [%s]",comNameStr);
#endif
        } else {
#if DEBUG_SPOT_COM
            printf ("\n [%s] exists in PC", comNameStr);
#endif
            deviceList [comPortNum].isExistPort = true;
            CloseHandle (hComm);
        }

        snprintf (comNameStr, sizeof(comNameStr), "\\\\.\\COM%u", comPortNum);
        hComm = CreateFile (comNameStr, GENERIC_READ | GENERIC_WRITE, 0,                            // No Sharing
            NULL,                         // No Security
            OPEN_EXISTING,
            0,            // Non Overlapped I/O
            NULL);        // Null for Comm Devices
#if DEBUG_FAILED_OPENS
        printf ("\n hComm [%p]", hComm);
#endif
        if (hComm == INVALID_HANDLE_VALUE) {
#if DEBUG_FAILED_OPENS
            printf ("\n  Error in opening serial port [%s]",comNameStr);
#endif
        } else {
#if DEBUG_SPOT_COM
            printf ("\n [%s] exists in PC", comNameStr);
#endif
            deviceList [comPortNum].isExistPort = true;
            com_set_params (hComm);
            com_set_timeout (hComm);
            uint32_t realRxLen = 0;

            res = com_receive_remain (hComm, &realRxLen);

            char txBuffer [] = "vi\n\r";
            res = com_send_str (hComm, txBuffer, strlen (txBuffer));
            if (true == res) {
#if DEBUG_FINE_VI_REQ
                printf ("\n vi request ok!");
#endif
            } else {
                printf ("\n vi request fail!");
            }
            char rxBuffer [10000] = "";
            printf ("\n");
            res = com_receive_str (hComm, rxBuffer, sizeof(rxBuffer), &realRxLen);
            if (true == res) {
                if (0 < realRxLen) {
#if DEDUG_RX_TEXT
                    printf ("[%s]\n rx %u bytes", rxBuffer, realRxLen);
#endif
                    res = parse_serial (rxBuffer, realRxLen, &deviceList [comPortNum].serialNumber);
                    if (true == res) {
                        deviceList [comPortNum].isExistDevice = true;
                        deviceList [comPortNum].deviceID = parse_product (rxBuffer, realRxLen);
                    }
                } else {
                    printf ("\nLack of response");
                }
            } else {
                printf ("\n read fail!");
            }

            CloseHandle (hComm);
        }

    }

    print_device_list ();

    return res;
}

bool print_device_list (void) {
    bool out_res = false;
    uint32_t comPortNum = 0;
    for (comPortNum = 0; comPortNum < MAX_COM_NUM; comPortNum++) {
        if (true == deviceList [comPortNum].isExistPort) {
            printf ("\n COM[%u] ", comPortNum);
        }
        if (true == deviceList [comPortNum].isExistDevice) {
            printf ("Device exists. ");
            out_res = true;
        }
        if (true == deviceList [comPortNum].isExistDevice) {
            if (UNDEF_DEVICE != deviceList [comPortNum].deviceID) {
                printf (" Device %s ", dev_id_name (deviceList [comPortNum].deviceID));
            }
            printf ("Serial 0x%llx ", (long long unsigned int) deviceList [comPortNum].serialNumber);
        }
    }
    return out_res;
}

//CanFlasher on CanFlash Version 0.17.1.1.34 GCC Release 11/7/2020 19:34:29 FlashId:E58F0042 Serial:202B17D3015A by Arrival
uint64_t parse_serial (char *inStr, uint16_t inStrLen, uint64_t *outSerial64bNumber) {
    bool res = false;
    (void) inStrLen;
    //printf ("\n inStr[%s]", inStr);
    if (strlen ("Serial:") < inStrLen) {
        char *serialStartPtr = strstr (inStr, "Serial:");
        if (NULL != serialStartPtr) {
            uint16_t hexValLen;
            //printf ("\n serialStartPtr[%s]", serialStartPtr);
            //printf ("\n numstr[%s]", (serialStartPtr + strlen ("Serial:")));
            hexValLen = calc_hex_val_len ((serialStartPtr + strlen ("Serial:")));
            //printf ("\n hexValLen[%d]", hexValLen);
            res = try_strl2uint64_hex ((const char *) (serialStartPtr + strlen ("Serial:")), hexValLen, outSerial64bNumber);

        } else {
            printf ("\n lack Serial number in ");
        }
    }

    return res;
}

uint16_t parse_product (char *inStr, uint16_t inStrLen) {
    (void) inStrLen;
    uint16_t deviceID = UNDEF_DEVICE;
    char *devNameStartPtr;
    devNameStartPtr = strstr (inStr, "CanFlasher");
    if (NULL != devNameStartPtr) {
        deviceID = CAN_FLASHER;
    }
    devNameStartPtr = strstr (inStr, "TSTE_V1");
    if (NULL != devNameStartPtr) {
        deviceID = TSTE_V1;
    }

    devNameStartPtr = strstr (inStr, "TSTS_V1");
    if (NULL != devNameStartPtr) {
        deviceID = TSTS_V1;
    }
    devNameStartPtr = strstr (inStr, "TSTF_V2");
    if (NULL != devNameStartPtr) {
        deviceID = TSTF_V2;
    }
    devNameStartPtr = strstr (inStr, "TSTF_V1");
    if (NULL != devNameStartPtr) {
        deviceID = TSTF_V1;
    }

    devNameStartPtr = strstr (inStr, "IOV4_A");
    if (NULL != devNameStartPtr) {
        deviceID = IOV4_A;
    }

    devNameStartPtr = strstr (inStr, "TSTP_V1");
    if (NULL != devNameStartPtr) {
        deviceID = TSTP_V1;
    }
    devNameStartPtr = strstr (inStr, "TSTP_V2");
    if (NULL != devNameStartPtr) {
        deviceID = TSTP_V2;
    }
    return deviceID;
}

const char *dev_id_name (deciceId_t deviceID) {
    static const char *devName = "UNDEF_DEV";
    switch (deviceID) {
        case CAN_FLASHER:
            devName = "CAN_FLASHER";
            break;
        case TSTF_V1:
            devName = "TSTF_V1";
            break;
        case TSTF_V2:
            devName = "TSTF_V2";
            break;
        case TSTP_V1:
            devName = "TSTP_V1";
            break;
        case TSTP_V2:
            devName = "TSTP_V2";
            break;
        case TSTI_V1:
            devName = "TSTI_V1";
            break;
        case TSTS_V1:
            devName = "TSTS_V1";
            break;
        case IOV4_A:
            devName = "IOV4_A";
            break;

        default:
            devName = "CAN_FLASHER";
            break;
    }
    return devName;
}

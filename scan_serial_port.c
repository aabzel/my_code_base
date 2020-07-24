#include "scan_serial_port.h"

#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "convert.h"
#include "code_config.h"
#include "str_ops.h"
#include "tcp_client.h"
#include "utils.h"

xSerialConnection_t deviceList [MAX_COM_NUM];

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
    timeouts.ReadIntervalTimeout = 500; // in milliseconds
    timeouts.ReadTotalTimeoutConstant = 500; // in milliseconds
    timeouts.ReadTotalTimeoutMultiplier = 500; // in milliseconds
    timeouts.WriteTotalTimeoutConstant = 500; // in milliseconds
    timeouts.WriteTotalTimeoutMultiplier = 500; // in milliseconds
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
    bool out_res = false;
    char comNameStr [20] = "";
    uint8_t comPortNum;
    memset (deviceList, 0x00, sizeof(deviceList));
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
            out_res = true;
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
                        strncpy( deviceList [comPortNum].deviceName, parse_product_name (rxBuffer, realRxLen),sizeof(deviceList [comPortNum].deviceName));
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

    return out_res;
}

bool print_device_list (void) {
    bool out_res = false;
    bool res = false;
    system("cmd /c cls");
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("\nnow: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900,
			tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    //system("@cls||clear");
    //clrscr(); does not work
    printf("\n Compile Date %s %s ",__DATE__,__TIME__);
    printf("\n local  mac: ");
    print_mac_addr (workBenchParam.mac_addr);
    printf ("\nclient IP: %s \nServer IP: %s Server port: %u\n", workBenchParam.clientIPstr, workBenchParam.serverIPstr, workBenchParam.serverPort);
    uint16_t txTextLen;
    uint32_t comPortNum = 0;
    char txText [MAX_SIZE_OF_TCP_DATA_BYTE] = "";
    for (comPortNum = 0; comPortNum < MAX_COM_NUM; comPortNum++) {
        if (true == deviceList [comPortNum].isExistPort) {
            printf ("\n COM%u ", comPortNum);
        }
        if (true == deviceList [comPortNum].isExistDevice) {
            //printf ("Device exists. ");
            out_res = true;
        }
        if (true == deviceList [comPortNum].isExistDevice) {
            if (UNDEF_DEVICE != deviceList [comPortNum].deviceID) {
                printf ("Device [%s] Serial [0x%llx]", dev_id_name (deviceList [comPortNum].deviceID), (long long unsigned int) deviceList [comPortNum].serialNumber);
            }
            snprintf (
                txText,
                sizeof(txText),
                "\nDevice [%s] Serial 0x%llx from IP %s MAC %s user <%s>",
				deviceList [comPortNum].deviceName,
                (long long unsigned int) deviceList [comPortNum].serialNumber,
                workBenchParam.clientIPstr,
                mac_to_str (workBenchParam.mac_addr), workBenchParam.userName);
            txTextLen = strlen (txText);
            res = sent_to_tcp_server (txText, txTextLen, workBenchParam.serverPort, workBenchParam.serverIP);
            if (false == res) {
                //printf ("\nUnable to send to TCP server");
            }
        }
    }
    printf("\n");
    return out_res;
}

char* parse_product_name (char *inStr, uint16_t inStrLen) {
	static char devName[100] = "";
	int i ;
	for (i = 0; i < inStrLen; i++) {
		if (' ' != inStr[i]) {
			devName[i] = inStr[i];
		}
	}
	devName[i] ='\0';
	return devName;
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

#include "tcp_server.h"

// https://habr.com/ru/post/327574/
#if !defined(_WIN32) && !defined(__CYGWIN__)
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/select.h>
#include <sys/socket.h>
#else
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#include <stdio.h>
#include <time.h>

#include "code_config.h"
#include "convert.h"
#include "str_ops.h"
#include "tcp_client.h"
#include "win_utils.h"

#define MAX_AMOUNT_OF_DEVICES 1000U

ComputerServerParams_t serverPC = {0};

xConnection_t deviceList[MAX_AMOUNT_OF_DEVICES];

static bool print_dev_table (void) {
    uint16_t i = 0;
    bool res = false;
    clear_tui ();
    printf ("\nTCP server port: %u", serverPC.serverPort);
    printf ("\nTCP server IP: %s", serverPC.serverIPstr);
    time_t t = time (NULL);
    struct tm tm = *localtime (&t);
    printf ("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min,
            tm.tm_sec);
    printf ("\n");
    for (i = 0; i < MAX_AMOUNT_OF_DEVICES; i++) {
        if (true == deviceList[i].isbusy) {
            printf ("\n%s Serial [0x%016llx] holder MAC [%02X:%02X:%02X:%02X:%02X:%02X] IP %s name %s spot %s",
                    deviceList[i].deviceName, (long long unsigned int)deviceList[i].serialNumber,
                    deviceList[i].holderMac[0], deviceList[i].holderMac[1], deviceList[i].holderMac[2],
                    deviceList[i].holderMac[3], deviceList[i].holderMac[4], deviceList[i].holderMac[5],
                    ip_to_str ((uint8_t *)&deviceList[i].holderIp), deviceList[i].holderName,
                    deviceList[i].spotTimeStr);
            res = true;
        }
    }
    printf ("\n");
    if (false == res) {
        printf ("\n Nothing to print");
    }
    return res;
}

static bool save_device_in_log_file (char *fileName, xConnection_t inDev) {
    FILE *filePtr;
    bool res = false;
    filePtr = fopen (fileName, "a");
    if (NULL != filePtr) {
        fprintf (filePtr, "\n%s Serial [0x%016llx] holder MAC [%02X:%02X:%02X:%02X:%02X:%02X] IP %s name %s spot %s",
                 inDev.deviceName, (long long unsigned int)inDev.serialNumber, inDev.holderMac[0], inDev.holderMac[1],
                 inDev.holderMac[2], inDev.holderMac[3], inDev.holderMac[4], inDev.holderMac[5],
                 ip_to_str ((uint8_t *)&inDev.holderIp), inDev.holderName, inDev.spotTimeStr);

        fclose (filePtr);
        res = true;
    }
    return res;
}

static bool init_dev_list (void) {
    uint16_t i = 0;
    for (i = 0; i < MAX_AMOUNT_OF_DEVICES; i++) {
        deviceList[i].isbusy = false;
    }
    return true;
}

static bool is_device_exist_in_list (xConnection_t inDev) {
    bool res = false;
    uint16_t i = 0;
    for (i = 0; i < MAX_AMOUNT_OF_DEVICES; i++) {
        if (deviceList[i].serialNumber == inDev.serialNumber) {
            res = true;
            break;
        }
    }
    return res;
}

static bool insert_device_in_list (xConnection_t inDev) {
    bool res = false;
    uint16_t i;
    for (i = 0; i < MAX_AMOUNT_OF_DEVICES; i++) {
        if (false == deviceList[i].isbusy) {
            memcpy (&deviceList[i], &inDev, sizeof (inDev));
            deviceList[i].isbusy = true;
            res = true;
            break;
        }
    }
    return res;
}

static bool update_device_in_list (xConnection_t inDev) {
    bool res = false;
    uint16_t i;
    for (i = 0; i < MAX_AMOUNT_OF_DEVICES; i++) {
        if (deviceList[i].serialNumber == inDev.serialNumber) {
            memcpy (&deviceList[i], &inDev, sizeof (inDev));
            deviceList[i].isbusy = true;
            // memcpy (deviceList[i].holderMac,inDev.holderMac,6);
            // deviceList[i].holderIp = inDev.holderIp;
            // memcpy (deviceList[i].spotTimeStr,inDev.spotTimeStr,sizeof(inDev.spotTimeStr));
            // memcpy (deviceList[i].holderName,inDev.holderName,sizeof(inDev.holderName));
            // memcpy (deviceList[i].deviceName,inDev.deviceName,sizeof(inDev.deviceName));
            res = true;
            break;
        }
    }
    return res;
}

static bool update_dev_table (char *rxArray, uint16_t rxByteCnt) {
    bool res = false;
    if ((NULL != rxArray) && (1 < rxByteCnt)) {

        xConnection_t newDevice = {0};

        res = parse_ip (rxArray, rxByteCnt, &newDevice.holderIp);
        if (false == res) {
            return false;
        }
        res = parse_mac (rxArray, rxByteCnt, newDevice.holderMac);
        if (false == res) {
            return false;
        }

        res = parse_serial (rxArray, rxByteCnt, &newDevice.serialNumber);
        if (false == res) {
            return false;
        }

        res = parse_substr_name (rxArray, rxByteCnt, newDevice.deviceName, '[', ']');
        if (false == res) {
            return false;
        }

        res = parse_substr_name (rxArray, rxByteCnt, newDevice.holderName, '<', '>');
        if (false == res) {
            return false;
        }

        // newDevice.spotTimeStr,
        time_t t = time (NULL);
        struct tm tm = *localtime (&t);
        snprintf (newDevice.spotTimeStr, sizeof (newDevice.spotTimeStr), "%d-%02d-%02d %02d:%02d:%02d",
                  tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

        if (true == res) {
            res = is_device_exist_in_list (newDevice);
            if (true == res) {
                // update
                res = update_device_in_list (newDevice);
                if (false == res) {
                    printf ("\n unable to update device");
                }
            } else {
                // insert
                res = insert_device_in_list (newDevice);
                if (false == res) {
                    printf ("\n unable to insert device");
                }
                res = save_device_in_log_file ("log_devices.txt", newDevice);
                if (false == res) {
                    printf ("\n unable to insert device");
                }
            }
        }
    }
    return res;
}

bool launch_tcp_server (uint16_t tcpServerPort) {
    bool res = false;
    init_dev_list ();
    res = get_adapter_info ();
    if (false == res) {
        printf ("\nUnable to get adapter info..");
    }
    WSADATA wsa;
    SOCKET sockeDescriptor;
    struct sockaddr_in server;
    printf ("\n TCP server port %u", tcpServerPort);
    printf ("\nInitialising Winsock...");
    if (WSAStartup (MAKEWORD (2, 2), &wsa) != 0) {
        printf ("\nFailed. Error Code : %d", WSAGetLastError ());
        return false;
    } else {
        printf ("\nInitialised.");

        // Create a socket
        if ((sockeDescriptor = socket (AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
            printf ("\nCould not create socket : %d", WSAGetLastError ());
        } else {
            clear_tui ();
            printf ("Socket created.\n");
            time_t t = time (NULL);
            struct tm tm = *localtime (&t);
            printf ("\nnow: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
                    tm.tm_min, tm.tm_sec);
            printf ("\n");
            // Prepare the sockaddr_in structure
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = INADDR_ANY;
            server.sin_port = htons (tcpServerPort);

            // Bind
            if (bind (sockeDescriptor, (struct sockaddr *)&server, sizeof (server)) == SOCKET_ERROR) {
                printf ("\nBind failed with error code : [%d]", WSAGetLastError ());
            } else {
                puts ("Bind done");
                listen (sockeDescriptor, 3);
                print_dev_table ();
                puts ("\nWaiting for incoming connections...");
                SOCKET new_socket;
                int addrlen;
                struct sockaddr_in client;
                addrlen = sizeof (struct sockaddr_in);
                new_socket = accept (sockeDescriptor, (struct sockaddr *)&client, &addrlen);
                while (new_socket != INVALID_SOCKET) {
                    time_t t = time (NULL);
                    struct tm tm = *localtime (&t);
                    clear_tui ();
                    printf ("\nnow: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                            tm.tm_hour, tm.tm_min, tm.tm_sec);
                    printf ("\n");
#if DEBUG_RX_TCP_SERVER_CONNECTION
                    printf ("\nConnection accepted");
                    printf ("client connected %u.%u.%u.%u:%u\n", (unsigned char)client.sin_addr.S_un.S_un_b.s_b1,
                            (unsigned char)client.sin_addr.S_un.S_un_b.s_b2,
                            (unsigned char)client.sin_addr.S_un.S_un_b.s_b3,
                            (unsigned char)client.sin_addr.S_un.S_un_b.s_b4, ntohs (client.sin_port));
#endif
                    char rxArray[1000];
                    int rxByteCnt;
                    bool waitRxFlag = false;
                    time_t secondsStart;
                    secondsStart = time (NULL);
                    bool updRes = false;
                    rxByteCnt = recv (new_socket, rxArray, sizeof (rxArray), 0);
                    if (0 < rxByteCnt) {
                        updRes = update_dev_table (rxArray, rxByteCnt);
                        if (false == updRes) {
                            printf ("\n Unable to update dev table");
                        }
#if DEBUG_RX_TCP_SERVER_TEXT
                        printf ("\n %s", rxArray);
#endif
                    }
                    while (waitRxFlag) {
                        time_t curSeconds = time (NULL);
                        if (rxByteCnt < 0) {
                            waitRxFlag = false;
                        }
                        if (0.1 < (curSeconds - secondsStart)) {
                            waitRxFlag = false;
                        }
                    }
                    closesocket (new_socket);
                    listen (sockeDescriptor, 3);
                    if (true == updRes) {
                        print_dev_table ();
                    }
                    new_socket = accept (sockeDescriptor, (struct sockaddr *)&client, &addrlen);
                    res = true;
                }
            }
        }
    }
    closesocket (sockeDescriptor);
    return res;
}

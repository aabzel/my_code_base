#include "tcp_client.h"

#if !defined(_WIN32) && !defined(__CYGWIN__)
#   include <sys/socket.h>
#   include <netinet/in.h>
#   include <netinet/tcp.h>
#   include <sys/select.h>
#else
#   include <winsock2.h>
#   include <windows.h>
#   include <ws2tcpip.h>
#endif

#include <Iphlpapi.h>
#include <Assert.h>
#include <stdio.h>

#include "convert.h"
#include "str_ops.h"
#include "tcp_server.h"

ComputerParams_t workBenchParam;

bool sent_to_tcp_server (char *txText, uint16_t txTextLen, uint16_t tcpServerPort, uint32_t tcp_server_ip){
    char *ipAddrStr;
    ipAddrStr = ip_to_str ((uint8_t *)&tcp_server_ip);
    //printf ("\n server IP %s port %u",ipAddrStr,tcpServerPort);
    bool res = false;
    WSADATA wsa;
    SOCKET socDescriptor;
    //printf ("\nInitialising Winsock...");
    if (0 == WSAStartup (MAKEWORD (2, 2), &wsa)) {
#if DEBUG_TCP_CLIENT
        printf ("\nInitialised");
#endif
        res = true;
        socDescriptor = socket (AF_INET, SOCK_STREAM, 0);
        if (socDescriptor == INVALID_SOCKET) {
            printf ("Could not create socket : %d", WSAGetLastError ());
        } else {
#if DEBUG_TCP_CLIENT
            printf ("Socket created.\n");
#endif
            struct sockaddr_in server;
            //server.sin_addr.s_addr = inet_addr ("192.168.0.11");
            server.sin_addr.s_addr = inet_addr (ipAddrStr);
            //printf ("\nip paced %08x des %08x",server.sin_addr.s_addr, tcp_server_ip);
            server.sin_family = AF_INET;
            server.sin_port = htons (tcpServerPort);
            //Connect to remote server
            if (connect (socDescriptor, (struct sockaddr *) &server, sizeof(server)) < 0) {
                //printf ("\nTCP server connect error");
                res = false;
            } else {
#if DEBUG_TCP_CLIENT
                puts ("Connected");
#endif
                if (send (socDescriptor, txText, txTextLen, 0) < 0) {
                    printf ("\nSend failed");
                    res = false;
                } else {
#if DEBUG_TCP_CLIENT
                    printf ("\nData Send");
#endif
                    res = true;
                }
                closesocket(socDescriptor);
            }

        }

    } else {
        printf ("Failed. Error Code : %d", WSAGetLastError ());
        res = false;
    }

    return res;
}

bool get_adapter_info (void) {
    bool res = false;
    PIP_ADAPTER_INFO AdapterInfo;
    DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);
    char mac_addr[18] ;

    printf ("MAX_ADAPTER_ADDRESS_LENGTH: %u", (unsigned int) (MAX_ADAPTER_ADDRESS_LENGTH));
    printf ("sizeof IP_ADAPTER_INFO: %u", (unsigned int) sizeof(IP_ADAPTER_INFO));
    AdapterInfo = (IP_ADAPTER_INFO *) malloc (sizeof(IP_ADAPTER_INFO));
    if (AdapterInfo == NULL) {
        printf ("Error allocating memory needed to call GetAdaptersinfo\n");
        return NULL; // it is safe to call free(NULL)
    }

    // Make an initial call to GetAdaptersInfo to get the necessary size into the dwBufLen variable
    if (GetAdaptersInfo (AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW) {
        free (AdapterInfo);
        AdapterInfo = (IP_ADAPTER_INFO *) malloc (dwBufLen);
        if (AdapterInfo == NULL) {
            printf ("Error allocating memory needed to call GetAdaptersinfo\n");
            return NULL;
        }
    }
    uint16_t numOfAdapters = 0;
    printf ("\n");
    if (GetAdaptersInfo (AdapterInfo, &dwBufLen) == NO_ERROR) {
        // Contains pointer to current adapter info
        PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
        do {
            // technically should look at pAdapterInfo->AddressLength
            //   and not assume it is 6.
            uint32_t ipVal;
            res = try_strl2ipv4 (pAdapterInfo->IpAddressList.IpAddress.String, strlen (pAdapterInfo->IpAddressList.IpAddress.String), &ipVal);
            if (true == res) {
                if (0 < ipVal) {
                    workBenchParam.serverIP = ipVal;
                    serverPC.serverIP = ipVal;
                    sprintf (
                        mac_addr,
                        "%02X:%02X:%02X:%02X:%02X:%02X",
                        pAdapterInfo->Address [0],
                        pAdapterInfo->Address [1],
                        pAdapterInfo->Address [2],
                        pAdapterInfo->Address [3],
                        pAdapterInfo->Address [4],
                        pAdapterInfo->Address [5]);

                    printf ("Address %s, MAC %s\n", pAdapterInfo->IpAddressList.IpAddress.String, mac_addr);
                    memcpy(workBenchParam.mac_addr, pAdapterInfo->Address, 6);
                    memcpy(serverPC.mac_addr, pAdapterInfo->Address, 6);
                    strncpy (workBenchParam.clientIPstr, pAdapterInfo->IpAddressList.IpAddress.String, sizeof(workBenchParam.clientIPstr));
                    strncpy (serverPC.serverIPstr, pAdapterInfo->IpAddressList.IpAddress.String, sizeof(serverPC.serverIPstr));
                }
            }

            pAdapterInfo = pAdapterInfo->Next;
            numOfAdapters++;
        } while (pAdapterInfo);
    }
    printf ("\n numOfAdapters %u", numOfAdapters);

    free (AdapterInfo);
    return true;
}

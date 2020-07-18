#include "tcp_server.h"

//https://habr.com/ru/post/327574/
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
#include <time.h>

#include "convert.h"
#include "str_ops.h"

bool launch_tcp_server (uint16_t tcpServerPort) {
    bool res = false;
    WSADATA wsa;
    SOCKET sockeDescriptor;
    struct sockaddr_in server;
    printf ("\n TCP server port %u", tcpServerPort);
    printf ("\nInitialising Winsock...");
    if (WSAStartup (MAKEWORD (2, 2), &wsa) != 0) {
        printf ("Failed. Error Code : %d", WSAGetLastError ());
        return false;
    } else {
        printf ("\nInitialised.");

        //Create a socket
        if ((sockeDescriptor = socket (AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
            printf ("Could not create socket : %d", WSAGetLastError ());
        } else {

            printf ("Socket created.\n");

            //Prepare the sockaddr_in structure
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = INADDR_ANY;
            server.sin_port = htons (tcpServerPort);

            //Bind
            if (bind (sockeDescriptor, (struct sockaddr *) &server, sizeof(server)) == SOCKET_ERROR) {
                printf ("\nBind failed with error code : [%d]", WSAGetLastError ());
            } else {
                puts ("Bind done");

                listen (sockeDescriptor, 3);

                puts ("Waiting for incoming connections...");

                SOCKET new_socket;
                int addrlen;
                struct sockaddr_in client;
                addrlen = sizeof(struct sockaddr_in);
                new_socket = accept (sockeDescriptor, (struct sockaddr *) &client, &addrlen);
                while (new_socket != INVALID_SOCKET) {
                    puts ("\nConnection accepted");
                    printf (
                        "client connected %u.%u.%u.%u:%u\n",
                        (unsigned char) client.sin_addr.S_un.S_un_b.s_b1,
                        (unsigned char) client.sin_addr.S_un.S_un_b.s_b2,
                        (unsigned char) client.sin_addr.S_un.S_un_b.s_b3,
                        (unsigned char) client.sin_addr.S_un.S_un_b.s_b4,
                        ntohs (client.sin_port));
                    char rxArray [1000];
                    int rxByteCnt;
                    bool waitRxFlag = false;
                    time_t secondsStart;
                    secondsStart = time (NULL);
                    rxByteCnt = recv (new_socket, rxArray, sizeof(rxArray), 0);
                    if (0 < rxByteCnt) {
                        printf ("\n %s", rxArray);
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
                    new_socket = accept (sockeDescriptor, (struct sockaddr *) &client, &addrlen);
                    res = true;
                }
            }
        }
    }
    closesocket (sockeDescriptor);
    return res;
}


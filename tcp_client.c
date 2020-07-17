#include "tcp_client.h"

//#include <stdio.h>


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

//#include <stdio.h>

bool test_tcp_client (void) {
    bool res = false;
    WSADATA wsa;
    //SOCKET s;
    //printf ("\nInitialising Winsock...");
    if (WSAStartup (MAKEWORD (2, 2), &wsa) != 0) {
       // printf ("Failed. Error Code : %d", WSAGetLastError ());
        res = false;
    } else {
        res = true;
    }

   // printf ("Initialised.\n");
    return res;
}

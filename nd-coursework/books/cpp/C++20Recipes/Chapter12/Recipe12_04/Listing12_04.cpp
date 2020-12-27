// Copyright (c) 2020 J. Burton Browning and Bruce Sutherland. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing12_04.cpp
// Author: crdrisko
// Date: 10/12/2020-10:25:23
// Description: Wrapping Winsock

#include <iostream>

#ifdef _MSC_VER
    #pragma comment(lib, "Ws2_32.lib")

    #include <WS2tcpip.h>
    #include <WinSock2.h>å

    #define UsingWinsock 1

using ssize_t = SSIZE_T;

#else
    #define UsingWinSock 0
#endif

class WinsockWrapper
{
public:
    WinsockWrapper()
    {
#if UsingWinsock
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
            std::exit(1);
    #ifndef NDEBUG
        std::cout << "Winsock started!" << std::endl;
    #endif
#endif
    }

    ~WinsockWrapper()
    {
#if UsingWinsock
        WSACleanup();
    #ifndef NDEBUG
        std::cout << "Winsock shut down!" << std::endl;
    #endif
#endif
    }
};

int main()
{
    WinsockWrapper myWinsockWrapper;

    return 0;
}

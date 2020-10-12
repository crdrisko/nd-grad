// Copyright (c) 2020 J. Burton Browning and Bruce Sutherland. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing12_02.cpp
// Author: crdrisko
// Date: 10/12/2020-16:54:38
// Description: Opening a Berkeley Socket on Linux

#include <netdb.h>

#include <iostream>

#include <sys/socket.h>
#include <sys/types.h>

using SOCKET = int;

int main(int argc, const char* argv[])
{
    addrinfo hints {};
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    addrinfo* servinfo {};
    getaddrinfo("www.google.com", "80", &hints, &servinfo);

    SOCKET sockfd {socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)};

    int connectionResult {connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen)};

    if (connectionResult == -1)
        std::cout << "Connection failed!" << std::endl;
    else
        std::cout << "Connection successful!" << std::endl;

    freeaddrinfo(servinfo);

    return 0;
}

// Copyright (c) 2020 J. Burton Browning and Bruce Sutherland. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Listing12_05.cpp
// Author: crdrisko
// Date: 10/12/2020-12:55:52
// Description: Creating an object-oriented Socket class

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#if !UsingWinsock
    #include <netdb.h>
    #include <unistd.h>

    #include <sys/socket.h>
    #include <sys/types.h>
#endif

class Socket
{
private:
#if !UsingWinsock
    using SOCKET = int;
#endif

    addrinfo* m_ServerInfo {nullptr};
    SOCKET m_Socket {static_cast<SOCKET>(0xFFFFFFFF)};
    sockaddr_storage m_AcceptedSocketStorage {};
    socklen_t m_AcceptedSocketSize {sizeof(m_AcceptedSocketStorage)};

    void CreateSocket(std::string& webAddress, std::string& port, addrinfo& hints)
    {
        getaddrinfo(webAddress.c_str(), port.c_str(), &hints, &m_ServerInfo);

        m_Socket = socket(m_ServerInfo->ai_family, m_ServerInfo->ai_socktype, m_ServerInfo->ai_protocol);
    }

    Socket(int newSocket, sockaddr_storage&& socketStorage)
        : m_Socket {newSocket}, m_AcceptedSocketStorage {std::move(socketStorage)}
    {
    }

public:
    Socket(std::string& port)
    {
#ifndef NDEBUG
        std::stringstream portStream {port};
        int portValue {};
        portStream >> portValue;

        assert(portValue > 1024);   // Ports under 1024 are reserved for certain applications and protocols!
#endif

        addrinfo hints {};
        hints.ai_family   = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags    = AI_PASSIVE;

        std::string address {""};
        CreateSocket(address, port, hints);
    }

    Socket(std::string& webAddress, std::string& port)
    {
        addrinfo hints {};
        hints.ai_family   = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        CreateSocket(webAddress, port, hints);
    }

    Socket(std::string& webAddress, std::string& port, addrinfo& hints) { CreateSocket(webAddress, port, hints); }

    ~Socket() { Close(); }

    bool IsValid() { return m_Socket != -1; }

    // Used to establish a connection to a remote computer without receiving connections from other programs
    int Connect()
    {
        int connectionResult {connect(m_Socket, m_ServerInfo->ai_addr, m_ServerInfo->ai_addrlen)};

#ifndef NDEBUG
        if (connectionResult == -1)
            std::cout << "Connection failed!" << std::endl;
        else
            std::cout << "Connection successful!" << std::endl;
#endif

        return connectionResult;
    }

    // Used to receive incoming connections
    int Bind()
    {
        int bindResult {bind(m_Socket, m_ServerInfo->ai_addr, m_ServerInfo->ai_addrlen)};

#ifndef NDEBUG
        if (bindResult == -1)
            std::cout << "Bind failed!" << std::endl;
        else
            std::cout << "Bind successful!" << std::endl;
#endif

        return bindResult;
    }

    // Used to tell the socket to begin queuing connections from remote machines after a call to Bind()
    int Listen(int queueSize)
    {
        int listenResult {listen(m_Socket, queueSize)};

#ifndef NDEBUG
        if (listenResult == -1)
            std::cout << "Listen failed!" << std::endl;
        else
            std::cout << "Listen successful!" << std::endl;
#endif

        return listenResult;
    }

    // Used to pull connections from the queue created when Listen() is called
    Socket Accept()
    {
        SOCKET newSocket {accept(m_Socket, reinterpret_cast<sockaddr*>(&m_AcceptedSocketStorage), &m_AcceptedSocketSize)};

#ifndef NDEBUG
        if (newSocket == -1)
            std::cout << "Accept failed!" << std::endl;
        else
            std::cout << "Accept successful!" << std::endl;
#endif

        m_AcceptedSocketSize = sizeof(m_AcceptedSocketStorage);

        return Socket(newSocket, std::move(m_AcceptedSocketStorage));
    }

    // Used to shut down the Socket when it's no longer needed
    void Close()
    {
#ifdef _MSC_VER
        closesocket(m_Socket);
#else
        close(m_Socket);
#endif
        m_Socket = -1;
        freeaddrinfo(m_ServerInfo);
    }

    // Used to send data to the machine on the other end of the connection
    ssize_t Send(std::stringstream data)
    {
        std::string packetData {data.str()};
        ssize_t sendResult {send(m_Socket, packetData.c_str(), packetData.length(), 0)};

#ifndef NDEBUG
        if (sendResult == -1)
            std::cout << "Send failed!" << std::endl;
        else
            std::cout << "Send successful!" << std::endl;
#endif

        return sendResult;
    }

    // Used to bring data in from the remote connection
    std::stringstream Receive()
    {
        const int size {1024};
        char dataReceived[size];

        ssize_t receiveResult {recv(m_Socket, dataReceived, size, 0)};

#ifndef NDEBUG
        if (receiveResult == -1)
            std::cout << "Receive failed!" << std::endl;
        else if (receiveResult == 0)
        {
            std::cout << "Receive Detected Closed Connection!" << std::endl;
            Close();
        }
        else
        {
            dataReceived[receiveResult] = '\0';
            std::cout << "Receive successful!" << std::endl;
        }
#endif

        std::stringstream data {dataReceived};
        return std::move(data);
    }
};

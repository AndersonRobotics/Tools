#ifndef _RCOMM_SOCKET_H
#define _RCOMM_SOCKET_H

#if defined(__unix__) && defined(_WIN32)
#error _WIN32 and __unix__ macro defined under similar platform. Only one may be defined
#endif

//Make sure those users of anything else dont get to use this amazing library either
#if !defined(__unix__) && !defined(_WIN32)
#error The RoboComm library is intended for use with Unix and Windows platforms
#endif

#ifdef _WIN32

#include <winsock2.h>
#include <Ws2tcpip.h>

#endif

#ifdef __unix__

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#define SOCKET int

#endif

#include "threading.h"

typedef struct rcomm_socket_t{

    int sockfd;
    int port;
    int client;

    int read_size;

    sockaddr_in serv_addr;
    sockaddr_in cli_addr;
    rthread_t thread;

    void (*callback)(rcomm_socket_t socket);

};

rcomm_socket_t* rcomm_create_socket(int port, void (*func)(rcomm_socket_t* socket));

#endif
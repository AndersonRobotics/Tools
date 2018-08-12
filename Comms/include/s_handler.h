#ifndef _SOCKET_HANDLER_H
#define _SOCKET_HANDLER_H

//Make sure those little rascals defining __unix__ and _WIN32 together dont get away with it
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
#include "rcomm_socket.h"

////////////////////////////////////////////////////
//--Platform independent port definitions
//  Nobody has a perfect memory, so these definitions
//  help your memory by labelling which ports are used
//  for given functions <3
////////////////////////////////////////////////////

#define DEBUG_ERROR      0
#define DEBUG_WARNING    1
#define DEBUG_MESSAGE    2
#define JOYSTICKS        3
#define JOYSTICK_AXIS    4
#define JOYSTICK_BUTTONS 5

int rcomm_init(void);
int rcomm_quit(void);

int rcomm_shutdown(SOCKET socket);

#endif
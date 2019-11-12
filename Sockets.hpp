//
//  Sockets.hpp
//  AWUDProtocol
//
//  Created by Zihao Arthur Wang [STUDENT] on 8/21/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//

#ifndef Sockets_hpp
#define Sockets_hpp


#include <stdio.h>
#include <sys/socket.h>
#include "ServerTask.hpp"
#include "ClientTask.hpp"

#define SUCCEED             0
#define SOCKET_ERROR        1
#define BIND_ERROR          2
#define LISTEN_ERROR        3
#define ACCEPT_EROR         4
#define CONNECT_ERROR       4

int server(short port, ServerTask* task);

int server(short port, void* captured, void (*pf)(void* captured, int sockfd, struct sockaddr saddr, socklen_t socklen));

int client(const char *addr, short port, ClientTask* task);

int client(const char *addr, short port, void* captured, void (*pf)(void* captured, int sockfd));

#endif /* Sockets_hpp */

//
//  ServerTask.hpp
//  AWDroper
//
//  Created by Zihao Arthur Wang [STUDENT] on 11/12/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//


#ifndef SocketTask_hpp
#define SocketTask_hpp

#include <stdio.h>
extern "C" {
#include <sys/socket.h>
}
class ServerTask {
public:
    ServerTask* preTask = NULL;
    void* captured = NULL;
    void (*task)(void* captured, int sockfd, struct sockaddr saddr, socklen_t socklen) = NULL;
    ServerTask(void* captured,
               void (*task)(void* captured,
                            int sockfd,
                            struct sockaddr saddr,
                            socklen_t socklen));
    void executeServer(int sockfd, struct sockaddr saddr, socklen_t socklen);
};
#endif /* ServerTask_hpp */

//
//  ServerTask.cpp
//  AWDroper
//
//  Created by Zihao Arthur Wang [STUDENT] on 11/12/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//

#include "ServerTask.hpp"
extern "C" {
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
}
ServerTask::ServerTask(void* captured,
                       void (*task)(void* captured, int sockfd, struct sockaddr saddr, socklen_t socklen)){
    this->captured = captured;
    this->task = task;
}

void ServerTask::executeServer(int sockfd, struct sockaddr saddr, socklen_t socklen) {
    if (preTask != NULL) {
        preTask->executeServer(sockfd, saddr, socklen);
    }
    this->task(captured, sockfd, saddr, socklen);
}

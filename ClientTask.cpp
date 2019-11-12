//
//  ClientTask.cpp
//  AWDroper
//
//  Created by Zihao Arthur Wang [STUDENT] on 11/12/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//

#include "ClientTask.hpp"

extern "C" {
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
}
ClientTask::ClientTask(void* captured,
                       void (*task)(void* captured, int sockfd)){
    this->captured = captured;
    this->task = task;
}

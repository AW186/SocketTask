//
//  ClientTask.hpp
//  AWDroper
//
//  Created by Zihao Arthur Wang [STUDENT] on 11/12/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//

#ifndef ClientTask_hpp
#define ClientTask_hpp

#include <stdio.h>
class ClientTask {
public:
    ClientTask* preTask = NULL;
    void* captured = NULL;
    void (*task)(void* captured, int sockfd) = NULL;
    ClientTask(void* captured,
               void (*task)(void* captured, int sockfd));
    void executeClient(int sockfd);
};
#endif /* ClientTask_hpp */

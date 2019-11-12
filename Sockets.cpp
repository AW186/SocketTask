//
//  Sockets.cpp
//  AWUDProtocol
//
//  Created by Zihao Arthur Wang [STUDENT] on 8/21/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//

#include "Sockets.hpp"
extern "C" {
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
}
int server(short port, ServerTask* task) {
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return SOCKET_ERROR;
    }
    struct sockaddr_in socketaddr;
    socketaddr.sin_family = AF_INET;
    socketaddr.sin_addr.s_addr = INADDR_ANY;
    socketaddr.sin_port = htons(port);
    int err = bind(sockfd, (struct sockaddr*)&socketaddr, sizeof(socketaddr));
    if (err < 0) { perror("bind"); return BIND_ERROR; } //check
    err = listen(sockfd, 10);
    if (err < 0) { perror("listen"); return LISTEN_ERROR; } //check
    signal(SIGCHLD, [](int num) {
        int stat;
        waitpid(-1, &stat, WNOHANG);
    });
    while(true) {
        struct sockaddr addr;
        socklen_t size;
        int connectfd = accept(sockfd, &addr, &size);
        if (connectfd < 0) { perror("accept"); return ACCEPT_EROR; } //check
        pid_t pid;
        if((pid = fork()) == 0) {
            task->executeServer(sockfd, addr, size);
            close(connectfd);
            exit(0);
        }
        close(connectfd);
    }
    return 0;
}

int server(short port, void* captured, void (*pf)(void* captured, int sockfd, struct sockaddr saddr, socklen_t socklen)) {
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return SOCKET_ERROR;
    }
    struct sockaddr_in socketaddr;
    socketaddr.sin_family = AF_INET;
    socketaddr.sin_addr.s_addr = INADDR_ANY;
    socketaddr.sin_port = htons(port);
    int err = bind(sockfd, (struct sockaddr*)&socketaddr, sizeof(socketaddr));
    if (err < 0) { perror("bind"); return BIND_ERROR; } //check
    err = listen(sockfd, 10);
    if (err < 0) { perror("listen"); return LISTEN_ERROR; } //check
    signal(SIGCHLD, [](int num) {
        int stat;
        waitpid(-1, &stat, WNOHANG);
    });
    while(true) {
        struct sockaddr addr;
        socklen_t size;
        int connectfd = accept(sockfd, &addr, &size);
        if (connectfd < 0) { perror("accept"); return ACCEPT_EROR; } //check
        pid_t pid;
        if((pid = fork()) == 0) {
            pf(captured, connectfd, addr, size);
            close(connectfd);
            exit(0);
        }
        close(connectfd);
    }
    return 0;
}

int client(const char *addr, short port, void* captured, ClientTask* task) {
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return SOCKET_ERROR;
    }
    struct sockaddr_in socketaddr;
    socketaddr.sin_family = AF_INET;
    socketaddr.sin_addr.s_addr = inet_addr(addr);
    socketaddr.sin_port = htons(port);
    int err = connect(sockfd, (struct sockaddr*)&socketaddr, sizeof(socketaddr));
    if (err < 0) {
        perror("connect");
        return CONNECT_ERROR;
    }
    printf("connect succeed\n");
    task->executeClient(sockfd);
    close(sockfd);
    return 0;
}

int client(const char *addr, short port, void* captured, void (*pf)(void* captured, int sockfd)) {
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return SOCKET_ERROR;
    }
    struct sockaddr_in socketaddr;
    socketaddr.sin_family = AF_INET;
    socketaddr.sin_addr.s_addr = inet_addr(addr);
    socketaddr.sin_port = htons(port);
    int err = connect(sockfd, (struct sockaddr*)&socketaddr, sizeof(socketaddr));
    if (err < 0) {
        perror("connect");
        return CONNECT_ERROR;
    }
    printf("connect succeed\n");
    pf(captured, sockfd);
    close(sockfd);
    return 0;
}

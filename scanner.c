#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <fcntl.h>
#include "scanner.h"
#include "colors.h"

#define TIMEOUT 1

int check_ports(const char *ip, int port) {
    int sock;
    struct sockaddr_in server;
    fd_set write_fds;
    struct timeval timeout;
    int result;
    socklen_t len = sizeof(result);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf( BRIGHT_RED "[!]" RESET_COLOR " Failed to create socket\n");
        return 0;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(port);

    timeout.tv_sec = TIMEOUT;
    timeout.tv_usec = 0;

    fcntl(sock, F_SETFL, O_NONBLOCK);
    connect(sock, (struct sockaddr *)&server, sizeof(server));

    FD_ZERO(&write_fds);
    FD_SET(sock, &write_fds);
    int select_result = select(sock + 1, NULL, &write_fds, NULL, &timeout);

    if (select_result > 0 && FD_ISSET(sock, &write_fds)) {
        getsockopt(sock, SOL_SOCKET, SO_ERROR, &result, &len);
        if (result == 0) {
            close(sock);
            return 1;
        } 
        else {
            close(sock);
            return 0;
        }
    }

    close(sock);
    return 0;
}


void scan_ports(const char *ip, int start_port, int end_port){
    printf(BRIGHT_GREEN "[*]" RESET_COLOR "Scanning ports on %s \n\n", ip);

    for(int port = start_port; port <= end_port; port++){
        if(check_ports(ip, port)){
            printf("Open port: %d\n", port);
        }
    }
}

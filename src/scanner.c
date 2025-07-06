#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <fcntl.h>
#include "scanner.h"
#include "utils.h"
#include "colors.h"

#define TIMEOUT 1
#define MAX_RETRIES 3

int scan_ports(const char *ip, int start_port, int end_port, int is_long_scanning){
    struct sockaddr_in addr;
    int total_ports = end_port - start_port + 1;
    int batch_size = calculate_batch_size(total_ports);
    fd_set write_fds;
    struct timeval timeout;
    int result;
    socklen_t len = sizeof(result);

    for (int batch_start = start_port; batch_start <= end_port; batch_start += batch_size){
        int batch = min(batch_size, end_port - batch_start + 1);

        for (int i = 0; i < batch; i++){
            int port = batch_start + i;
            
            int attempt_num = 0;
            int total_attempts = 0;
            
            if (is_long_scanning){
                total_attempts = MAX_RETRIES;
            }

            while (attempt_num <= total_attempts){
                int sock = socket(AF_INET, SOCK_STREAM, 0);
                
                if (sock < 0){
                    attempt_num++;
                    continue;
                }
                
                addr.sin_family = AF_INET;
                addr.sin_addr.s_addr = inet_addr(ip);
                addr.sin_port = htons(port);
                
                fcntl(sock, F_SETFL, O_NONBLOCK);
                connect(sock, (struct sockaddr *)&addr, sizeof(addr));

                FD_ZERO(&write_fds);
                FD_SET(sock, &write_fds);

                timeout.tv_sec = TIMEOUT;
                timeout.tv_usec = 0;

                int select_result = select(sock + 1, NULL, &write_fds, NULL, &timeout);

                if (select_result > 0 && FD_ISSET(sock, &write_fds)){
                    getsockopt(sock, SOL_SOCKET, SO_ERROR, &result, &len);
                    if (result == 0){
                        printf(GREEN "Open port: " RESET_COLOR "%d\n", port);
                        close(sock);
                        break;
                    }
                }

                close(sock);
                attempt_num++;
            }
        }
    }

    return 0;
}


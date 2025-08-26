#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <fcntl.h>
#include <string.h>
#include "scanner.h"
#include "utils.h"          // min()
#include "top_1000_ports.h" // top_ports[1000]
#include "colors.h"
#include "global_vars.h"

#define TIMEOUT 1
#define MAX_RETRIES 3

port_list found_ports[65535] = {0};

int calculate_batch_size(int total_ports){
    if (total_ports <= 100) {
        return total_ports;
    }
    else if (total_ports <= 1000) {
        return min(total_ports / 4, 250);
    }
    else {
        return 500;
    }
}

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
                        printf(BRIGHT_GREEN "Open: " RESET_COLOR "%d\n", port);
                        close(sock);
                        
                        if (!found_ports[port-1].is_valid) {
                            found_ports[port-1].is_valid = 1;
                            found_ports[port-1].port_number = port;
                        }
                        break;
                    }
                    else if (is_single_port){
                        printf(BRIGHT_RED "Close: " RESET_COLOR "%d\n", port);
                        close(sock);
                    }
                }
                close(sock);
                attempt_num++;
            }
        }
    }
    return 0;
}

// if no '-p' or '--ports' options are specified, scan top 1000 ports from top_1000_ports.h
int scan_top_ports(const char *ip, int starting_index, int ending_index, int is_long_scanning){
    struct sockaddr_in addr;
    fd_set write_fds;
    struct timeval timeout;
    int result;
    socklen_t len = sizeof(result);

    for (int i = starting_index; i <= ending_index; i++){
        int port = top_ports[i];
        
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
                    printf(BRIGHT_GREEN "Open: " RESET_COLOR "%d\n", port);
                    close(sock);
                    if (!found_ports[port-1].is_valid) {
                        found_ports[port-1].is_valid = 1;
                        found_ports[port-1].port_number = port;
                    }
                    break;
                }
            }

            close(sock);
            attempt_num++;
        }
    }
    return 0;
}

int start_nmap_scan(const char *ip){
    char nmap_cmd[2048] = {0};
    char ports[512] = {0};
    
    int is_first_port = 1;
    for (int i = 0; i < 65535; i++){
        if(found_ports[i].is_valid){
            if (!is_first_port){
                strcat(ports, ",");
            }
            char ports_list[6];
            snprintf(ports_list, sizeof(ports_list), "%d", found_ports[i].port_number);
            strcat(ports,ports_list);
            is_first_port = 0;
        }
    }
    if(strlen(ports) == 0){
        printf(BRIGHT_RED "[!]" RESET_COLOR " NMAP. No open ports found to scan\n");
        return 1;
    }

    snprintf(nmap_cmd, sizeof(nmap_cmd), "nmap %s -p %s %s", ip, ports, nmap_flags );

    printf("\n" GREEN "[*]" RESET_COLOR " Running nmap:\n$ %s\n\n", nmap_cmd);
    system(nmap_cmd);

    return 0;
}

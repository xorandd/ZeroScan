#ifndef SCANNER_H
#define SCANNER_H

typedef struct {
    int is_valid;
    int port_number;
} port_list;

int scan_ports(const char *ip, int start_port, int end_port, int is_long_scanning);

int scan_top_ports(const char *ip, int is_long_scanning, int starting_index, int ending_index);

int start_nmap_scan(const char *ip);

#endif

#ifndef SCANNER_H
#define SCANNER_H

int scan_ports(const char *ip, int start_port, int end_port, int is_long_scanning);

int scan_top_ports(const char *ip, int is_long_scanning, int starting_index, int ending_index);

#endif

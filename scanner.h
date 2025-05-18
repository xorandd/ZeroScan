#ifndef SCANNER_H
#define SCANNER_H

int check_ports(const char *ip, int port);
void scan_ports(const char *ip, int start_port, int end_port);

#endif
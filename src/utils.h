#ifndef UTILS_H
#define UTILS_H

#define min(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})

int validate_ip(const char *ip);

int assign_values(int argc, char *argv[], char **ip, int *start_port, int *end_port, int *num_threads, int *is_long_scanning, int *is_ping, int *is_top_ports, int *is_nmap, int *nmap_flags_size);

int validate_values(char **ip, int *start_port, int *end_port, int *num_threads, int *is_top_ports);

int calculate_batch_size(int total_ports);

int get_linux_distro(char *return_name);
int check_nmap();
int install_nmap(char *distro_name);

int domain_to_ip(const char *domain, char *ipv4, size_t buffer_size);

#endif

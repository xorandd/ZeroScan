#ifndef THREADING_H
#define THREADING_H

typedef struct{
    const char *ip;
    int start_port;
    int end_port;
    int is_long_scanning;
}thread_args;

void *thread_call_scan_ports(void *arg);
void threads_for_scanning(const char *ip, int start_port, int end_port, int num_threads, int is_long_scanning);

#endif

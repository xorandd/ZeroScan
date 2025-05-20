#ifndef UTILS_H
#define UTILS_H

int validate_ip(const char *ip);
int assign_values(int argc, char *argv[], char **ip, int *start_port, int *end_port, int *num_threads);

#endif

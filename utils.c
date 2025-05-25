#include <stdio.h>
#include <regex.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "colors.h"

int validate_ip(const char *ip) {
    regex_t regex;
    int regRes;
    const char *pattern = "^((25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})\\.){3}(25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})$";

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        return 1;
    }

    regRes = regexec(&regex, ip, 0, NULL, 0);
    regfree(&regex);

    if (regRes == 0) {
        return 1; //valid ip
    } else {
        return 0; //invalid ip
    }
}

int assign_values(int argc, char *argv[], char **ip, int *start_port, int *end_port, int *retries, int *num_threads, int *is_long_scanning){
    for (int i = 1; i < argc; i++){
        if (validate_ip(argv[i])){
            *ip = argv[i];
        }
        else if (strcmp(argv[i], "-p") == 0 && i+1 < argc){
            *start_port = atoi(argv[++i]);
            if (i+1 < argc && argv[i+1][0] != '-'){
                *end_port = atoi(argv[++i]);
            }
            else{
                *end_port = *start_port;
            }
        }
        else if((strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--threads") == 0) && i+1 < argc){
            *num_threads = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "--retries") == 0 && i+1 < argc){
            *retries = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "--long") == 0){
            *is_long_scanning = 1;
        }
        else{
            printf( BRIGHT_RED "[-]" RESET_COLOR " Urecognized option: %s", argv[i]);
            return 1;
        }
    }
    return 0;
}

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

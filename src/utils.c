#include <stdio.h>
#include <regex.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "colors.h"
#include "messages.h" // program_usage()

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

int assign_values(int argc, char *argv[], char **ip, int *start_port, int *end_port, int *retries, int *num_threads, int *is_long_scanning, int *is_ping){
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
        else if (strcmp(argv[i], "--no-ping") == 0){
            *is_ping = 0;
        }
        else{
            printf( BRIGHT_RED "[-]" RESET_COLOR " Urecognized option: %s\n", argv[i]);
            return 1;
        }
    }
    return 0;
}
int validate_values(char **ip, int *start_port, int *end_port, int *retries, int *num_threads){
    if (! (*ip) || validate_ip(*ip) != 1){
        printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. Incorrect or missing IP format.\n");
        program_usage();
        return 1;
    }        

    if (*start_port == -1 || *end_port == -1){
        printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. Some arguments are missing\n");
        return 1;
    }

    if(*end_port < *start_port){
        printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. end port <= start port, enter valid values.\n");
        program_usage();
        return 1;
    }
    if(*start_port < 0 || *end_port > 65535){
	printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. Ports should be withing range of 0-65535\n");
        program_usage();
        return 1;
    }

    if (*num_threads <= 0){
        printf( BRIGHT_RED "[!]" RESET_COLOR "ERROR. Num of threads cant be 0 or less\n");
        return 1;
    }
    
    if (*retries <= 0){
        printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. --retries can't be negative");
        return 1;
    }
    return 0;
}

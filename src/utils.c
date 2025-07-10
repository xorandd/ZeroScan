#include <stdio.h>
#include <regex.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "colors.h"
#include "messages.h" // program_usage()
#include "global_vars.h"

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

int assign_values(int argc, char *argv[], char **ip, int *start_port, int *end_port, int *retries, int *num_threads, int *is_long_scanning, int *is_ping, int *is_top_ports, int *nmap_flags_size){
    int is_port_option = 0;

    for (int i = 1; i < argc; i++){
        if (validate_ip(argv[i])){
            *ip = argv[i];
        }
        else if (strcmp(argv[i], "-p") == 0 && i+1 < argc){
            char *range_str = argv[++i];
            if (strchr(range_str, '-')){
                sscanf(range_str, "%d-%d", start_port, end_port);
            }
            else{
                *start_port = atoi(range_str);
                *end_port = *start_port;
            }
            is_port_option = 1;
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
        else if (strcmp(argv[i], "--nmap") == 0){
            is_nmap = 1;
            
            for (int j = i + 1; j < argc; j++){
                if (strcmp(argv[j], "-p") == 0 || strcmp(argv[j], "-t") == 0 || strcmp(argv[j], "--threads") == 0 || 
                    strcmp(argv[j], "--retries") == 0 || strcmp(argv[j], "--long") == 0 ||
                    strcmp(argv[j], "--no-ping") == 0 || strcmp(argv[j], "--nmap") == 0) {    
                    break;
                }
                if (strcmp(argv[j], "-sS") == 0 || strcmp(argv[j], "-sC") == 0 || strcmp(argv[j], "-sV") == 0 || strcmp(argv[j], "-A") == 0 ||
                    strcmp(argv[j], "-T0") == 0 || strcmp(argv[j], "-T1") == 0 || strcmp(argv[j], "-T2") == 0 || 
                    strcmp(argv[j], "-T3") == 0 || strcmp(argv[j], "-T4") == 0 || strcmp(argv[j], "-T5") == 0){
                    strncat(nmap_flags, " ", *nmap_flags_size - strlen(nmap_flags) - 1);
                    strncat(nmap_flags, argv[j], *nmap_flags_size - strlen(nmap_flags) - 1);
                }
                i=j;
            }
        }
        else{
            printf( BRIGHT_RED "[-]" RESET_COLOR " Unrecognized option: %s\n", argv[i]);
            return 1;
        }
    }
    if (is_port_option == 0){
        *is_top_ports = 1;
    }
    return 0;
}
int validate_values(char **ip, int *start_port, int *end_port, int *retries, int *num_threads, int *is_top_ports){
    if (!(*ip) || validate_ip(*ip) != 1){
        printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. Incorrect or missing IP format.\n");
        program_usage();
        return 1;
    }        
    if (!(*is_top_ports)){
        if (*start_port == -1 || *end_port == -1){
            printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. Some arguments are missing\n");
            return 1;
        }
    
        if(*end_port < *start_port){
            printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. end port <= start port, enter valid values.\n");
            program_usage();
            return 1;
        }
        if(*start_port < 1 || *end_port > 65535){
	        printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. Ports should be within range of 1-65535\n");
            program_usage();
            return 1;
        }
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "messages.h"  // startup_banner(), program_usage() 
#include "colors.h"
#include "utils.h"     // validate_ip(), assign_values(), validate_values()
#include "threading.h" // threads_for_scanning(), threads_for_scanning_top_ports
#include "global_vars.h"
#include "scanner.h"   // start_nmap_scan()

int is_nmap = 0;
char nmap_flags[256] = {0};

int main(int argc, char* argv[]){

    startup_banner();

    if(argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)){
        program_usage();
        return 0;
    }
    if(argc < 2 || argc > 11){
        printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. Some arguments are missing \n");
        program_usage();
        return 1;
    }
    char *ip = NULL;
    int start_port = -1;
    int end_port = -1;
    int retries = 1;
    int num_threads = 200; //by default
    int is_long_scanning = 0;
    int is_ping = 1;
    int is_top_ports = 0;
    int nmap_flags_size = sizeof(nmap_flags);

    // ---- assigning ----
    if (assign_values(argc, argv, &ip, &start_port, &end_port, &retries, &num_threads, &is_long_scanning, 
                      &is_ping, &is_top_ports, &nmap_flags_size) == 1)
        return 1;
    
    // ---- validations ----
    if (validate_values(&ip,&start_port,&end_port,&num_threads,&retries, &is_top_ports) == 1)
        return 1;
    
     // ---- ping / scan ----
    if (is_ping == 1){
        char ping_cmd[256];
        snprintf(ping_cmd, sizeof(ping_cmd), "ping -c 1 %s > /dev/null 2>&1", ip);
        if (system(ping_cmd) != 0){
            printf( BRIGHT_RED "[!]" RESET_COLOR " Host is down\n");
            return 1;
        }
    }
    
    printf( BRIGHT_GREEN "\n[*]" RESET_COLOR " Scanning %s\n\n", ip);

    if (is_top_ports){
        while(retries > 0){
            threads_for_scanning_top_ports(ip, num_threads, is_long_scanning);    
            retries--;
        }
    }
    else {
        while(retries > 0){
            threads_for_scanning(ip, start_port, end_port, num_threads, is_long_scanning);    
            retries--;
        }
    }
    if (is_nmap){
        start_nmap_scan(ip);
    }
    return 0;
}

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

int is_single_port = 0;
char nmap_flags[256] = {0};

int main(int argc, char* argv[]){
    const char *version_number = "1.5.5";

    char *ip = NULL;            // -a --address option
    int start_port = -1;        // -p option
    int end_port = -1;          // -p option
    int num_threads = 200;      // By default, can be changed using -t --threads option
    int is_long_scanning = 0;   // --long
    int is_ping = 1;            // 1 means program will ping target before scanning, can be changed using --no-ping option
    int is_top_ports = 0;       // 0 means user used -p option 
    int is_nmap = 0;            // 0 -> user used --nmap <ARGS> option
    int nmap_flags_size = sizeof(nmap_flags);

    // print help menu if -h --help option used
    if(argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)){
        program_usage();
        return 0;
    }
    // print version if -v --version option used
    else if(argc == 2 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)){
        printf("ZeroScan %s\n", version_number);
        return 1;
    }

    if(argc < 3 || argc > 15){
        printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. Some arguments are missing/too much arguments given \n");
        return 1;
    }
    
    
    startup_banner();

    // ---- Check if nmap is installed ----
    if (check_nmap() == 1)
        return 1;

    // ---- Assigning ----
    if (assign_values(argc, argv, &ip, &start_port, &end_port, &num_threads, &is_long_scanning, 
                      &is_ping, &is_top_ports, &is_nmap, &nmap_flags_size) == 1)
        return 1;
    
    // ---- Validations ----
    if (validate_values(&ip,&start_port,&end_port,&num_threads, &is_top_ports) == 1)
        return 1;
    
    // check if single port entered
    is_single_port = (start_port == end_port);

    // ---- Ping target ----
    if (is_ping == 1){
        char ping_cmd[256];
        snprintf(ping_cmd, sizeof(ping_cmd), "ping -c 1 %s > /dev/null 2>&1", ip);
        if (system(ping_cmd) != 0){
            printf( BRIGHT_RED "[!]" RESET_COLOR " Host is down\n");
            return 1;
        }
    }
    
    // --- Scan target ----
    printf( GREEN "\n[*]" RESET_COLOR " Scanning %s\n\n", ip);

    // if no '-p' option eg 'zeroscan 10.10.10.10'
    if (is_top_ports)
        threads_for_scanning_top_ports(ip, num_threads, is_long_scanning);    
    // if port(-s) are specified
    else 
        threads_for_scanning(ip, start_port, end_port, num_threads, is_long_scanning);    
    
    // if --nmap option included, start nmap scan on found ports (scanner.c)
    if (is_nmap)
        start_nmap_scan(ip);
    
    // free ip after assigning it with strdup() in utils.c
    if (ip)
        free(ip);

    return 0;
}

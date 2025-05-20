#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "messages.h"
#include "colors.h"
#include "utils.h"
#include "threading.h"

int main(int argc, char* argv[]){

    startup_banner();

    if(argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)){
        program_usage();
        return 0;
    }

    if(argc < 4 || argc > 7){
        printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. Some arguments are missing / typo in flag\n");
        program_usage();
        return 1;
    }
    
    char *ip = NULL;
    int start_port = -1;
    int end_port = -1;
    int num_threads = 10; //by default
    
    // ---- ASSIGNING ----
    assign_values(argc, argv, &ip, &start_port, &end_port, &num_threads);
    
    // ---- VALIDATIONS ----
    if (!ip || validate_ip(ip) != 1){
        printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. Incorrect or missing IP format.\n");
        program_usage();
        return 1;
    }        

    if (start_port == -1 || end_port == -1){
        printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. Some arguments are missing\n");
        return 1;
    }

    if(end_port < start_port){
        printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. end port <= start port, enter valid values.\n");
        program_usage();
        return 1;
    }
    if(start_port < 0 || end_port > 65535){
	printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. Ports should be withing range of 0-65535\n");
        program_usage();
        return 1;
    }

    if (num_threads <= 0){
        printf( BRIGHT_RED "[!]" RESET_COLOR "ERROR. Num of threads cant be 0 or less\n");
        return 1;
    }
    
    
    // ---- PING / SCAN ----
    char ping_cmd[256];
    snprintf(ping_cmd, sizeof(ping_cmd), "ping -c 1 %s > /dev/null 2>&1", ip);
    if(system(ping_cmd) == 0){
        printf(BRIGHT_GREEN "[*]" RESET_COLOR "Scanning ports on %s \n\n", ip);
        threads_for_scanning(ip, start_port, end_port, num_threads);
    }
    else{
        printf( BRIGHT_RED "[!]" RESET_COLOR " Host is down\n");
    }

    return 0;
}

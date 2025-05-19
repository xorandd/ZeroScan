#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "messages.h"
#include "scanner.h"
#include "colors.h"
#include "utils.h"

int main(int argc, char* argv[]){

    startup_banner();

    if(argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)){
        program_usage();
        return 0;
    }

    if(argc != 4){
        printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. Some arguments are missing\n");
        program_usage();
        return 1;
    }

    char *ip = argv[1];
    int start_port = atoi(argv[2]);
    int end_port = atoi(argv[3]);

    if(validate_ip(ip) != 1){
        printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. Incorrect IP format. \n");
        program_usage();
        return 1;
    }
    
    if(end_port < start_port){
        printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. end port <= start port, enter valid values.\n");
        program_usage();
        return 1;
    }
    if(start_port < 0 || end_port > 65535){
        printf( BRIGHT_RED "[!]" RESET_COLOR " ERROR. port range: 0-65535\n");
        program_usage();
        return 1;
    }

    char ping_cmd[256];
    sprintf(ping_cmd, "ping -c 1 %s > /dev/null 2>&1", ip);
    if(system(ping_cmd) == 0){
        scan_ports(ip, start_port, end_port);
    }
    else{
        printf( BRIGHT_RED "[!]" RESET_COLOR " Host is down.\n");
    }

    return 0;
}

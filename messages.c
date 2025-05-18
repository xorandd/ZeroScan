#include <stdio.h>
#include "messages.h"
#include "colors.h"

void startup_banner(){
    printf(RED
           " _____               __                 \n"
           "/ _  / ___ _ __ ___ / _\\ ___ __ _ _ __  \n"
           "\\// / / _ \\ '__/ _ \\\\ \\ / __/ _` | '_ \\ \n"
           " / //\\  __/ | | (_) |\\ \\ (_| (_| | | | |\n"
           "/____/\\___|_|  \\___/\\__/\\___\\__,_|_| |_|\n" RESET_COLOR
LIGHT_GRAY "---------------------------------------------\n" RESET_COLOR
RED        "github" RESET_COLOR ": https://github.com/xorandd/ZeroScan\n"
LIGHT_GRAY "---------------------------------------------\n" RESET_COLOR
    );
}

void program_usage(){
    printf("[*] Usage example: ");
    printf(" <ip_address> <start_port> <end_port> \n");
    printf("\n");
    printf("Parameters:\n");
    printf("    <ip_address>  :  IP address\n");
    printf("    <start_port>  :  Starting port\n");
    printf("     <end_port>   :  Ending port\n");
    printf(BRIGHT_RED "[!]" RESET_COLOR " Ports should be withing range of 0-65535\n");
}
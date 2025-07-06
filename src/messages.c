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
    printf( GREEN "[*]" RESET_COLOR " Usage example:\n");
    printf("    zeroscan 127.0.0.1 -p 1 1000\n");
    printf("    zeroscan 127.0.0.1 -p 3306 --retries 2\n");
    printf("    zeroscan 127.0.0.1 -p 5000 --long --threads 200 --no-ping\n");

    printf("\n");
    
    printf( GREEN "[*]" RESET_COLOR " Options:\n");
    printf("    -p: port(s) to scan (single port or range (see example))\n");
    printf("    -t, --threads: number of concurrent threads, default value is 500.\n");
    printf("    --retries: number of times to scan\n");
    printf("    --long: retry failed scanned ports up to 3 times\n");
    printf("    --no-ping: doesn't ping target and tries to scan ports anyway, can be useful if ICMP is disabled (like with windows firewall by default)\n");
    printf("    -h, --help: show help menu\n");
}

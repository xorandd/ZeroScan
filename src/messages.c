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
    // 17 arguments MAX (apart of -v, -h)
    printf( GREEN "[*]" RESET_COLOR " Options:\n");
    printf("    -v, --version: show version number\n");
    printf("    -a, --address: target's ip address / hostname\n");
    printf("    -p: port(s) to scan (single port or range (see example))\n");
    printf("    -t, --threads: number of concurrent threads, default value is 500.\n");
    printf("    --long: scan target up to 3 times\n");
    printf("    --no-ping: doesn't ping target. Can be useful if ICMP is disabled (like with windows firewall by default)\n");
    printf("    --nmap: run nmap with optional flags\n");
    printf("    -h, --help: show help menu\n");

    printf("\n");

    printf(GREEN "[*]" RESET_COLOR " Optional Nmap Flags, --nmap [OPTIONS]:\n");
    printf("    -sS: TCP SYN\n");
    printf("    -sC: Run default scripts\n");
    printf("    -sV: Version detection\n");
    printf("    -A: Agressive scan. Enable OS detection, version detection, script scanning, and traceroute\n");
    printf("    -T<0-5>: 'Paranoid - 0', 'Sneaky - 1', 'Polite - 2', 'Normal - 3', 'Aggressive - 4', 'Insane - 5'\n");
}

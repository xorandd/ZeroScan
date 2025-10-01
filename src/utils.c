#include <stdio.h>
#include <regex.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "utils.h"
#include "colors.h"
#include "messages.h" // program_usage()
#include "global_vars.h"

int get_linux_distro(char *return_name){
    FILE *f = fopen("/etc/os-release", "r");
    if (!f){
        printf( BRIGHT_RED "[!]" RESET_COLOR "Couldn't open /etc/os-release");
        return 1;
    }

    char line[128];
    while(fgets(line, sizeof(line),f )){
        if(strncmp(line, "ID=", 3) == 0){
            char *distro_name = line + 3;
            distro_name[strcspn(distro_name, "\n")] = '\0';
            strcpy(return_name, distro_name);
            printf( BRIGHT_GREEN "[*]" RESET_COLOR " Detected %s\n", distro_name);
        }
    }
    return 0;
}

int install_nmap(char *distro_name){
    printf( BRIGHT_GREEN "[*]" RESET_COLOR " Installing nmap...\n\n");
    if (strcmp(distro_name, "arch") == 0 || strcmp(distro_name, "manjaro") == 0){
        system("sudo pacman -S nmap");
    }
    else if (strcmp(distro_name, "ubuntu") == 0 ||
             strcmp(distro_name, "debian") == 0 || 
             strcmp(distro_name, "linuxmint") == 0){
        system("sudo apt install nmap");
    }
    else if (strcmp(distro_name, "fedora") == 0){
        system("sudo dnf install nmap");
    }
    else{
        printf( BRIGHT_RED "[!]" RESET_COLOR " Unsupported linux distribution.\n");
        return 1;
    }
    return 0;
}

// checks if nmap is installed on system, if not - prompts user to do so
int check_nmap(){
    char cmd[32] = "which nmap > /dev/null 2>&1\n";
    
    char answer;
    if(system(cmd) != 0){
        printf( BRIGHT_RED "[!]" RESET_COLOR " Nmap is not detected, would you like to install it now? [Y/n] ");
        scanf(" %c", &answer);
        
        printf("\n");

        if (answer == 'n' || answer == 'N')
            return 0;
        else if (answer == 'y' || answer == 'Y'){
            char linux_distro[128];
            if (get_linux_distro(linux_distro) == 1){
                return 1;
            }
            if (install_nmap(linux_distro) == 1)
                return 1;
            return 0;
        }
        else{
            printf( BRIGHT_RED "[!]" RESET_COLOR " Unrecognized option.\n");
            return 1;
        }
    }
    return 0;
}

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
        return 0; //valid ip
    } else {
        return 1; //invalid ip
    }
}

int domain_to_ip(const char *domain, char *ipv4, size_t buffer_size){
    struct addrinfo hints, *res, *p;
    struct sockaddr_in *addr;
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(domain, NULL, &hints, &res)) != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    for (p = res; p != NULL; p = p->ai_next){
        addr = (struct sockaddr_in *) p->ai_addr;
        if (inet_ntop(AF_INET, &(addr->sin_addr), ipv4, buffer_size) != NULL){
            freeaddrinfo(res);
            return 0;
        }
    }
    freeaddrinfo(res);
    return 1;
}

int assign_values(int argc, char *argv[], char **ip, int *start_port, int *end_port, int *num_threads, int *is_long_scanning, int *is_ping, int *is_top_ports, int *nmap_flags_size){
    int is_port_option = 0;
    for (int i = 1; i < argc; i++){
        char ip_buffer[32];
        if ((strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--address") == 0) && i+1 < argc){    
            if (validate_ip(argv[++i]) == 0){
                *ip = strdup(argv[i]);
            }
            else if (domain_to_ip(argv[i], ip_buffer, sizeof(ip_buffer)) == 0){
                *ip = strdup(ip_buffer);
            }
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

int validate_values(char **ip, int *start_port, int *end_port, int *num_threads, int *is_top_ports){
    if (!(*ip) || validate_ip(*ip) != 0){
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
    return 0;
}

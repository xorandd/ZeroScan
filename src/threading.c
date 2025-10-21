#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "threading.h"
#include "scanner.h"   // scan_ports()

// ---- For ranged ports ----
void *thread_call_scan_ports(void *arg){
    //thread_args points to the passed values
    //casting pointer to the thread_args type
    thread_args *args = (thread_args*) arg; 
    scan_ports(args->ip, args->start_port, args->end_port, args->is_long_scanning);

    return NULL;
}

void threads_for_scanning(const char *ip, int start_port, int end_port, int num_threads, int is_long_scanning){
    int total_ports = (end_port - start_port) + 1;

    /*
    //to not create extra useless threads 
    if (num_threads > total_ports){
        num_threads = total_ports;
    }
    */

    int chunk = (total_ports + num_threads-1) / num_threads;

    pthread_t threads[num_threads];
    thread_args args[num_threads];
    for (int i = 0; i < num_threads; i++){
        args[i].ip = ip;
        args[i].start_port = start_port  + (i * chunk);
        args[i].end_port = args[i].start_port + chunk - 1;
        
        //if exceeded end_port value
        if(args[i].end_port > end_port)
            args[i].end_port = end_port;

        args[i].is_long_scanning = is_long_scanning;

        pthread_create(&threads[i], NULL, thread_call_scan_ports, (void*)&args[i]);
    }

    for (int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }
}

// ---- For top 1000 ports ----
void *thread_call_scan_top_ports(void *arg){
    thread_args_top_ports *args = (thread_args_top_ports*) arg; 
    scan_top_ports(args->ip, args->starting_index, args->ending_index, args->is_long_scanning);
    return NULL;
}

void threads_for_scanning_top_ports(const char *ip, int num_threads, int is_long_scanning){
    int total_ports = 1000;

    /*
    //to not create extra useless threads 
    if (num_threads > total_ports){
        num_threads = total_ports;
    }
    */

    int chunk = (total_ports + num_threads-1) / num_threads;

    pthread_t threads[num_threads];
    thread_args_top_ports args[num_threads];
    for (int i = 0; i < num_threads; i++){
        args[i].ip = ip;
        args[i].starting_index = i * chunk;
        args[i].ending_index = args[i].starting_index + chunk - 1;
        
        //if exceeded end_port value
        if(args[i].ending_index >= total_ports)
            args[i].ending_index = total_ports-1;

        args[i].is_long_scanning = is_long_scanning;

        pthread_create(&threads[i], NULL, thread_call_scan_top_ports, (void*)&args[i]);
    }

    for (int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }
}

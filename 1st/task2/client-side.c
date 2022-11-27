#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
//library for creating threads
#include <pthread.h>

#include <time.h>


// maximum concurrent connections
#define CONCURRENT_CONNECTION 100

// maximum connection requests queued
#define QUEUE_CONNECTION 100

#define NUM_THREADS 100



// connection handler function
void * func100(void *arg)
{
    int socket_desc;
    struct sockaddr_in server_addr;
    char message[1000];
    char buffer[1024];
    socklen_t addr_size;

    close(socket_desc);
    pthread_exit(NULL);
}

int main()
{

    int socket_desc;
    struct sockaddr_in server_addr;
    char message[1000];
    char buffer[1024];
    socklen_t addr_size;

    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_desc < 0){
        printf("Unable to create socket\n");
        sleep(2);
        _Exit(-1);
        return 0;
    }


    // Set port and IP the same as server-side:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero);

    // Send connection request to server:
    if(connect(socket_desc, (struct sockaddr * )&server_addr, sizeof(server_addr)) < 0){
        printf("Unable to connect\n");
        sleep(2);
        exit(0);
        return 0;
    }
    strcpy(message,"Hi");
    clock_t begin = clock();

    if( send(socket_desc, message , strlen(message) , 0) < 0)
    {
            printf("Send failed\n");
    }

    //Read the message from the server into the buffer
    if(recv(socket_desc, buffer, 1024, 0) < 0)
    {
       printf("Failed to communicate with the server \n");
       sleep(2);
       exit(0);
       return 0;
    }

    //Print the received message
    printf("Communication established: %s\n",buffer);
    // thread identifier
	pthread_t thread_id[NUM_THREADS];
	int i=0;

    //useful variables
    double time_sec;
    double timetaken;

    printf("Hello, My name is Samuel!\n");
    // creating 100 threads:
    for(i = 0; i < NUM_THREADS; i++)
    {

        clock_t started = clock();

        pthread_create(&thread_id[i], NULL, func100, NULL); //creating the threads

        clock_t ended = clock();

        timetaken = ended - started;
        time_sec = timetaken / CLOCKS_PER_SEC;

        printf("Thread %d %f\n", i+1, time_sec);
    }
    clock_t end = clock();

    double elapsed;
    double delayed;
    double milli;

    // calculate elapsed time by finding difference (end - begin) and
    elapsed += end - begin;


    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    delayed = elapsed / CLOCKS_PER_SEC;

    //converting to milliseconds
    milli = delayed * 1000;

    printf ("Elapsed time in seconds: %f\n", delayed);
    printf ("Elapsed time in milliseconds: %f\n", milli);
    return 0;
}



#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
//library for creating threads
#include <pthread.h>


// maximum concurrent connections
#define CONCURRENT_CONNECTION 100

// maximum connection requests queued
#define QUEUE_CONNECTION 100

#define NUM_THREADS 100


// connection handler function
void *func100(void *vargp){
    printf("created threads! \n");
}

int main(void)
{
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[2000], client_message[2000];

    // Clean buffers:
    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));

    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_desc < 0){
        printf("Unable to create socket\n");
        return -1;
    }

    printf("Socket created successfully\n");


    // Set port and IP the same as server-side:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Send connection request to server:
    if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Unable to connect\n");
        return -1;
    }
    printf("Hello, My name is Samuel!\n");

    // Send the message to server:
    if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
        printf("Unable to send message\n");
        return -1;
    }

    // thread identifier
	pthread_t thread_id[NUM_THREADS];
	long i;

    // creating 100 threads:
    for(i = 0; i < NUM_THREADS; i++)
        printf("creating thread...%d\n", i+1);

        pthread_create(&thread_id[i], NULL, func100, (void*)i); //creating the threads

    // Receive the server's response:
    if(recv(socket_desc, server_message, sizeof(server_message), 0) < 0){
        printf("Error while receiving server's msg\n");
        return -1;
    }

    printf("Server's response: %s\n",server_message);

    // Close the socket:
    close(socket_desc);

    return 0;
}



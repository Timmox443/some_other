#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
//include the time library
#include <time.h>

//library for creating threads
#include <pthread.h>

#define NUM_THREADS 100


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void count_one(int socket_desc)
{
    char client_message[2000];
    char buffer[1024];
    int new_socket = socket_desc;
    recv(new_socket, client_message , 2000 , 0);

    //responding to the client socket
    pthread_mutex_lock(&lock);
    char *message = malloc(sizeof(client_message)+20);
    strcpy(message,"Hello samuel... yES I copy : ");
    strcat(message,client_message);
    strcat(message,"\n");
    strcpy(buffer,message);
    free(message);
    pthread_mutex_unlock(&lock);
    send(new_socket,buffer,100,0);
    printf("Exit socketThread \n");
    close(new_socket);

}

void operation_one(int socket_desc)
{

    int i;
    int total = 0;
    for(i = 0;i < 9000000; i++)
        total = total + i;
    printf("total: %d\n", total);



}








int main(void)
{
    int new_socket, serverSocket, client_size, client_sock;
    struct sockaddr_in server_addr, client_addr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    pid_t pid[100];



    // Clean buffers:
    //memset(server_message, '\0', sizeof(server_message));

    // Create socket:
    new_socket = socket(PF_INET, SOCK_STREAM, 0);

    if(new_socket < 0){
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    // Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind to the set port and IP:
    if(bind(new_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
        printf("Couldn't bind to the port\n");
        return -1;
    }
    printf("Done with binding\n");

    // Listen for clients:
    if(listen(new_socket, 100) < 0){
        printf("Error while listening\n");
        return -1;
    }
    printf("\nListening for incoming connections.....\n");

    pthread_t thread_id[NUM_THREADS];
	int i=0;

	while(1)
	{


        // Accept an incoming connection:
        client_size = sizeof(client_addr);
        client_sock = accept(new_socket, (struct sockaddr*)&client_addr, &client_size);

        if (client_sock < 0){
            printf("Can't accept\n");
            return -1;
        }

        clock_t begin = clock();
        printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        int pid_c = 0;

        if ((pid_c = fork())==0)
        {
            count_one(client_sock);
            operation_one(client_sock);
        }
        else
        {
              pid[i++] = pid_c;
              if( i >= 99)
               {
                 i = 0;
                 while(i < 100)
                    waitpid(pid[i++], NULL, 0);
                 i = 0;
        }




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

    //Closing the socket:
    close(client_sock);
    close(new_socket);

    return 0;
    }
}



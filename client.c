#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h> // for close

//for sendfile()
#include<sys/sendfile.h>

//for getting file size using stat()
#include<sys/stat.h>

#define SIZE 256

int main(int argc, char * argv[])
{
    if(argc < 6){
        printf("[ERR] Missing arguments.\n");
        exit(-2);
    }

    // Collect user arguments
    char * server_ip = argv[1];
    char * file_path = argv[3];
    int to_format = atoi(argv[4]);
    char * to_name = argv[5];

    // Create a socket
    int client_socket;
    
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket == -1){
        printf("[ERR] Socket creation failed!\n");
        exit(-1);
    }

    // Specify an address and port for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(atoi(argv[2]));
    server_address.sin_addr.s_addr = INADDR_ANY;

    printf("[STAT] Connecting to server at address %s...\n", server_ip);

    // Connect client socket to server with specified address
    int conn_status = connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    if(conn_status == -1){
        printf("[ERR] socket connection failed!\n");
        exit(-1);
    }

    printf("[STAT] Connected!\n");


    char client_msg[256];

    FILE * input_file = fopen(file_path, "r");

    fread(client_msg, 256, 1, input_file);

    //Receive data from server
    //char buff[1024];
    //recv(client_socket, &buff, sizeof(buff), 0);

    //printf("Data Rx: %s\n", buff);

    //char msg[256] = "Hey I am a Client!\n";

    if (send(client_socket, client_msg, sizeof(client_msg), 0) < 0){
        printf("[ERR] Error sending message to server at address %s", server_ip);
        exit(1);
    }
    

    // Close the connection socket
    close(client_socket);

    return 0;

}
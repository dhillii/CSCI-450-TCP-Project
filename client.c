#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    // Create a socket
    int client_socket;
    
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket == -1){
        printf("ERROR: Socket creation failed!\n");
        exit(-1);
    }

    // Specify an address for the socket

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int conn_status = connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    if(conn_status == -1){
        printf("ERROR: socket connection failed!\n");
        exit(-1);
    }

    char buff[1024];
    recv(client_socket, &buff, sizeof(buff), 0);

    printf("Data Rx: %s\n", buff);

    close(client_socket);

    return 0;

}
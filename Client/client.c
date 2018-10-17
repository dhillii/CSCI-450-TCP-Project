#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <fcntl.h>
#include <unistd.h> // for close


//for getting file size using stat()
#include<sys/stat.h>

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

    printf("[OK] Connecting to server at address %s...\n", server_ip);

    // Connect client socket to server with specified address
    int conn_status = connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    if(conn_status == -1){
        printf("[ERR] socket connection failed!\n");
        exit(-1);
    }

    printf("[OK] Connected!\n");

    char file_data[4096];
    char send_byte[1];
    char ch;

    //Attempt to open file
    FILE * file_to_send = fopen(file_path,"r");

    if(!file_to_send) {
        printf("[ERR] Could not open file!");
        close(client_socket);
        exit(-1);
    } 
    
    long file_size;
    fseek (file_to_send, 0, SEEK_END);     
    file_size =ftell (file_to_send);
    rewind(file_to_send);
 
    sprintf(file_data,"FBEGIN:%s:%d:%d\r\n", to_name, file_size, to_format);      //Create header message with target name
                                                                    // and file size

    send(client_socket, file_data, sizeof(file_data), 0);           //Send file data
 

    //Send file data one byte at a time until end of file
    while((ch=getc(file_to_send))!=EOF){
        send_byte[0] = ch;
        send(client_socket, send_byte, 1, 0);    
    }
    fclose(file_to_send);

    printf("[OK] Data was sent successfully!\n");


    
    

    // Close the connection socket
    close(client_socket);

    return 0;

}
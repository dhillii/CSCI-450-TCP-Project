

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char * argv[])
{

   char server_msg[256] = "You have reached the server!\n";

   int server_socket;
   server_socket = socket(AF_INET, SOCK_STREAM, 0);
   if(server_socket == -1){
       printf("ERROR: Socket creation failed!\n");
       exit(-1);
   }

   if(argc <= 1){
    printf("ERROR: No listener port specified.\n");
    exit(-1);
   }

   struct sockaddr_in server_address;
   server_address.sin_family = AF_INET;
   server_address.sin_port = htons(atoi(argv[1]));
   server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*) &server_address,sizeof(server_address));

    listen(server_socket, 5);

    int client_socket;

    client_socket = accept(server_socket, NULL, NULL);

    send(client_socket, server_msg, sizeof(server_msg), 0);

    close(server_socket);

	return 0;
}



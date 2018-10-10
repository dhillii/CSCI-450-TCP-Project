

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <fcntl.h>
#include <unistd.h> // for close


int main(int argc, char * argv[]){

char server_msg[256] = "You have reached the server!\n";

// Create server socket
printf("[OK] Creating Server Socket...\n");
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

// Specify address and port for the socket
struct sockaddr_in server_address;
server_address.sin_family = AF_INET;
server_address.sin_port = htons(atoi(argv[1]));
server_address.sin_addr.s_addr = INADDR_ANY;

// Bind the server to address 
printf("[OK] Binding...\n");
bind(server_socket, (struct sockaddr*) &server_address,sizeof(server_address));


// Start listener on the socket to listen for connections
printf("[OK] Starting Listener...\n");
listen(server_socket, 5);

// Accept client connection 

 // Bind the server to address 
bind(server_socket, (struct sockaddr*) &server_address,sizeof(server_address));

// Start listener on the socket to listen for connections
listen(server_socket, 5);

// Accept client connection 

while(1){

  int client_socket;
  client_socket = accept(server_socket, NULL, NULL);

  // Send data to the client
  //send(client_socket, server_msg, sizeof(server_msg), 0);

  char to_name[50];
  recv(client_socket, &to_name, sizeof(to_name), 0);

  printf("Data Rx: %s\n", to_name);



  char buff[256];

  recv(client_socket, &buff, sizeof(buff), 0);

  printf("Data Rx: %s\n", buff);

  //close the connection
  close(client_socket);
}


return 0;
}


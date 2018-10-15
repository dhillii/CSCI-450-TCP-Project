#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <fcntl.h>
#include <unistd.h> // for close

void translateUnits(char * file_name, int option);

void translate_0_1(char data[]);

void translate_1_0(char data[]);


int parseArguments(char **args, char *line){
  int tmp=0;
  args[tmp] = strtok( line, ":" );
  while ( (args[++tmp] = strtok(NULL, ":" ) ) != NULL );
  return tmp - 1;
}


int main(int argc, char * argv[])
{


  char *header[4096];
  char recv_buff[4096];
  char *file_name;
  char *file_size;
  FILE * recv_file;
  int received = 0;
  char tempstr[4096];

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

  while(1){

    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    if( recv(client_socket, recv_buff, sizeof(recv_buff), 0) )
    {
      //If first 6 characters are not "FBEGIN parse arguments to get file name and size"
      if(!strncmp(recv_buff,"FBEGIN",6)) {
        recv_buff[strlen(recv_buff) - 2] = 0;
        parseArguments(header, recv_buff);
        file_name = header[1];
        file_size = header[2];
        }
      recv_buff[0] = 0;
      recv_file = fopen ( file_name,"w" );

      while(1){

        if(recv(client_socket, recv_buff, 1, 0) != 0){

          fwrite(recv_buff, sizeof(recv_buff[0]), 1, recv_file);
          recv_buff[0] = 0;
        }
        else {
          printf("[OK] File data received from client successfully!\n");
          fclose(recv_file);
          close(client_socket);
          break;
        }
      }
    } 
  }

  return 0;

}






void translateUnits(char * file_name, int option){

  FILE * out_file = fopen(file_name, "r+");

  if(out_file == NULL){
        printf("[ERR] Could not create file.\n");
        exit(-1);
  }

  switch(option){

    case 0: 
      printf("[SUCCESS] Saving file as %s\n", file_name);
      break;

    case 1:
      break;

    case 2:
      break;

    case 3:
      break;

    default:
      printf("[ERR] Invalid translation parameter.\n");
      exit(-1);

  }
}
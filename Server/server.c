#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <ctype.h>

#include <fcntl.h>
#include <unistd.h> // for close

void translateUnits(char * file_name, int option, int client_socket, int file_size);

void translate_0_1(unsigned char * buffer, int amount_bytes ,FILE * outfile);

void translate_1_0(unsigned char * buffer, int amount_bytes ,FILE * outfile);

int parseArguments(char **args, char *line);

int numDigits(int num);

int main(int argc, char * argv[])
{
  char * header[4096];
  char recv_buff[4096];
  char file_name[256];
  char file_size[256];
  char to_format[256];

  int to_format_num;
  int file_size_num;

  FILE * recv_file;

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

    if( recv(client_socket, recv_buff, sizeof(recv_buff), 0) != 0)
    {
      //If first 6 characters are not "FBEGIN parse arguments to get file name and size from header."
      if(!strncmp(recv_buff,"FBEGIN",6)) {
        recv_buff[strlen(recv_buff) - 2] = 0;
        parseArguments(header, recv_buff);
        strcpy(file_name, header[1]);
        strcpy(file_size, header[2]);
        strcpy(to_format, header[3]);
        file_size_num = atoi(file_size);
        to_format_num = atoi(to_format);
        }
      recv_buff[0] = 0;
      recv_file = fopen ( file_name,"w" );

      while(1){
        //This works and will not block the server because if recv isn't 0 it will read a byte and then write to a file
        //recv will be 0 when no data is available to be received from the client. Thus it will close the file and the connection
        //to the client. Hence, we do not need to know the file size for reading.
        if(recv(client_socket, recv_buff, 1, 0) != 0){

          fwrite(recv_buff, sizeof(recv_buff[0]), 1, recv_file);
          recv_buff[0] = 0;
        }
        else {
          printf("[OK] File data received from client successfully!\n");
          fclose(recv_file);
          break;
        }
      } 
    }

    translateUnits(file_name, to_format_num, client_socket, file_size_num);

    close(client_socket);
  }

  
  return 0;

}


void translateUnits(char * file_name, int option, int client_socket, int file_size){

  FILE * in_file = fopen(file_name, "r");
  FILE * out_file = fopen("translated.bin","wb");

  unsigned char file_data[file_size];

  fread(file_data,file_size,1,in_file);

  char stat_message[256];

  if(in_file == NULL){
        printf("[ERR] Could not open %s.\n", file_name);
        exit(-1);
  }

  switch(option) {
      case 0 :
        sprintf(stat_message, "[SUCCESS] File saved as %s and no units translated.\n", file_name);
        if (send(client_socket, stat_message, 256, 0) <= 0){
          printf("[ERR] Error sending message! \n");
          exit(-1);
        }
        printf("[OK] Status Message Sent !\n");
        break;

      case 1 :
        translate_0_1(file_data, file_size, out_file);
        sprintf(stat_message, "[SUCCESS] File saved as %s and type 0 units translated.\n", file_name);
        if (send(client_socket,stat_message, 256, 0) <= 0){
          printf("[ERR] Error sending message! \n");
          exit(-1);
        }
        printf("[OK] Status Message Sent!\n" );
        break;

      case 2 :
        //translate_1_0(in_file);
        sprintf(stat_message, "[SUCCESS] File saved as %s and type 1 units translated.\n", file_name);
        if (send(client_socket,stat_message, 256, 0) <= 0){
          printf("[ERR] Error sending message! \n");
          exit(-1);
        }
        printf("Status Message Sent!\n" );
        break;

      case 3 :
        //translate_0_1(in_file);
        //translate_1_0(in_file);
        sprintf(stat_message, "[SUCCESS] File saved as %s and type 1 and 2 units translated.\n", file_name);
        if (send(client_socket,stat_message, 256, 0) <= 0){
          printf("[ERR] Error sending message! \n");
          exit(-1);
        }
        printf("Status Message Sent!\n" );
        break;
      default :
         printf("[ERR] to_format paramater invalid!\n" );
   }

}


//This function parses arguments sent by the client.
int parseArguments(char **args, char *line){
  int tmp=0;
  args[tmp] = strtok( line, ":" );
  while ( (args[++tmp] = strtok(NULL, ":" ) ) != NULL );
  return tmp - 1;
}

void translate_0_1(unsigned char * buffer, int amount_bytes ,FILE * outfile){

    for(int i = 0; i<amount_bytes; i++){

        if(buffer[i] == 0){

            unsigned char type = (unsigned char)1;
            fwrite(&type, 1, 1, outfile);
            i+=1;

            unsigned int amount_int = (int)buffer[i];
            char amount_arr[3];

            int digits = numDigits(amount_int);

            if(digits == 1){
                amount_arr[0] = '0';
                amount_arr[1] = '0';
                amount_arr[2] = (char)amount_int;
                fwrite(amount_arr, 3, 1, outfile);
            }
            else if(digits == 2){
                amount_arr[0] = '0';
                char amount_str[2];
                fwrite(amount_arr, 1, 1, outfile);
                sprintf(amount_str, "%d", amount_int);
                fwrite(amount_str, 2, 1, outfile);      
            }
            else{
                char amount_str[3];
                sprintf(amount_str, "%d", amount_int);
                fwrite(amount_str, 3, 1, outfile);
            }

            unsigned int units[amount_int];
            unsigned char comma = (unsigned char)',';

            for(int j = 0; j < amount_int; j++){
                units[j] = buffer[i+2] | (buffer[i+1] << 8) ;                  
                i+=2;
            }

            fwrite(units, sizeof(units), 1, outfile);

            printf("Amount: %d\n", amount_int);
            printf("Units Written: %u %u %u\n\n", units[0], units[1], units[2]);
        }
    }

}

void translate_1_0(unsigned char * buffer, int amount_bytes ,FILE * outfile){

}




int numDigits(int num){
    int count = 0;
    int Number = num;
    while(Number != 0)
    {
        count++;
        Number /= 10;
    }
    return count;
}

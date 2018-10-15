# TCP Programming Project



## Getting Started



### Prerequisites

To run this project it is suggested that you compile and run on a Linux based operating system.


The GCC compiler must also be installed as a prerequisite.

```
$ sudo apt-get update
$ sudo apt-get upgrade
$ sudo apt-get install build-essential
```

### Compiling

To compile this project open up your linux terminal and change your directory to the project directory.

```
$ cd /path/to/project/CSCI-450-TCP-Project
```

Run the make script to compile both the server and client code.

```
$ make
```

## Running

To run the client application:

```
$ ./tcpclient.out <server_IP> <server_port> <file_path> <to_format> <to_name>
```

To run the server application:

```
$ ./tcpserver <listen_port>
```

## Test Cases

[X] The file given in the command to run client does not exist
* The file given in the command to run client is empty
* The format given in the command to run client is out of range
* The file from client has only type 0 units and the "to format" is 0.
* The file from client has only type 0 units and the "to format" is 1.
* The file from client has only type 0 units and the "to format" is 2.
* The file from client has only type 0 units and the "to format" is 3.
* The file from client has only type 1 units and the "to format" is 0.
* The file from client has only type 1 units and the "to format" is 1.
* The file from client has only type 1 units and the "to format" is 2.
* The file from client has only type 1 units and the "to format" is 3.
* The file from client has both type 0 and type 1 units and the "to format" is 0.
* The file from client has both type 0 and type 1 units and the "to format" is 1.
* The file from client has both type 0 and type 1 units and the "to format" is 2.
* The file from client has both type 0 and type 1 units and the "to format" is 3.
* The file from client has only type 0 units but have errors
* The file from client has only type 1 units but have errors
* The file from client has both type 0 and type 1 units and have errors in type 0 units
only
* The file from client has both type 0 and type 1 units and have errors in type 1 units
only
-[x] Two clients send files to the server one by one
-[x] Ten clients send files to the server one by one



## Authors

* **David Hill, Jr.** 

## Refrences

Base code refrence:

http://armi.in/wiki/FTP_Server_and_Client_Implementation_in_C/C%2B%2B

https://www.cs.utah.edu/~swalton/listings/sockets/programs/part2/chap6/simple-server.c



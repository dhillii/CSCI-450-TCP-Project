# TCP Programming Project



## Getting Started



### Prerequisites

To run this project it is suggested that you compile and run on a Linux based operating system.

The latest version of Debian 9.9.5 was used to build and run this project.

The GCC compiler must also be installed as a prerequisite.

Follow the steps below on a clean linux install to get the gcc compiler.

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

Run the make command in the terminal to compile both the server and client code.

```
$ make
```

## Running

To run the client application:

Open a terminal and run the following commands.

```
$ cd Client
$ ./tcpclient.out <server_IP> <server_port> <file_path> <to_format> <to_name>
```

To run the server application:

Open another terminal and run the following commands.

```
$ cd Server
$ ./tcpserver <listen_port>
```

Note: Make sure the <listen_port> and <server_port> parameters have the same port number. The server IP should be localhost "127.0.0.1" if you are running on a local machine.

## Test Cases

- [x] The file given in the command to run client does not exist
- [ ] The file given in the command to run client is empty
- [ ] The format given in the command to run client is out of range
- [ ] The file from client has only type 0 units and the "to format" is 0.
- [ ] The file from client has only type 0 units and the "to format" is 1.
- [ ] The file from client has only type 0 units and the "to format" is 2.
- [ ] The file from client has only type 0 units and the "to format" is 3.
- [ ] The file from client has only type 1 units and the "to format" is 0.
- [ ] The file from client has only type 1 units and the "to format" is 1.
- [ ] The file from client has only type 1 units and the "to format" is 2.
- [ ] The file from client has only type 1 units and the "to format" is 3.
- [ ] The file from client has both type 0 and type 1 units and the "to format" is 0.
- [ ] The file from client has both type 0 and type 1 units and the "to format" is 1.
- [ ] The file from client has both type 0 and type 1 units and the "to format" is 2.
- [ ] The file from client has both type 0 and type 1 units and the "to format" is 3.
- [ ] The file from client has only type 0 units but have errors
- [ ] The file from client has only type 1 units but have errors
- [ ] The file from client has both type 0 and type 1 units and have errors in type 0 units
only
- [ ] The file from client has both type 0 and type 1 units and have errors in type 1 units
only
- [x] Two clients send files to the server one by one
- [x] Ten clients send files to the server one by one



## Authors

* **David Hill, Jr.** 

## Refrences

Refrences:

http://armi.in/wiki/FTP_Server_and_Client_Implementation_in_C/C%2B%2B

https://www.cs.utah.edu/~swalton/listings/sockets/programs/part2/chap6/simple-server.c

ftp://gaia.cs.umass.edu/pub/kurose/ftpserver.c



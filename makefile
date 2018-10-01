tcpprojectmake: server.c client.c
	gcc -pthread -o tcpserver.out server.c
	gcc -o tcpclient.out client.c

.PHONY: runserver
.PHONY: runclient




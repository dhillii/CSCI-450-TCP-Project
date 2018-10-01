tcpprojectmake: server.c client.c
	gcc -pthread -o tcpserver server.c
	gcc -o tcpclient client.c

.PHONY: runserver
.PHONY: runclient

runserver: tcpserver
	./tcpserver

runclient:
	./tcpclient


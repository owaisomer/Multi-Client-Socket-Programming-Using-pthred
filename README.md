# Multi-Client-Socket-Programming-Using-pthred

A simple TCP client-server chat application with socket programming. 
Server can handle multiple clients with the help of multi-threading.

pthread is used to create and handle threads with very basic implmentation.

To compile client file simple gcc command can be used like: 
gcc -o client client.c

To compile server file following command can be used:
gcc -pthread -o server server.c

INSTRUCTIONS

Prerequisites
    Compiling will require thrift and libcurl to be installed.
    The Makefile assumes standard location of packages.

Compilation Run "make" in the top directory

To remove all object files and executables, run "make clean".
 
To enter the ipaddress of the server, change it in line 134 of client.cpp

Execution

To run the server, use one of the following commands: ./server_random [cache_size] ./server_fifo [cache_size] ./server_lru [cache_size]

Ex. ./server_random 1024000 (cache size of 1MB)

To run the client, use the following command: ./client [no of loops] [sequence]

Sequence= 0 for random 1 for repetitive

default(no of loops = 100 and sequence = 0)

Ex. ./client   (100 loops random sequence)
   ./client 100 1   (100 loops repititive sequence)

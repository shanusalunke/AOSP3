INSTRUCTIONS

Prerequisites

    Compiling will require thrift and libcurl to be installed.
    The Makefile assumes standard location of packages.

Compilation Run "make" in the top directory

To remove all object files and executables, run "make clean".

Execution

To run the server, use one of the following commands: ./server_random [cache_size] ./server_fifo [cache_size] ./server_lru [cache_size]

To run the client, use the following command: ./client [no of loops] [sequence]

= 1 for random 2 for repetitive
default(no of loops = 100 and sequence = 1)


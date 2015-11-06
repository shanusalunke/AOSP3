
g++ -o client client.cpp curl_fetch.cpp cache_FIFO.cpp cache_Random.cpp gen-cpp/HelloWorld.cpp gen-cpp/helloworld_constants.cpp gen-cpp/helloworld_types.cpp -std=c++11 -I gen-cpp -lcurl -lboost_system -lpthread -lthrift

g++ -o server server.cpp curl_fetch.cpp cache_FIFO.cpp cache_Random.cpp gen-cpp/HelloWorld.cpp gen-cpp/helloworld_constants.cpp gen-cpp/helloworld_types.cpp -std=c++11 -I gen-cpp -lcurl -lboost_system -lpthread -lthrift



sudo -- LD_LIBRARY_PATH=/home/shanu/Development/thrift/lib/ dc_full

thrift -r --gen cpp helloworld.thrift

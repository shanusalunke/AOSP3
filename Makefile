all: client server

client:
	g++ -o client client.cpp curl_fetch.cpp cache_FIFO.cpp cache_Random.cpp cache_LFU.cpp gen-cpp/HelloWorld.cpp gen-cpp/helloworld_constants.cpp gen-cpp/helloworld_types.cpp -std=c++11 -I gen-cpp -lcurl -lboost_system -lpthread -lthrift

server:
	g++ -o server server.cpp curl_fetch.cpp cache_FIFO.cpp cache_Random.cpp cache_LFU.cpp gen-cpp/HelloWorld.cpp gen-cpp/helloworld_constants.cpp gen-cpp/helloworld_types.cpp -std=c++11 -I gen-cpp -lcurl -lboost_system -lpthread -lthrift

clean:
	rm *o client server

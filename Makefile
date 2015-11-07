all: server

server: client
	g++ -o server server.cpp curl_fetch.cpp cache_FIFO.cpp cache_Random.cpp cache_LFU.cpp gen-cpp/proxy.cpp gen-cpp/HTTPproxy_constants.cpp gen-cpp/HTTPproxy_types.cpp -std=c++11 -I gen-cpp -lcurl -lboost_system -lpthread -lthrift

client:
	g++ -o client client.cpp curl_fetch.cpp cache_FIFO.cpp cache_Random.cpp cache_LFU.cpp gen-cpp/proxy.cpp gen-cpp/HTTPproxy_constants.cpp gen-cpp/HTTPproxy_types.cpp -std=c++11 -I gen-cpp -lcurl -lboost_system -lpthread -lthrift

clean:
	rm *o client server

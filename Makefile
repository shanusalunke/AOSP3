all: client server1 server2 server3

server1:
	g++ -Dfifo_policy -o server_fifo server.cpp curl_fetch.cpp cache_FIFO.cpp gen-cpp/proxy.cpp gen-cpp/HTTPproxy_constants.cpp gen-cpp/HTTPproxy_types.cpp -std=c++11 -I gen-cpp -lcurl -lboost_system -lpthread -lthrift

server2:
	g++ -Dlfu_policy -o server_lfu server.cpp curl_fetch.cpp cache_LFU.cpp gen-cpp/proxy.cpp gen-cpp/HTTPproxy_constants.cpp gen-cpp/HTTPproxy_types.cpp -std=c++11 -I gen-cpp -lcurl -lboost_system -lpthread -lthrift

server3:
	g++ -Drandom_policy -o server_random server.cpp curl_fetch.cpp cache_Random.cpp gen-cpp/proxy.cpp gen-cpp/HTTPproxy_constants.cpp gen-cpp/HTTPproxy_types.cpp -std=c++11 -I gen-cpp -lcurl -lboost_system -lpthread -lthrift

client:
	g++ -o client client.cpp curl_fetch.cpp cache_FIFO.cpp cache_Random.cpp cache_LFU.cpp gen-cpp/proxy.cpp gen-cpp/HTTPproxy_constants.cpp gen-cpp/HTTPproxy_types.cpp -std=c++11 -I gen-cpp -lcurl -lboost_system -lpthread -lthrift

clean:
	rm *.o client server_lfu server_fifo server_random

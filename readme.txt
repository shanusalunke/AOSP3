g++ -o client CppClient.cpp gen-cpp/Calculator.cpp gen-cpp/tutorial_constants.cpp gen-cpp/tutorial_types.cpp -std=c++11 -I gen-cpp -lboost_system -lpthread -lthrift



g++ -o client client.cpp gen-cpp/HelloWorld.cpp gen-cpp/helloworld_constants.cpp gen-cpp/helloworld_types.cpp -std=c++11 -I gen-cpp -lboost_system -lpthread -lthrift

g++ -o server server.cpp gen-cpp/HelloWorld.cpp gen-cpp/helloworld_constants.cpp gen-cpp/helloworld_types.cpp -std=c++11 -I gen-cpp -lboost_system -lpthread -lthrift


sudo -- LD_LIBRARY_PATH=/home/shanu/Development/thrift/lib/ dc_full


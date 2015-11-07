
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>
#include <boost/make_shared.hpp>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "gen-cpp/HelloWorld.h"
#include "../curl_fetch.h"
#include "cache_FIFO.h"
#include "cache_Random.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace hellons;


// cache_fifo cache;
cache_random cache;

class HelloWorldHandler : public HelloWorldIf {
public:

  HelloWorldHandler()
  {
         std::cout<<"Server is up and running...\n";
  }

void request(response& _return, const std::string& url)
{
       std::string cache_entry;
       std::cout<<"Requested URL: "<<url<<"\n";

       //Check if entry is in the cache
       if (cache.cache_fetch(url, _return.document) == 1){
         _return.cache_hit_flag = 0;
       }else{
         if (fetch_url(url, cache_entry) == 1){
           _return.cache_hit_flag = 1;
         }else if (cache.cache_insert(url, cache_entry) == 1){
           _return.cache_hit_flag = 2;
         }else{
           _return.cache_hit_flag = 3;
         }
         _return.document = cache_entry;
         std::cout<<"Insert into cache\n";
       }
}

void shutdown()
{
    printf("Shutting down...\n");
    exit(0);
  }
};


int main() {
  TThreadedServer server(
//  boost::make_shared<HelloWorldProcessorFactory>(boost::make_shared<HelloWorldCloneFactory>()),
  boost::make_shared<HelloWorldProcessor>(boost::make_shared<HelloWorldHandler>()),
  boost::make_shared<TServerSocket>(9091), //port
  boost::make_shared<TBufferedTransportFactory>(),
  boost::make_shared<TBinaryProtocolFactory>());


  cout << "Starting the server..." << endl;
  server.serve();
  cout << "Done." << endl;
  return 0;
}

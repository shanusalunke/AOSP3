
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

#include "gen-cpp/proxy.h"
#include "../curl_fetch.h"
#include "cache_FIFO.h"
#include "cache_LFU.h"
#include "cache_Random.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace HTTPproxy;

/*FIFO CACHE*/
//cache_fifo cache;

/*LFU CACHE*/
//cache_lfu cache;

/*RANDOM CACHE*/
 cache_random cache;

class proxyHandler : public proxyIf {
public:

  proxyHandler()
  {
         std::cout<<"Server is up and running...\n";
  }

void request(response& _return, const std::string& url)
{
       std::string cache_entry;
       std::cout<<"Requested URL: "<<url<<"\n";

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


int main(int argc, char **argv)
{
  int size;
 if (argc == 2)
 {
   size = atoi(argv[1]);
   cache.cache_set_max(size);
   cout<<"Cache size set to: "<<size<<endl;
 }

  TThreadedServer server(
  boost::make_shared<proxyProcessor>(boost::make_shared<proxyHandler>()),
  boost::make_shared<TServerSocket>(9091), //port
  boost::make_shared<TBufferedTransportFactory>(),
  boost::make_shared<TBinaryProtocolFactory>());


  cout << "Starting the server..." << endl;
  server.serve();
  cout << "Done." << endl;
  return 0;
}

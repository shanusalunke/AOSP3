#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sys/time.h>
#include <exception>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include "gen-cpp/HelloWorld.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace hellons;

class statistics
{
private:
  struct timeval tim;
  long hit_count;
  long miss_count;

  long hit_size;
  long miss_size;

  double hit_time;
  double miss_time;
public:
  statistics();
  void issue();
  void receive(int response, long rcv_size);
  void tally();
};

statistics::statistics()
{
  hit_count=0;
  miss_count=0;
  hit_size=0;
  miss_size=0;
  hit_time=0;
  miss_time=0;
}

int main()
{
  boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9091));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  response serverResponse;
  HelloWorldClient client(protocol);

  vector<string> url_list;
  int size = 0;
  string url;
  long doc_size;
  int index;
  ifstream in("url.list");
  while(in>>url)
  {
    url_list.push_back(url);
    size++;
  }
  in.close();

  try {
    transport->open();
    std::cout<<"Using access sequence : Random\n";
    for(int i=0;i<100;i++)
    {
          index = rand() % size;
          url = url_list[index];
          client.request(serverResponse, url);
          doc_size = (long)serverResponse.document.length();
            std::cout<<"DocSize: "<<doc_size<< "  "<<serverResponse.isCacheHit <<"\n";
    }
      //    url = "google.com";
      //    client.request(serverResponse, url);
        //  doc_size = (long)serverResponse.document.length();
      //    std::cout<<"DocSize: "<<doc_size<<"\n";



}
  catch (TException& tx)
  {
    cout << "ERROR: " << tx.what() << endl;
  }
  client.shutdown();
  transport->close();
}

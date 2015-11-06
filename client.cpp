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

   double time_int;
public:
  statistics();
  void issue();
  void receive(bool response, long rcv_size);
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

void statistics::issue()
{
  gettimeofday(&tim, NULL);
  time_int = tim.tv_sec+(tim.tv_usec/1000000.0);
}

void statistics::receive(bool response, long rcv_size)
{
    gettimeofday(&tim, NULL);
    time_int = (tim.tv_sec+(tim.tv_usec/1000000.0)) - time_int;
    switch(response)
    {
      case true :
          hit_count++;
          hit_size += rcv_size;
          hit_time += time_int;
          break;
      case false:
          miss_count++;
          miss_size += rcv_size;
          miss_time += time_int;
          break;
      }
  }

 void statistics::tally()
 {
   cout<<"Total requests = "<<hit_count+miss_count;
   cout<<"\nHit count = "<<hit_count<<"\nMiss count = "<<miss_count;
   cout<<"\nHit-data size = "<<hit_size<<"\nMiss-data size = "<<miss_size;
   cout<<"\n\nTotal time = "<<hit_time+miss_time;
   cout<<"\nAverage hit time = "<<((hit_count==0)? 0:(hit_time/hit_count));
   cout<<"\nAverage miss time = "<<((miss_count==0)? 0:(miss_time/miss_count));

   cout<<"\n\n==================  Key statistics  ==============\n"
             "Hit rate = "<<(float)hit_count/(hit_count+miss_count);
   cout<<"\nMiss penalty = "<<((miss_count==0)? 0:(((miss_time)/(miss_count))- ((hit_count==0)? 0:(hit_time/hit_count))));
   cout<<"\nAverage access time (AAT) = "<<(miss_time + hit_time)/ (miss_count+hit_count);
   cout<<"\n\nData hit rate = "<<(float)hit_size/(hit_size+miss_size);
   cout<<"\nMiss penalty per kB = "<<((miss_size==0)? 0:((((miss_time)*1000)/(miss_size))- ((hit_size==0)? 0:((hit_time*1000)/hit_size))));
   cout<<"\nAverage access time (AAT) per kB = "<<((miss_time + hit_time)*1000)/ (miss_size+hit_size);

 }


int main()
{
  statistics stats;
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
          stats.issue();
          client.request(serverResponse, url);
          doc_size = (long)serverResponse.document.length();
          stats.receive(serverResponse.isCacheHit, doc_size);
          cout<<"DocSize: "<<doc_size<< "  "<<serverResponse.isCacheHit <<"\n";
    }
      //    url = "google.com";
      //    client.request(serverResponse, url);
        //  doc_size = (long)serverResponse.document.length();
      //    std::cout<<"DocSize: "<<doc_size<<"\n";
   stats.tally();
}
  catch (TException& tx)
  {
    cout << "ERROR: " << tx.what() << endl;
  }
  client.shutdown();
  transport->close();
}

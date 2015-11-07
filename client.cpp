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
  long curl_fail_count;
  long data_exceed_count;
  long hit_size;
  long miss_size;
  long data_exceed_size;
  double hit_time;
  double miss_time;
  double curl_fail_time;
  double data_exceed_time;
   double time_int;
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
  curl_fail_count=0;
  data_exceed_count=0;
  hit_size=0;
  miss_size=0;
  data_exceed_size=0;
  hit_time=0;
  miss_time=0;
  curl_fail_time=0;
  data_exceed_time=0;
}

void statistics::issue()
{
  gettimeofday(&tim, NULL);
  time_int = tim.tv_sec+(tim.tv_usec/1000000.0);
}

void statistics::receive(int response, long rcv_size)
{
    gettimeofday(&tim, NULL);
    time_int = (tim.tv_sec+(tim.tv_usec/1000000.0)) - time_int;
    /*
    0 - cache hit
    1 - cache miss because couldn't return curl
    2 - cache miss because couldn't find in cache
    3 - cache miss because document couldn't fit in the cache
    */
    switch(response)
    {
      case 0 :
          hit_count++;
          hit_size += rcv_size;
          hit_time += time_int;
          break;
      case 1:
          curl_fail_count++;
          curl_fail_time += time_int;
          break;
      case 2:
          miss_count++;
          miss_size += rcv_size;
          miss_time += time_int;
          break;
      case 3:
          data_exceed_count++;
          data_exceed_size += rcv_size;
          data_exceed_time += time_int;
          break;
      }
  }

 void statistics::tally()
 {
   cout<<"Total requests = "<<hit_count+miss_count+data_exceed_count+curl_fail_count;
   cout<<"\nHit count = "<<hit_count<<"\nMiss count = "<<miss_count;
   cout<<"\nCache capacity exceed count = "<<data_exceed_count;
   cout<<"\nFailed requests = "<<curl_fail_count<<"\n";
   cout<<"\nHit-data size = "<<hit_size<<"\nMiss-data size = "<<miss_size;
   cout<<"\nCache capacity exceed-data size = "<<data_exceed_size;
   cout<<"\n\nTotal time = "<<hit_time+miss_time+data_exceed_time+curl_fail_time;
   cout<<"\nAverage hit time = "<<((hit_count==0)? 0:(hit_time/hit_count));
   cout<<"\nAverage miss time = "<<((miss_count==0)? 0:(miss_time/miss_count));
   cout<<"\nAverage exceed time = "<<((data_exceed_count==0)? 0:(data_exceed_time/data_exceed_count));
   cout<<"\nAverage failure time = "<<((curl_fail_count==0)? 0:(curl_fail_time/curl_fail_count));
   cout<<"\nOverall average miss time = "<<((miss_count+data_exceed_count==0)? 0:((miss_time + data_exceed_time)/(miss_count+data_exceed_count)));
   cout<<"\n\n==================  Key statistics  ==============\n";
   cout<<"Hit rate = "<<(float)hit_count/(hit_count+miss_count+curl_fail_count+data_exceed_count);
   cout<<"\nMiss penalty = "<<((miss_count+data_exceed_count==0)? 0:(((miss_time + data_exceed_time)/(miss_count+data_exceed_count))- ((hit_count==0)? 0:(hit_time/hit_count))));
   cout<<"\nAverage access time (AAT) = "<<(miss_time + data_exceed_time + hit_time)/ (miss_count+data_exceed_count+hit_count);
   cout<<"\n\nData hit rate = "<<(float)hit_size/(hit_size+miss_size+data_exceed_size);
   cout<<"\nMiss penalty per kB = "<<((miss_size+data_exceed_size==0)? 0:((((miss_time + data_exceed_time)*1000)/(miss_size+data_exceed_size))- ((hit_size==0)? 0:((hit_time*1000)/hit_size))));
   cout<<"\nAverage access time (AAT) per kB = "<<((miss_time + data_exceed_time + hit_time)*1000)/ (miss_size+data_exceed_size+hit_size);
 }


int main(int argc, char **argv)
{
  int NUM_LOOPS = 100;
  int SEQUENCE = 0; //0-random 1-predefined
  if (argc == 3)
  {
    NUM_LOOPS = atoi(argv[1]);
    SEQUENCE = atoi(argv[2]);
  }
  // std::cout<<"Number of loops = "<<NUM_LOOPS <<"\tSequence = "<< SEQUENCE;

  statistics stats;
  // boost::shared_ptr<TTransport> socket(new TSocket("10.0.0.8", 9091));
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

    switch (SEQUENCE){
      case 0:{
        // std::cout<<"Using access sequence : Random\n";
        for(int i=0;i<NUM_LOOPS;i++)
        {
          index = rand() % size;
          url = url_list[index];
          stats.issue();
          client.request(serverResponse, url);
          doc_size = (long)serverResponse.document.length();
          stats.receive(serverResponse.cache_hit_flag, doc_size);
          // cout<<"DocSize: "<<doc_size<< "  "<<serverResponse.cache_hit_flag <<"\n";
        }
        break;
      }
      case 1:{
        // std::cout<<"Using access sequence : Predefined\n";
        int count=0;
        int i=0;
        while(count<NUM_LOOPS)
        {
          //i-1
          if (i>0){
            index = (i-1) % size;
            url = url_list[index];
            stats.issue();
            client.request(serverResponse, url);
            doc_size = (long)serverResponse.document.length();
            stats.receive(serverResponse.cache_hit_flag, doc_size);
            // cout<<"DocSize: "<<doc_size<< "  "<<serverResponse.cache_hit_flag <<"\n";
            count++;
          }

          //i
          index = (i) % size;
          url = url_list[index];
          stats.issue();
          client.request(serverResponse, url);
          doc_size = (long)serverResponse.document.length();
          stats.receive(serverResponse.cache_hit_flag, doc_size);
          // cout<<"DocSize: "<<doc_size<< "  "<<serverResponse.cache_hit_flag <<"\n";
          count++;

          //i+1
          if (i < NUM_LOOPS-1){
            index = (i+1) % size;
            url = url_list[index];
            stats.issue();
            client.request(serverResponse, url);
            doc_size = (long)serverResponse.document.length();
            stats.receive(serverResponse.cache_hit_flag, doc_size);
            // cout<<"DocSize: "<<doc_size<< "  "<<serverResponse.cache_hit_flag <<"\n";
            count++;
          }

          i++;
        }
      }
    }//end of switch

   stats.tally();
}
  catch (TException& tx)
  {
    cout << "ERROR: " << tx.what() << endl;
  }
  client.shutdown();
  transport->close();
}

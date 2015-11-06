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

int main() {
  boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9091));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  response serverResponse;
  HelloWorldClient client(protocol);

  int size = 0;
  std::string url;

  long doc_size;
  try {
    transport->open();
    std::cout<<"Using access sequence : Random\n";

          url = "google.com";
          client.request(serverResponse, url);
          doc_size = (long)serverResponse.document.length();
          std::cout<<"DocSize: "<<doc_size<< "  "<<serverResponse.isCacheHit <<"\n";

}
  catch (TException& tx)
  {
    cout << "ERROR: " << tx.what() << endl;
  }
  client.shutdown();
  transport->close();
}

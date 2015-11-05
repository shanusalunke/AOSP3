
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

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace hellons;

class HelloWorldHandler : public HelloWorldIf {
public:
  HelloWorldHandler() {}

  void ping() { cout << "ping()" << endl; }

  int32_t sayHello(){
    return 3;
  }

  void zip() { cout << "zip()" << endl; }
};

class HelloWorldCloneFactory : virtual public HelloWorldIfFactory {
public:
  virtual ~HelloWorldCloneFactory() {}
  virtual HelloWorldIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo)
{
  boost::shared_ptr<TSocket> sock = boost::dynamic_pointer_cast<TSocket>(connInfo.transport);
  cout << "Incoming connection\n";
  cout << "\tSocketInfo: "  << sock->getSocketInfo() << "\n";
  cout << "\tPeerHost: "    << sock->getPeerHost() << "\n";
  cout << "\tPeerAddress: " << sock->getPeerAddress() << "\n";
  cout << "\tPeerPort: "    << sock->getPeerPort() << "\n";
  return new HelloWorldHandler;
}

// virtual void releaseHandler( ::shared::SharedServiceIf* handler) {
//   delete handler;
 //}

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

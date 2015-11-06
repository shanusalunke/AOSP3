/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef HelloWorld_H
#define HelloWorld_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "helloworld_types.h"

namespace hellons {

#ifdef _WIN32
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class HelloWorldIf {
 public:
  virtual ~HelloWorldIf() {}
  virtual void request(response& _return, const std::string& url) = 0;
  virtual void shutdown() = 0;
};

class HelloWorldIfFactory {
 public:
  typedef HelloWorldIf Handler;

  virtual ~HelloWorldIfFactory() {}

  virtual HelloWorldIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(HelloWorldIf* /* handler */) = 0;
};

class HelloWorldIfSingletonFactory : virtual public HelloWorldIfFactory {
 public:
  HelloWorldIfSingletonFactory(const boost::shared_ptr<HelloWorldIf>& iface) : iface_(iface) {}
  virtual ~HelloWorldIfSingletonFactory() {}

  virtual HelloWorldIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(HelloWorldIf* /* handler */) {}

 protected:
  boost::shared_ptr<HelloWorldIf> iface_;
};

class HelloWorldNull : virtual public HelloWorldIf {
 public:
  virtual ~HelloWorldNull() {}
  void request(response& /* _return */, const std::string& /* url */) {
    return;
  }
  void shutdown() {
    return;
  }
};

typedef struct _HelloWorld_request_args__isset {
  _HelloWorld_request_args__isset() : url(false) {}
  bool url :1;
} _HelloWorld_request_args__isset;

class HelloWorld_request_args {
 public:

  HelloWorld_request_args(const HelloWorld_request_args&);
  HelloWorld_request_args& operator=(const HelloWorld_request_args&);
  HelloWorld_request_args() : url() {
  }

  virtual ~HelloWorld_request_args() throw();
  std::string url;

  _HelloWorld_request_args__isset __isset;

  void __set_url(const std::string& val);

  bool operator == (const HelloWorld_request_args & rhs) const
  {
    if (!(url == rhs.url))
      return false;
    return true;
  }
  bool operator != (const HelloWorld_request_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const HelloWorld_request_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class HelloWorld_request_pargs {
 public:


  virtual ~HelloWorld_request_pargs() throw();
  const std::string* url;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _HelloWorld_request_result__isset {
  _HelloWorld_request_result__isset() : success(false) {}
  bool success :1;
} _HelloWorld_request_result__isset;

class HelloWorld_request_result {
 public:

  HelloWorld_request_result(const HelloWorld_request_result&);
  HelloWorld_request_result& operator=(const HelloWorld_request_result&);
  HelloWorld_request_result() {
  }

  virtual ~HelloWorld_request_result() throw();
  response success;

  _HelloWorld_request_result__isset __isset;

  void __set_success(const response& val);

  bool operator == (const HelloWorld_request_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const HelloWorld_request_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const HelloWorld_request_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _HelloWorld_request_presult__isset {
  _HelloWorld_request_presult__isset() : success(false) {}
  bool success :1;
} _HelloWorld_request_presult__isset;

class HelloWorld_request_presult {
 public:


  virtual ~HelloWorld_request_presult() throw();
  response* success;

  _HelloWorld_request_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class HelloWorld_shutdown_args {
 public:

  HelloWorld_shutdown_args(const HelloWorld_shutdown_args&);
  HelloWorld_shutdown_args& operator=(const HelloWorld_shutdown_args&);
  HelloWorld_shutdown_args() {
  }

  virtual ~HelloWorld_shutdown_args() throw();

  bool operator == (const HelloWorld_shutdown_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const HelloWorld_shutdown_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const HelloWorld_shutdown_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class HelloWorld_shutdown_pargs {
 public:


  virtual ~HelloWorld_shutdown_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class HelloWorldClient : virtual public HelloWorldIf {
 public:
  HelloWorldClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  HelloWorldClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void request(response& _return, const std::string& url);
  void send_request(const std::string& url);
  void recv_request(response& _return);
  void shutdown();
  void send_shutdown();
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class HelloWorldProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<HelloWorldIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (HelloWorldProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_request(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_shutdown(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  HelloWorldProcessor(boost::shared_ptr<HelloWorldIf> iface) :
    iface_(iface) {
    processMap_["request"] = &HelloWorldProcessor::process_request;
    processMap_["shutdown"] = &HelloWorldProcessor::process_shutdown;
  }

  virtual ~HelloWorldProcessor() {}
};

class HelloWorldProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  HelloWorldProcessorFactory(const ::boost::shared_ptr< HelloWorldIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< HelloWorldIfFactory > handlerFactory_;
};

class HelloWorldMultiface : virtual public HelloWorldIf {
 public:
  HelloWorldMultiface(std::vector<boost::shared_ptr<HelloWorldIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~HelloWorldMultiface() {}
 protected:
  std::vector<boost::shared_ptr<HelloWorldIf> > ifaces_;
  HelloWorldMultiface() {}
  void add(boost::shared_ptr<HelloWorldIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void request(response& _return, const std::string& url) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->request(_return, url);
    }
    ifaces_[i]->request(_return, url);
    return;
  }

  void shutdown() {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->shutdown();
    }
    ifaces_[i]->shutdown();
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class HelloWorldConcurrentClient : virtual public HelloWorldIf {
 public:
  HelloWorldConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  HelloWorldConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void request(response& _return, const std::string& url);
  int32_t send_request(const std::string& url);
  void recv_request(response& _return, const int32_t seqid);
  void shutdown();
  void send_shutdown();
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _WIN32
  #pragma warning( pop )
#endif

} // namespace

#endif
// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "ThriftTestKernalService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::thrift_test_kernal;

class ThriftTestKernalServiceHandler : virtual public ThriftTestKernalServiceIf {
 public:
  ThriftTestKernalServiceHandler() {
    // Your initialization goes here
  }

  void GetServiceList(GetServiceListResponse& _return, const GetServiceListRequest& request) {
    // Your implementation goes here
    printf("GetServiceList\n");
  }

  void AddService(AddServiceResponse& _return, const AddServiceRequest& request) {
    // Your implementation goes here
    printf("AddService\n");
  }

  void FillData(FillDataResponse& _return, const FillDataRequest& request) {
    // Your implementation goes here
    printf("FillData\n");
  }

  void RequestTrigger(RequestTriggerReseponse& _return, const RequestTriggerRequest& request) {
    // Your implementation goes here
    printf("RequestTrigger\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<ThriftTestKernalServiceHandler> handler(new ThriftTestKernalServiceHandler());
  shared_ptr<TProcessor> processor(new ThriftTestKernalServiceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}


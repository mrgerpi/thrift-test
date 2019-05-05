#include "CalculatorService.h"

#include "simple_log.h"
#include <boost/shared_ptr.hpp>

#include <thrift/transport/TSocket.h>
#include <thrift/transport/TSimpleFileTransport.h>
#include <thrift/transport/TTransport.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>

using namespace std;
using namespace thrift_test_kernel;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

extern "C" int calculator_Calculate_1234()
{
	boost::shared_ptr<TSocket> socket(new TSocket(ip, port));
	boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

	socket->setConnTimeout(500);
	socket->setRecvTimeout(300);
	socket->setSendTimeout(300);
	shared_ptr<CalculatorServiceClient> client(new CalculatorServiceClient(protocol));
	using apache::thrift::to_string;

	CalculateResponse rsp;

	CalculateResponse req;
	boost::shared_ptr<TTransport> CalculatorRequest_itrans(new TSimpleFileTransport(REQ_PATH, true, true));
	boost::shared_ptr<TProtocol> CalculatorRequest_iprot(new TJSONProtocol(otrans));
	rsp.read(CalculatorRequest_iprot.get());
	log_info("calculator client||entry||CalculatorRequest=%s", to_string(req).c_str());	

	transport->open();
	try {
		client->Caculate(rsp, req);	
	} catch (TException& tx) {
		log_error("Calculate Exception||message=%s", tx.what());
		transport->close();
		return -1;
	}
	transport->close();
	log_info("Calculate||rpc||rsp=%s", to_string(rsp).c_str());


	boost::shared_ptr<TTransport> otrans(new TSimpleFileTransport(REQ_PATH, true, true));
	boost::shared_ptr<TProtocol> iprot(new TJSONProtocol(otrans));
	rsp.read(iprot.get());
	log_info("calculator client||exit||CalculateResponse=%s", to_string(rsp).c_str());	
}

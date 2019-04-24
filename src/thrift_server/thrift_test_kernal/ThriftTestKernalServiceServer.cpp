#include "ThriftTestKernalServiceServer.h"
#include "ThriftTestKernalServiceHandler.h"
#include "ThriftTestKernalService.h"
#include "didiutils.h"

#include "thrift/TProcessor.h"
#include "thrift/protocol/TBinaryProtocol.h"
#include "thrift/protocol/TProtocol.h"
#include "thrift/concurrency/ThreadManager.h"
#include "thrift/concurrency/PosixThreadFactory.h"
#include "simple_log.h" 


#define nThreadNum 5
#define nPort	9537
#define THREAD_STACK_SIZE  64


using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace apache::thrift::concurrency;


ThriftTestKernalServiceServer* ThriftTestKernalServiceServer::p = NULL;

ThriftTestKernalServiceServer* ThriftTestKernalServiceServer::instance() {
	if (p == NULL) {
		p = new ThriftTestKernalServiceServer();
	} 
	return p;
}

int ThriftTestKernalServiceServer::startServer() {
	uint64_t begin = DidiUtils::timems();

	boost::shared_ptr<ThriftTestKernalServiceHandler> handler (new ThriftTestKernalServiceHandler());
	boost::shared_ptr<TProcessor> processor (new ThriftTestKernalServiceProcessor(handler));
	boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

	boost::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(nThreadNum);
	boost::shared_ptr<PosixThreadFactory> threadFactory = boost::shared_ptr<PosixThreadFactory>(
			new PosixThreadFactory(apache::thrift::concurrency::PosixThreadFactory::ROUND_ROBIN,
				apache::thrift::concurrency::PosixThreadFactory::NORMAL,
				THREAD_STACK_SIZE));
	threadManager->threadFactory(threadFactory);
	threadManager->start();
	manager_ = threadManager;

	server_ = new TNonblockingServer(processor, protocolFactory, nPort, threadManager);
	//server_->setServerEventHandler(boost::shared_ptr<TServerEventHandler>(new ClientIpServerEventHandler()));
	log_info ("star server t_cost: %lums", DidiUtils::timems()- begin);
	try
	{
		server_->serve();
	}
	catch(TException& tx)
	{
		threadManager->stop();
		log_error("failed to start server:tx.what:%s",tx.what());
		exit(1);
	}
}

int ThriftTestKernalServiceServer::stopServer() {

}

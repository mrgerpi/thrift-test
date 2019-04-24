#ifndef _thrift_test_kernal_server_h_
#define _thrift_test_kernal_server_h_

#include "thrift/server/TNonblockingServer.h"

class ThriftTestKernalServiceServer {
	private:
		ThriftTestKernalServiceServer() :server_(NULL) {}
		~ThriftTestKernalServiceServer() 
		{
			if (server_ != NULL) {
				delete server_;
				server_ = NULL;
			} 
		}
		static ThriftTestKernalServiceServer* p;
		::apache::thrift::server::TNonblockingServer* server_;
		boost::shared_ptr<apache::thrift::concurrency::ThreadManager> manager_;
	public:
		static ThriftTestKernalServiceServer* instance();
		int startServer();
		int stopServer();
};

#endif

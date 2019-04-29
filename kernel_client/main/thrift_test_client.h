#ifndef _thrift_test_client_h_
#define _thrift_test_client_h_

#include <boost/shared_ptr.hpp>
#include <string>

#include "ThriftTestKernalService.h"

#define REQ 1
#define RSP 2

using namespace std;
using namespace thrift_test_kernal;
using namespace apache::thrift::protocol;

class ThriftTestClient {
private:
	boost::shared_ptr<ThriftTestKernalServiceClient> clientPtr;
	boost::shared_ptr<TTransport> transport;
	TProtocol* getJsonProtocol(string path);
public:
	ThriftTestClient(int port, string ip = "127.0.0.1");
	~ThriftTestClient(){};
public:
	int GetServiceList(const string& reqJson, string& rspJson);
	int AddService(const string& reqJson, string& rspJson);
	int FillData(const string& reqJson, string& rspJson);
	int RequestTrigger(const string& reqJson, string& rspJson);
public:
	static int readAllFile(string path, string& content);
	static int writeAllFile(const string& path, const string& content);
};

#endif

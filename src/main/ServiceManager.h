#ifndef _service_manager_h_
#define _service_manager_h_

#include "ThriftTestKernelService.h"
#include "ServiceSrcGenerator.h"

#include <pthread.h>
#include <string>
#include <vector>
#include <map>

using namespace std;
using namespace thrift_test_kernel;

//serviceId format: serviceName_version_port_transport_protocol
class ServiceManager {
private:
	pthread_mutex_t mutex;
	ServiceSrcGenerator* generator;
	vector<string> serverList;
	map<string, string> serviceIdToSrcPath;
private:
	string serviceIdGen(const AddServiceRequest& req);
	string srcDirGen(const AddServiceRequest& req);
public:
	ServiceManager();
	~ServiceManager();
public:
	/*
	 * @return
	 * 0:succ
	 * 1:kernel internal error
	 * 2:compile error, idl file invalid
	 * 3:para error
	 */
	int addService(const AddServiceRequest& req);

	int getServiceList(ServiceType type, vector<string>& list);

	int requestTrigger(string serviceName, string methodName);
};

#endif

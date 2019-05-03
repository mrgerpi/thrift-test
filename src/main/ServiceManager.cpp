#include "ServiceManager.h"
#include "ThriftTestKernelService.h"
#include "simple_log.h"
#include "didiutils.h"

#include <pthread.h>
#include <string>
#include <map>

using namespace std;
using namespace thrift_test_kernel;

ServiceManager::ServiceManager() 
{
	pthread_mutex_init(&mutex, NULL);
	generator = new ServiceSrcGenerator();
}

ServiceManager::~ServiceManager() 
{
	pthread_mutex_destroy(&mutex);
	if (generator != NULL) {
		delete generator;
	}
}

string ServiceManager::serviceIdGen(const AddServiceRequest& req) 
{
	return req.serviceName + "_" + req.version + "_" + DidiUtils::print(req.port) + "_"
		+ req.transport + "_" + req.protocol;
}

string ServiceManager::srcDirGen(const AddServiceRequest& req) 
{
	string curPath = DidiUtils::pwd();
	return curPath + "/thrift_gen/" + req.serviceName;
}

int ServiceManager::addService(const AddServiceRequest& req) 
{
	int ret;
	string serviceId = serviceIdGen(req);
	string genSrcDir;

	string idl;
	ret = DidiUtils::readFile(req.idlAbsFileName, idl);
	if (ret != 0) {
		log_error("ServiceManager::addService||rea idl file failed||path=%s", 
				req.idlAbsFileName.c_str());
		return ret;
	}

	map<string, string>::iterator it = serviceIdToSrcPath.find(serviceId);
	if (it == serviceIdToSrcPath.end()) {
		genSrcDir = srcDirGen(req);
		int ret = generator->serviceSrcGen(serviceId, req.idlAbsFileName, genSrcDir);
		if (ret != 0) {
			log_error("ServiceManager::addService||service src gen failed||serviceId=%s||ret=%d", 
					serviceId.c_str(), ret);
			return ret;
		}
	} else {
		genSrcDir = it->second;
		log_info("ServiceManager::addService||service src exists||serviceId=%s||\
				srcPath=%s", serviceId.c_str(), genSrcDir.c_str());
	}

}



#include "ServiceManager.h"
#include "ThriftTestKernelService.h"
#include "simple_log.h"
#include "didiutils.h"

#include <pthread.h>
#include <string>
#include <map>
#include <algorithm>

using namespace std;
using namespace thrift_test_kernel;

void* start_service_server(void* args) 
{
	Server_Args* p = (Server_Args*)args;
	log_info("%s server start! :)", (p->serviceId).c_str());
	p->server->serve();
}

ServiceManager::ServiceManager() 
{
	pthread_mutex_init(&mutex, NULL);
	generator = new ServiceSrcGenerator();
	loader = new ServiceLoader();
}

ServiceManager::~ServiceManager() 
{
	pthread_mutex_destroy(&mutex);
	if (generator != NULL) {
		delete generator;
	}
	if (loader != NULL) {
		delete loader;
	}
}

string ServiceManager::serviceIdGen(const AddServiceRequest& req) 
{
	return req.serviceName + "_" + req.version + "_" + DidiUtils::print(req.port) + "_"
		+ req.transport + "_" + req.protocol;
}

int ServiceManager::addService(const AddServiceRequest& req) 
{
	int ret;
	string serviceId = serviceIdGen(req);
	vector<string> methodList;

	//original src gen
	vector<string>::iterator it = find(originalSrcServiceId.begin(), 
			originalSrcServiceId.end(), serviceId);
	if (it == originalSrcServiceId.end()) {
		ret = generator->originalSrcGen(serviceId, req.idlAbsFileName);
		if (ret != 0) {
			log_error("ServiceManager::addService||origin src gen failed||serviceId=%s||ret=%d", 
					serviceId.c_str(), ret);
			return ret;
		}
		pthread_mutex_lock(&mutex);
		originalSrcServiceId.push_back(serviceId);
		pthread_mutex_unlock(&mutex);
	} else {
		log_info("ServiceManager::addService||origin src exists||serviceId=%s", 
				serviceId.c_str());
	}

	if (req.type == ServiceType::Client) {		//add Client src
		vector<string>::iterator it = find(clientSrcServiceId.begin(), 
				clientSrcServiceId.end(), serviceId);
		if (it == clientSrcServiceId.end()) {
			string methodStr;
			ret = generator->clientSrcGen(serviceId, req.idlAbsFileName, methodStr);
			if (ret != 0) {
				log_error("ServiceManager::addService||client src gen failed||serviceId=%s||ret=%d", 
						serviceId.c_str(), ret);
				return ret;
			}

			DidiUtils::split_str(methodStr, methodList, "\n");

			pthread_mutex_lock(&mutex);
			clientSrcServiceId.push_back(serviceId);
			pthread_mutex_unlock(&mutex);
		} else {
			log_info("ServiceManager::addService||client src exists||serviceId=%s", 
					serviceId.c_str());
		}
	} else if (req.type == ServiceType::Server) { //add Server src
		vector<string>::iterator it = find(serverSrcServiceId.begin(), 
				serverSrcServiceId.end(), serviceId);
		if (it == serverSrcServiceId.end()) {
			ret = generator->serverSrcGen(serviceId, req.idlAbsFileName);
			if (ret != 0) {
				log_error("ServiceManager::addService||server src gen failed||serviceId=%s||ret=%d", 
						serviceId.c_str(), ret);
				return ret;
			}
			pthread_mutex_lock(&mutex);
			serverSrcServiceId.push_back(serviceId);
			pthread_mutex_unlock(&mutex);
		} else {
			log_info("ServiceManager::addService||server src exists||serviceId=%s", 
					serviceId.c_str());
		}
	}


	//compile src to dynamic lib
	ret = loader->compile(serviceId, req.idlAbsFileName, req.type);
	if (ret != 0) {
		log_error("ServiceManager::addService||ServiceLoader Compile error||serviceId=%s||type=%d||ret=%d", serviceId.c_str(), req.type, ret);
		return ret;
	}

	//link dynamic lib to process
	ret = loader->link(serviceId, req.type);
	if (ret != 0) {
		log_error("ServiceManager::addService||ServiceLoader link error||serviceId=%s||type=%d||ret=%d", serviceId.c_str(), req.type, ret);
		return ret;
	}

	if (req.type == ServiceType::Server) {
		TSimpleServer* server = loader->getServer(serviceId);
		if (server == NULL) {
			log_error("ServiceManager::addService||ServiceLoader get server error||serviceId=%s||type=%d", serviceId.c_str(), req.type);
			return 1;
		}

		pthread_mutex_lock(&mutex);
		serverMap[serviceId] = server;
		pthread_mutex_unlock(&mutex);

		Server_Args* args = new Server_Args(serviceId, server);

		pthread_t t;
		pthread_create(&t, NULL, start_service_server, args);

		pthread_mutex_lock(&mutex);
		serverThreadMap[serviceId] = t;
		pthread_mutex_unlock(&mutex);
	} else if (req.type == ServiceType::Client) {
		map<string, Client_Entry> entryMap;
		for (vector<string>::iterator it = methodList.begin();it != methodList.end();it++) {
			Client_Entry entry = loader->getMethod(serviceId, *it);
			if (entry == NULL) {
				log_error("ServiceManager::addService||ServiceLoader get method error||serviceId=%s||method=%s", serviceId.c_str(), (*it).c_str());
				return 1;
			}

			entryMap[*it] = entry;
			log_info("ServiceManager::addService||add method succ||serviceId=%s||method=%s", serviceId.c_str(), (*it).c_str());
		}
		
		pthread_mutex_lock(&mutex);
		methodMap[serviceId] = entryMap;
		pthread_mutex_unlock(&mutex);
	}

	return 0;
}



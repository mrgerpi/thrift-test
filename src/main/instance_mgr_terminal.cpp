#include <unistd.h>

#include "instance_mgr_terminal.h"
#include "simple_log.h"
#include "ThriftTestKernalServiceServer.h"

void* start_thrift_server(void* args) {
	log_debug("thrift server start");
	ThriftTestKernalServiceServer::instance()->startServer();
}

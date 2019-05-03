#ifndef _service_src_generator_h_
#define _service_src_generator_h_

#include <string>

using namespace std;

class ServiceSrcGenerator {
private:
	int executeShell(string cmd, string& result);
public:
	ServiceSrcGenerator();

	/*
	 * @return
	 * 0: succ
	 * 1: compile error
	 * 2: internal error
	 */
	int serviceSrcGen(string serviceId, string idlPath, string srcDir);

};

#endif

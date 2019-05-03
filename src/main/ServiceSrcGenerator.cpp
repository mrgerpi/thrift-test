#include "ServiceSrcGenerator.h"
#include "didiutils.h"
#include "simple_log.h"

#include <stdio.h>
#include <string.h>
#include <sstream>
#include <errno.h>

using namespace std;

ServiceSrcGenerator::ServiceSrcGenerator()
{
}

int isDigit(string str, int& ret)
{
	istringstream iss(str);
	iss >> ret;
	if (iss.good()) {
		return 1;
	} else {
		return 0;
	}
}

int ServiceSrcGenerator::executeShell(string cmd, string& result)
{
	string realCmd = cmd + " 2>&1";
	FILE* fp = popen(realCmd.c_str(), "r");
	if (fp == NULL) {
		log_error("ServiceSrcGenerator::executeShell||popen fail||cmd=%s", realCmd.c_str());
		return 1;
	}

	char buff[256];		
	int ret = 0;
	do {
		if (fgets(buff, sizeof(buff), fp) == NULL) {
			break;		//EOF && no char be read
		}
		string line(buff);
		if (isDigit(line, ret)) {
			break;
		}
		result += line;
	}while(true);

	//errno == ECHILD: child process recover by wait system call
	if (pclose(fp) == -1 && errno != ECHILD) {
		log_error("ServiceSrcGenerator::executeShell||pclose fail||cmd=%s||err=%s", realCmd.c_str(), strerror(errno));
		return 1;
	}
	return ret;
}

int ServiceSrcGenerator::serviceSrcGen(string serviceId, 
		string idlPath, string srcDir) 
{
	string genScriptPaht = DidiUtils::pwd() + "/serviceGen.sh";
	string cmd = genScriptPaht + " " + idlPath + " " + srcDir;	
	log_info("ServiceSrcGenerator::serviceSrcGen||start service gen script||cmd=%s",
			cmd.c_str());
	string result;
	int ret = executeShell(cmd, result);
	if (ret != 0) {
		log_error("ServiceSrcGenerator::serviceSrcGen||service gen script exe fail||result=%s||ret=%d", result.c_str(), ret);
		return ret;
	} else {
		log_info("ServiceSrcGenerator::serviceSrcGen||service gen script succ||result=%s", result.c_str());
		return 0;
	}
}


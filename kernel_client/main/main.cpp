#include <iostream>
#include <string>
#include <vector>
#include <signal.h>
#include <execinfo.h>
#include <pthread.h>

#include "simple_log.h"
#include "cmd_parser.h"
#include "thrift_test_client.h"

using namespace std;

const static string log_conf_dir = "conf";
const static string log_conf_filename = "simple.conf";

void DumpTraceback(int Signal)
{
    const int len = 200;
    void* buffer[len];
    int nptrs = ::backtrace(buffer, len);		//
    char** strings = ::backtrace_symbols(buffer, nptrs);
    if (strings)
    {
      for (int i = 0; i < nptrs; ++i)
      {
		log_error("DumpTraceBack||line=%d||trace_back=%s", i, strings[i]);
      }
      free(strings);
    }
    exit(1);
}

int sig_actions() 
{
	/*
	// Delay exit
    signal(SIGTERM, DelayExit);
	*/
    // Ignore signal
    signal(SIGTERM, SIG_IGN);
	signal(SIGINT, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);

    // Dump traceback when crash.
    // Core signal's default action is to terminate the process and dump core.
    signal(SIGBUS, DumpTraceback);  // 10 Core  Bus error (bad memory access)
    signal(SIGSEGV, DumpTraceback); // 11 Core  Invalid memory reference
    signal(SIGABRT, DumpTraceback); // 6  Core  Abort signal from abort(3)
    signal(SIGILL, DumpTraceback);  // 4  Core  Illegal Instruction
    signal(SIGFPE, DumpTraceback);  // 8  Core  Floating point exception
}


void showHelp() 
{
	cout << "1-GetServiceList: \t\tclient 1" << endl;
	cout << "2-AddService: \t\t\tclient 2" << endl;
	cout << "3-FillData: \t\t\tclient 3" << endl;
	cout << "4-RequestTrigger:\t\tclient 4" << endl;
}

string GetServiceList(CmdParser& parser)
{
	string reqJson; 
	string rspJson; 
	int ret = ThriftTestClient::readAllFile("./input/GetServiceList.json", reqJson);
	if (ret == -1) {
		return "";
	}
	ThriftTestClient client(9537);	
	ret = client.GetServiceList(reqJson, rspJson);
	if (ret == -1) {
		return "";
	}
	return rspJson;
}

string AddService(CmdParser& parser)
{
	string reqJson; 
	string rspJson; 
	int ret = ThriftTestClient::readAllFile("./input/AddService.json", reqJson);
	if (ret == -1) {
		return "";
	}
	ThriftTestClient client(9537);	
	ret = client.AddService(reqJson, rspJson);
	if (ret == -1) {
		return "";
	}
	return rspJson;
}

string FillData(CmdParser& parser)
{
	string reqJson; 
	string rspJson; 
	int ret = ThriftTestClient::readAllFile("./input/FillData.json", reqJson);
	if (ret == -1) {
		return "";
	}
	ThriftTestClient client(9537);	
	ret = client.FillData(reqJson, rspJson);
	if (ret == -1) {
		return "";
	}
	return rspJson;
}

string RequestTrigger(CmdParser& parser)
{
	string reqJson; 
	string rspJson; 
	int ret = ThriftTestClient::readAllFile("./input/RequestTrigger.json", reqJson);
	if (ret == -1) {
		return "";
	}
	ThriftTestClient client(9537);	
	ret = client.RequestTrigger(reqJson, rspJson);
	if (ret == -1) {
		return "";
	}
	return rspJson;
}

int main(int argc, char* argv[]) 
{
	log_init(log_conf_dir.c_str(), log_conf_filename.c_str());
	log_info("%s", "welcome to thrift-test client ! :) ");
	sig_actions();


	CmdParser parser(argc, argv);

	/*
	parser.getNextPara();
	char* p = parser.getNextPara();
	if (p == NULL) {
		showHelp();
		return 0;
	} 

	p = parser.getNextPara();
	if (p == NULL) {
		log_error("second para is empty!");
		return 0;
	}
	*/
	char* p;
	if (argc == 1) {
		showHelp();
		return 0;
	} else if (argc == 2) {
		p = argv[1];
	} else {
		log_error("argv invalid!");
		return 0;
	}
	
	int cmd = atoi(p);
	string res;
	switch(cmd) {
		case 1:
			res = GetServiceList(parser);
			break;
		case 2:
			res = AddService(parser);
			break;
		case 3:
			res = FillData(parser);
			break;
		case 4:
			res = RequestTrigger(parser);
			break;
		default:
			showHelp();
			return 0;
	}
	cout << res << endl;	
	return 0;
}

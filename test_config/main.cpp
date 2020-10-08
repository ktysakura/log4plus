#include "log4cplus/logger.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/fileappender.h"
#include "log4cplus/layout.h"
#include "log4cplus/loggingmacros.h"
#include "log4cplus/configurator.h"
#include "log4cplus/ndc.h"
#include "log4cplus/helpers/loglog.h"
#include "Windows.h"

using namespace log4cplus;
using namespace log4cplus::helpers;

//链接WinSock库
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "log4cplusSD")
int main(int argc, char *argv[])
{
	//加载配置文件
	PropertyConfigurator::doConfigure("./test.cfg");
	Logger logger = Logger::getRoot();

	for (int i = 0; i < 3000; i++) {
		LOG4CPLUS_INFO(logger, "the loop time: " << i);

		//LOG宏的使用，输出字符串 puts
		LOG4CPLUS_DEBUG(logger, "This is the debug message");
		LOG4CPLUS_WARN(logger, "This is the warn message");
		LOG4CPLUS_ERROR(logger, "This is the error message");

		//LOG宏的使用，c++流语法
		LOG4CPLUS_DEBUG(logger, "this is a bool: " << true);
		LOG4CPLUS_INFO(logger, "this is a char: " << L'x');
		LOG4CPLUS_WARN(logger, "this is a int: " << 1000);
		LOG4CPLUS_FATAL(logger, "this is a double: " << 123.456);

		//LOG宏的使用，printf语法
		LOG4CPLUS_DEBUG_FMT(logger, "%d", 2000);
		LOG4CPLUS_WARN_FMT(logger, "%.3f", 34.56789);
		LOG4CPLUS_WARN_FMT(logger, "%c", L'a');
		LOG4CPLUS_DEBUG_FMT(logger, "%s", L"hello\n");
	}

	return 0;
}
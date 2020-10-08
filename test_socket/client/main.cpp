#include "log4cplus/logger.h"
#include "log4cplus/loggingmacros.h"
#include "log4cplus/socketappender.h"
#include "log4cplus/loglevel.h"
#include "log4cplus/tstring.h"
#include "log4cplus/thread/threads.h"
#include "log4cplus/helpers/loglog.h"
#include "log4cplus/configurator.h"
#include <iomanip>

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

//链接WinSock库
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "log4cplusSD")
int main(int argc, char *argv[])
{
	//SocketAppender不需要配置Layout，输出格式由服务端的Layout决定
	SharedObjectPtr<Appender> append(new SocketAppender("127.0.0.1", 9000, "local server"));
	Logger logger = Logger::getRoot();
	logger.addAppender(append);
	
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
	LOG4CPLUS_DEBUG_FMT(logger, "%s", L"hello");

	//这边很重要，要延时一下，不能提前结束客户端socket
	system("pause");

	return 0;
}
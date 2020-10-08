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

int main(int argc, char *argv[])
{
	//1. 创建一个滚动文件appender
	//默认最小的文件大小是200K，第3个参数为3，最多会有4个log文件，循环滚动
	SharedObjectPtr<Appender> append(new RollingFileAppender(L"./test.log", 200*1024, 3));

	//2. 创建一个pattern的layout
	tstring pattern = L"%D{%Y-%m-%d %H:%M:%S}---%b[%L]  - %m %n";
	std::auto_ptr<Layout> layout(new PatternLayout(pattern));

	//3. 把layout挂接到appender
	append->setLayout(layout);

	//4. 获取一个logger对象
	Logger logger = Logger::getInstance(L"test");

	//5. 把appender挂接到logger对象
	logger.addAppender(append);

	for (int i = 0; i < 3000; i++) {
		LOG4CPLUS_INFO(logger, L"the loop time: " << i);

		//LOG宏的使用，输出字符串 puts
		LOG4CPLUS_DEBUG(logger, L"This is the debug message");
		LOG4CPLUS_WARN(logger, L"This is the warn message");
		LOG4CPLUS_ERROR(logger, L"This is the error message");

		//LOG宏的使用，c++流语法
		LOG4CPLUS_DEBUG(logger, L"this is a bool: " << true);
		LOG4CPLUS_INFO(logger, L"this is a char: " << L'x');
		LOG4CPLUS_WARN(logger, L"this is a int: " << 1000);
		LOG4CPLUS_FATAL(logger, L"this is a double: " << 123.456);

		//LOG宏的使用，printf语法
		LOG4CPLUS_DEBUG_FMT(logger, L"%d", 2000);
		LOG4CPLUS_WARN_FMT(logger, L"%.3f", 34.56789);
		LOG4CPLUS_WARN_FMT(logger, L"%c", L'a');
		LOG4CPLUS_DEBUG_FMT(logger, L"%s", L"hello\n");
	}
	
	return 0;
}
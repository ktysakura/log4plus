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
	//1. 创建一个文件appender
	SharedObjectPtr<Appender> append(new FileAppender(L"./test.log"));
	SharedObjectPtr<Appender> append2(new ConsoleAppender());

	//2. 创建一个pattern的layout
	tstring pattern = L"%D{%Y-%m-%d %H:%M:%S}---%b[%L]  - %m %n";
	std::auto_ptr<Layout> layout(new PatternLayout(pattern));
	std::auto_ptr<Layout> layout2(new PatternLayout(pattern));

	//3. 把layout挂接到appender
	append->setLayout(layout);
	append2->setLayout(layout2);

	//4. 获取一个logger对象
	Logger logger = Logger::getInstance(L"test");

	//5. 把appender挂接到logger对象
	logger.addAppender(append);
	logger.addAppender(append2);

	//6. 设置logger的日志级别，大于该级别的都会输出
	logger.setLogLevel(ALL_LOG_LEVEL);

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
	LOG4CPLUS_DEBUG_FMT(logger, L"%s", L"hello");

	return 0;
}
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

//����WinSock��
#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char *argv[])
{
	//1. ����һ���ļ�appender
	SharedObjectPtr<Appender> append(new FileAppender(L"./test.log"));
	SharedObjectPtr<Appender> append2(new ConsoleAppender());

	//2. ����һ��pattern��layout
	tstring pattern = L"%D{%Y-%m-%d %H:%M:%S}---%b[%L]  - %m %n";
	std::auto_ptr<Layout> layout(new PatternLayout(pattern));
	std::auto_ptr<Layout> layout2(new PatternLayout(pattern));

	//3. ��layout�ҽӵ�appender
	append->setLayout(layout);
	append2->setLayout(layout2);

	//4. ��ȡһ��logger����
	Logger logger = Logger::getInstance(L"test");

	//5. ��appender�ҽӵ�logger����
	logger.addAppender(append);
	logger.addAppender(append2);

	//6. ����logger����־���𣬴��ڸü���Ķ������
	logger.setLogLevel(ALL_LOG_LEVEL);

	//LOG���ʹ�ã�����ַ��� puts
	LOG4CPLUS_DEBUG(logger, L"This is the debug message");
	LOG4CPLUS_WARN(logger, L"This is the warn message");
	LOG4CPLUS_ERROR(logger, L"This is the error message");

	//LOG���ʹ�ã�c++���﷨
	LOG4CPLUS_DEBUG(logger, L"this is a bool: " << true);
	LOG4CPLUS_INFO(logger, L"this is a char: " << L'x');
	LOG4CPLUS_WARN(logger, L"this is a int: " << 1000);
	LOG4CPLUS_FATAL(logger, L"this is a double: " << 123.456);

	//LOG���ʹ�ã�printf�﷨
	LOG4CPLUS_DEBUG_FMT(logger, L"%d", 2000);
	LOG4CPLUS_WARN_FMT(logger, L"%.3f", 34.56789);
	LOG4CPLUS_WARN_FMT(logger, L"%c", L'a');
	LOG4CPLUS_DEBUG_FMT(logger, L"%s", L"hello");

	return 0;
}
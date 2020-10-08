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
#pragma comment(lib, "log4cplusSD")
Logger logger;

//�߳�ִ�к���
static DWORD WINAPI threadProc1(LPVOID lpParam)
{
	//�̱߳�ʶ��
	NDCContextCreator ndc("thread1");

	for (int i = 0; i < 20; i++) {
		LOG4CPLUS_DEBUG_FMT(logger,"%s", "hello world 1");
	}
	return 0;
}

//�߳�ִ�к���
static DWORD WINAPI threadProc2(LPVOID lpParam)
{
	//�̱߳�ʶ��
	NDCContextCreator ndc("thread2");

	for (int i = 0; i < 20; i++) {
		LOG4CPLUS_DEBUG_FMT(logger, "%s", "hello world 2");
	}
	return 0;
}

int main(int argc, char *argv[])
{
	HANDLE hThread1, hThread2;

	//1. ����һ������̨appender
	SharedObjectPtr<Appender> append(new ConsoleAppender());

	//2. ����һ��pattern��layout
	//%x��������̱߳�ʶ���õģ�-7��ʾ����룬7���ַ������㲹�ո�
	tstring pattern = "%D{%Y-%m-%d %H:%M:%S}---%b[%L] - [%-7x] - %m %n";
	std::unique_ptr<Layout> layout(new PatternLayout(pattern));

	//3. ��layout�ҽӵ�appender
	append->setLayout(std::move(layout));

	//4. ��ȡһ��logger����
	logger = Logger::getInstance("test");

	//5. ��appender�ҽӵ�logger����
	logger.addAppender(append);

	//6. ����logger����־���𣬴��ڸü���Ķ������
	logger.setLogLevel(ALL_LOG_LEVEL);

	//���̱߳�ʶ��
	NDCContextCreator ndc("main");

	LOG4CPLUS_INFO(logger, "in main function");

	hThread1 = CreateThread(NULL, 0, threadProc1, NULL, 0, NULL);
	if (hThread1 == NULL) {
		LOG4CPLUS_ERROR(logger, "create thread1 error\n");
	}
	CloseHandle(hThread1);

	hThread2 = CreateThread(NULL, 0, threadProc2, NULL, 0, NULL);
	if (hThread2 == NULL) {
		LOG4CPLUS_ERROR(logger, L"create thread2 error\n");
	}
	CloseHandle(hThread2);

	for (int i = 0; i < 20; i++) {
		LOG4CPLUS_DEBUG_FMT(logger, "%s", "hello world 0");
	}

	return 0;
}
#include "log4cplus/config.hxx"
#include "log4cplus/configurator.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/socketappender.h"
#include "log4cplus/helpers/loglog.h"
#include "log4cplus/helpers/socket.h"
#include "log4cplus/thread/threads.h"
#include "log4cplus/spi/loggerimpl.h"
#include "log4cplus/spi/loggingevent.h"

#include <iostream>

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;
using namespace log4cplus::thread;

//链接WinSock库
#pragma comment(lib, "Ws2_32.lib")

//定义一个客户端类
class ClientThread : public AbstractThread
{
public:
	ClientThread(Socket cs) : clientsock(cs)
	{
		wcout << L"Received a client connection!!!!" << endl;
	}

	~ClientThread()
	{
		wcout << L"Client connection closed." << endl;
	}

	virtual void run();

private:
	Socket clientsock;
};

void ClientThread::run()
{
	while (1) {
		if (!clientsock.isOpen()) {
			return;
		}

		//分两步读
		//1. 读取一个报文长度
		SocketBuffer msgSizeBuffer(sizeof(unsigned int));
		bool ret = clientsock.read(msgSizeBuffer);
		if (!ret) {
			return;
		}

		//2. 
		unsigned int msgSize = msgSizeBuffer.readInt();
		SocketBuffer buffer(msgSize);
		if (!clientsock.read(buffer)) {
			return;
		}

		spi::InternalLoggingEvent event = readFromBuffer(buffer);
		Logger logger = Logger::getInstance(event.getLoggerName());
		logger.callAppenders(event);
	}
}

int main(int argc, char *argv[])
{
	//加载配置文件
	PropertyConfigurator::doConfigure(L"./test.cfg");
	
	//启动服务
	ServerSocket server(8988);

	while (1) {
		//监听新的客户端
		ClientThread *cthread = new ClientThread(server.accept());
		cthread->start();
	}

	return 0;
}
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

//����WinSock��
#pragma comment(lib, "Ws2_32.lib")

//����һ���ͻ�����
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

		//��������
		//1. ��ȡһ�����ĳ���
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
	//���������ļ�
	PropertyConfigurator::doConfigure(L"./test.cfg");
	
	//��������
	ServerSocket server(8988);

	while (1) {
		//�����µĿͻ���
		ClientThread *cthread = new ClientThread(server.accept());
		cthread->start();
	}

	return 0;
}
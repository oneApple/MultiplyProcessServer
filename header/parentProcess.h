/*
 * parentProcess.h
 *
 *  Created on: 2013-1-25
 *      Author: keym
 */

#ifndef PARENTPROCESS_H_
#define PARENTPROCESS_H_

#include<map>
#include"handleEpollSocket.h"
#include"childProcessInfo.h"
#include"globalDataControl.h"

class parentProcess : protected handleEpollSocket{
private:
	int _netListenfd;//接受客户端连接的socket
	int _devicefd;
	std::deque<int> _dnewConnectSocket;
	globalDataControl _cfdAndAlloc;
private:
	void initializeListenfd();
	void initializeChildProcessfd(int num);
	void acceptNewConnection(int newfd);
	void sendNewConnection(int sendfd);
public:
	const int GetFreeSockfd()
	{
		return this->_cfdAndAlloc.AllocFreeSockfd();
	}
	void relEpollSocket(int socket,PROCESSSTATE type);
	void InitializeManage(int num)throw(std::exception);
	void AddSocketToEpoll(int socket);
	void CommunicationHandle();
};

#endif /* PARENTPROCESS_H_ */

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

class parentProcess : private handleEpollSocket{
private:
	int _netListenfd;//接受客户端连接的socket
	std::map<int,bool> _mSocketAndAlloc;
	std::deque<int> _dnewConnectSocket;
private:
	void initializeListenfd();
	void initializeChildProcessfd(int num);
	void acceptNewConnection(int newfd);
	void sendNewConnection(int sendfd);
	void relEpollSocket(int socket,PROCESSSTATE type);
public:
	void InitializeManage(int num)throw(std::exception);
	void AddSocketToEpoll(int socket);
	void CommunicationHandle();
};

#endif /* PARENTPROCESS_H_ */

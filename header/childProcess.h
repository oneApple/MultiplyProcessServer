/*
 * childProcess.h
 *
 *  Created on: 2013-1-30
 *      Author: keym
 */

#ifndef CHILDPROCESS_H_
#define CHILDPROCESS_H_
#include"handleEpollSocket.h"

#include<assert.h>

class childProcess : protected handleEpollSocket{
private:
	int _parentSocket;
	int _clientSocket;
public:
	void acceptClientSocket();
	void AddEpollSocket(int socketfd)
	{
		handleEpollSocket::addEpollSocket(socketfd);
	}
	int  GetSocketfd(char pOrc)
	{
		switch(pOrc)
		{
		case 'p':
			return this->_parentSocket;
		case 'c':
			return this->_clientSocket;
		default:
			assert(1 == 0);
		}
	}
public:
	explicit childProcess(int parentfd):_parentSocket(parentfd){}
	void InitializeProcess();
	void CommunicateHandle();
};

#endif /* CHILDPROCESS_H_ */

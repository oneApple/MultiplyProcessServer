/*
 * childProcess.h
 *
 *  Created on: 2013-1-30
 *      Author: keym
 */

#ifndef CHILDPROCESS_H_
#define CHILDPROCESS_H_
#include"handleEpollSocket.h"

class childProcess : private handleEpollSocket{
private:
	int _parentSocket;
	int _clientSocket;
private:
	void acceptClientSocket();
public:
	explicit childProcess(int parentfd):_parentSocket(parentfd){}
    void InitializeProcess();
    void CommunicateHandle();
};

#endif /* CHILDPROCESS_H_ */

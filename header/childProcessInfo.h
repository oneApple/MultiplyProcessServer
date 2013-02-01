/*
 * childProcessInfo.h
 *
 *  Created on: 2013-1-24
 *      Author: keym
 */

#ifndef CHILDPROCESSINFO_H_
#define CHILDPROCESSINFO_H_

#include<signal.h>

#include<iostream>

enum PROCESSSTATE{INIT = 0,BUSY,ERR};

class childProcessInfo{
private:
	int _communicateSocket;
	PROCESSSTATE _processState;
	pid_t _processId;
public:
	explicit childProcessInfo(int socket,PROCESSSTATE state,pid_t pid)
	:_communicateSocket(socket),_processState(state),_processId(pid){}

	PROCESSSTATE GetProcessState(){return this->_processState;}
	void SetProcessState(PROCESSSTATE state){this->_processState = state;}
	int GetProcessSocket(){return this->_communicateSocket;}
	pid_t GetProcessPid(){return this->_processId;}
	//不要在析构或构造函数上使用一些可能产生错误的操作
};

#endif /* CHILDPROCESSINFO_H_ */

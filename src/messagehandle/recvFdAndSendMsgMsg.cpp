/*
 * handleReqSendfdMsg.cpp
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */
#include"childProcess.h"

#include"messagehandle/recvFdAndSendMsgMsg.h"
#include"commonfunction/netSocketFun.h"
#include<unistd.h>
commontype::headInfo *recvFdAndSendMsgMsg::packDataHead()
{
	childProcess *_tempuser = (childProcess *)this->_uperuser;
	_tempuser->acceptClientSocket();
	_tempuser->AddEpollSocket(_tempuser->GetSocketfd('c'));
	this->_sendSocketfd = _tempuser->GetSocketfd('c');

	commontype::headInfo *phead = new commontype::headInfo;
	phead->_size = this->_dataBodysize;
	phead->_type = magicnum::messagetype::CCMESSAGECC;
	return phead;
}

char *recvFdAndSendMsgMsg::packDataBody()
{
	int readbytes;
	char *readbuf = new char[this->_recvDatasize];
	if((readbytes=RepeatRecv(this->_recvSocketfd,readbuf,this->_recvDatasize)) < 0)
	{
		//这里可能是客户端关闭或出现错误
		return 0;
	}

	delete readbuf;
	char *buf = new char[sizeof(pid_t)];
	pid_t *pid = (pid_t*)buf;
	*pid = getpid();
	this->_dataBodysize = sizeof(pid_t);
	return buf;
}

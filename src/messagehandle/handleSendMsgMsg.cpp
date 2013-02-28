/*
 * handleSendMsgMsg.cpp
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */
#include"messagehandle/handleSendMsgMsg.h"
#include"commonfunction/netSocketFun.h"
#include<unistd.h>
commontype::headInfo *handleSendMsgMsg::packDataHead()
{
	commontype::headInfo *phead = new commontype::headInfo;
	phead->_size = this->_dataBodysize;
	phead->_type = magicnum::messagetype::CCMESSAGECC;
	return phead;
}

char *handleSendMsgMsg::packDataBody()
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


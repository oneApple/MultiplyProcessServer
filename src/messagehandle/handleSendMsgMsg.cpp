/*
 * handleSendMsgMsg.cpp
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */
#include"messagehandle/handleSendMsgMsg.h"
#include"commonfunction/netSocketFun.h"
#include<unistd.h>
void *handleSendMsgMsg::packDataHead()
{
	commontype::headInfo *phead = new commontype::headInfo;
	phead->_size = this->_dataBodysize;
	phead->_type = magicnum::messagetype::CCMESSAGECC;
	return phead;
}

void *handleSendMsgMsg::packDataBody()
{
	int readbytes;
	char *readbuf = new char[this->_recvDatasize];
	if((readbytes=RepeatRecv(this->_recvSocketfd,readbuf,this->_recvDatasize)) < 0)
	{
		//这里可能是客户端关闭或出现错误
		return 0;
	}
	delete readbuf;
	pid_t *pid = new pid_t;
	*pid = getpid();
	this->_dataBodysize = sizeof(pid_t);
	return pid;
}


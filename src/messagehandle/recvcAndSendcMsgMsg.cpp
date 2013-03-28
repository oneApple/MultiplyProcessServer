/*
 * handleSendMsgMsg.cpp
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */
#include"messagehandle/recvcAndSendcMsgMsg.h"
#include"commonfunction/netSocketFun.h"
#include<unistd.h>

#include<iostream>
#include<assert.h>
commontype::headInfo *recvcAndSendcMsgMsg::packDataHead()
{
	this->_sendSocketfd = this->_recvSocketfd;

	commontype::headInfo *phead = new commontype::headInfo;
	phead->_size = this->_dataBodysize;
	phead->_type = magicnum::messagetype::CCMESSAGECC;
	return phead;
}

char *recvcAndSendcMsgMsg::packDataBody()
{
	int readbytes;
	char *readbuf = new char[this->_recvDatasize];
	if((readbytes=RepeatRecv(this->_recvSocketfd,readbuf,this->_recvDatasize)) < 0)
	{
		//这里可能是客户端关闭或出现错误
		return 0;
	}
	pid_t *temp = (pid_t *)readbuf;
	assert(*temp == getpid());
	delete readbuf;
	char *buf = new char[sizeof(pid_t)];
	pid_t *pid = (pid_t*)buf;
	*pid = getpid();
	this->_dataBodysize = sizeof(pid_t);
	return buf;
}


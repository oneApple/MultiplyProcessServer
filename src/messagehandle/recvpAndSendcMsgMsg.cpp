/*
 * recvpAndSendcMsgMsg.cpp
 *
 *  Created on: Mar 28, 2013
 *      Author: keym
 */
#include"messagehandle/recvpAndSendcMsgMsg.h"
#include"commonfunction/netSocketFun.h"
#include"childProcess.h"
#include<unistd.h>

#include<iostream>
#include<assert.h>
void recvpAndSendcMsgMsg::packDataHead()
{
	this->_sendSocketfd = ((childProcess *)this->_uperuser)->GetSocketfd('c');
	this->phead->_size = this->_dataBodysize;
	this->phead->_type = magicnum::messagetype::CCMESSAGECC;
}

char *recvpAndSendcMsgMsg::packDataBody()
{
	int readbytes;
	char *readbuf = this->getfreemem(this->_recvDatasize);
	if((readbytes=RepeatRecv(this->_recvSocketfd,readbuf,this->_recvDatasize)) < 0)
	{
		//这里可能是客户端关闭或出现错误
		return 0;
	}
	this->releaseFreemem(readbuf);
	char *buf = this->getfreemem(sizeof(pid_t));
	pid_t *pid = (pid_t*)buf;
	*pid = getpid();
	this->_dataBodysize = sizeof(pid_t);
	return buf;
}



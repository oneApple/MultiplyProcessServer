/*
 * recvAlarmAndSendMsgMsg.cpp
 *
 *  Created on: Mar 28, 2013
 *      Author: keym
 */

#include"messagehandle/recvAlarmAndSendMsgMsg.h"
#include"commonfunction/netSocketFun.h"
#include"parentProcess.h"

#include<unistd.h>
#include<iostream>
#include<assert.h>
commontype::headInfo *recvAlarmAndSendMsgMsg::packDataHead()
{
	int _allocfd = ((parentProcess *)this->_uperuser)->GetFreeSockfd();
	if(_allocfd == magicnum::FAILIED)
	{
		return NULL;
	}
	this->_sendSocketfd = _allocfd;

	commontype::headInfo *phead = new commontype::headInfo;
	phead->_size = this->_dataBodysize;
	phead->_type = magicnum::messagetype::PCMESSAGEPC;
	return phead;
}

char *recvAlarmAndSendMsgMsg::packDataBody()
{
	char *buf = new char[sizeof(pid_t)];
	pid_t *pid = (pid_t*)buf;
	*pid = getpid();
	this->_dataBodysize = sizeof(pid_t);
	return buf;
}


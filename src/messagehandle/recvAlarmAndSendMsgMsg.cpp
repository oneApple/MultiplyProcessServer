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
void recvAlarmAndSendMsgMsg::packDataHead()
{
	int _allocfd = ((parentProcess *)this->_uperuser)->GetFreeSockfd();
	if(_allocfd == magicnum::FAILIED)
	{
		this->phead->_type = magicnum::messagetype::NULLTYPENUM;
		return;
	}
	this->_sendSocketfd = _allocfd;

	this->phead->_size = this->_dataBodysize;
	this->phead->_type = magicnum::messagetype::PCMESSAGEPC;
}

char *recvAlarmAndSendMsgMsg::packDataBody()
{
	char *buf = this->getfreemem(sizeof(pid_t));
	pid_t *pid = (pid_t*)buf;
	*pid = getpid();
	this->_dataBodysize = sizeof(pid_t);
	return buf;
}


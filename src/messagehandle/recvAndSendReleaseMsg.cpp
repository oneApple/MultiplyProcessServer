/*
 * recvAndSendReleaseMsg.cpp
 *
 *  Created on: Mar 28, 2013
 *      Author: keym
 */

#include"messagehandle/recvAndSendReleaseMsg.h"
#include"commonfunction/netSocketFun.h"
#include"childProcess.h"
#include<unistd.h>

#include<iostream>
#include<assert.h>
void recvAndSendReleaseMsg::packDataHead()
{

	this->_sendSocketfd = ((childProcess *)this->_uperuser)->GetSocketfd('p');
	this->phead->_size = this->_dataBodysize;
	this->phead->_type = magicnum::messagetype::CPRELEASECP;
}

char *recvAndSendReleaseMsg::packDataBody()
{
	int readbytes;
	char *readbuf = this->getfreemem(this->_recvDatasize);
	if((readbytes=RepeatRecv(this->_recvSocketfd,readbuf,this->_recvDatasize)) < 0)
	{
		//这里可能是客户端关闭或出现错误
		return 0;
	}
	pid_t *temp = (pid_t *)readbuf;
	assert(*temp == getpid());
	this->releaseFreemem(readbuf);
	this->_dataBodysize = 0;
	return NULL;
}


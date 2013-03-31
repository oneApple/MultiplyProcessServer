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
void recvcAndSendcMsgMsg::packDataHead()
{
	this->_sendSocketfd = this->_recvSocketfd;

	this->phead->_size = this->_dataBodysize;
	this->phead->_type = magicnum::messagetype::CCRELEASECC;

}

char *recvcAndSendcMsgMsg::packDataBody()
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
	char *buf = this->getfreemem(sizeof(pid_t));
	pid_t *pid = (pid_t*)buf;
	*pid = getpid();
	this->_dataBodysize = sizeof(pid_t);
	return buf;
}


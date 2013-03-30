/*
 * handleSendfdMsg.cpp
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */
#include"messagehandle/SendNewfdMsg.h"
#include<unistd.h>

void SendNewfdMsg::packDataHead()
{
	 this->_sendSocketfd = this->_recvSocketfd;
     this->phead->_size = this->_dataBodysize;
     this->phead->_type = magicnum::messagetype::PCREQSENDFD;
}

char *SendNewfdMsg::packDataBody()
{
	char *buf = new char[sizeof(pid_t)];
	pid_t *pid = (pid_t*)buf;
    *pid = getpid();
    this->_dataBodysize = sizeof(pid_t);
    return buf;
}

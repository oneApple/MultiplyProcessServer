/*
 * handleSendfdMsg.cpp
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */
#include"messagehandle/SendNewfdMsg.h"
#include<unistd.h>

commontype::headInfo *SendNewfdMsg::packDataHead()
{
	 this->_sendSocketfd = this->_recvSocketfd;

     commontype::headInfo *phead = new commontype::headInfo;
     phead->_size = this->_dataBodysize;
     phead->_type = magicnum::messagetype::PCREQSENDFD;
     return phead;
}

char *SendNewfdMsg::packDataBody()
{
	char *buf = new char[sizeof(pid_t)];
	pid_t *pid = (pid_t*)buf;
    *pid = getpid();
    this->_dataBodysize = sizeof(pid_t);
    return buf;
}

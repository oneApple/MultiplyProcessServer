/*
 * handleSendfdMsg.cpp
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */
#include"messagehandle/handleSendfdMsg.h"
#include<unistd.h>

commontype::headInfo *handleSendfdMsg::packDataHead()
{
     commontype::headInfo *phead = new commontype::headInfo;
     phead->_size = this->_dataBodysize;
     phead->_type = magicnum::messagetype::PCREQSENDFD;
     return phead;
}

char *handleSendfdMsg::packDataBody()
{
	char *buf = new char[sizeof(pid_t)];
	pid_t *pid = (pid_t*)buf;
    *pid = getpid();
    this->_dataBodysize = sizeof(pid_t);
    return buf;
}

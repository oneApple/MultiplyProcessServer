/*
 * handleSendfdMsg.cpp
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */
#include"messagehandle/handleSendfdMsg.h"
#include<unistd.h>

void *handleSendfdMsg::packDataHead()
{
     commontype::headInfo *phead = new commontype::headInfo;
     phead->_size = this->_dataBodysize;
     phead->_type = magicnum::messagetype::PCREQSENDFD;
     return phead;
}

void *handleSendfdMsg::packDataBody()
{
	pid_t *pid = new pid_t;
    *pid = getpid();
    this->_dataBodysize = sizeof(pid_t);
    return pid;
}

/*
 * sendAlarmMsg.cpp
 *
 *  Created on: Mar 28, 2013
 *      Author: keym
 */

#include"messagehandle/sendAlarmMsg.h"
#include"deviceProcess.h"
#include<unistd.h>

void sendAlarmMsg::packDataHead()
{
	 deviceProcess *_tempuser = (deviceProcess *)this->_uperuser;
	 this->_sendSocketfd = _tempuser->GetParentSocketfd();

     this->phead->_size = this->_dataBodysize;
     this->phead->_type =magicnum::messagetype::DPSENDALARM;
}

char *sendAlarmMsg::packDataBody()
{
    this->_dataBodysize = 0;
    return NULL;
}


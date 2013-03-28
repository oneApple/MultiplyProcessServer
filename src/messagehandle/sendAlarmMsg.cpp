/*
 * sendAlarmMsg.cpp
 *
 *  Created on: Mar 28, 2013
 *      Author: keym
 */

#include"messagehandle/sendAlarmMsg.h"
#include"deviceProcess.h"
#include<unistd.h>

commontype::headInfo *sendAlarmMsg::packDataHead()
{
	 deviceProcess *_tempuser = (deviceProcess *)this->_uperuser;
	 this->_sendSocketfd = _tempuser->GetParentSocketfd();

     commontype::headInfo *phead = new commontype::headInfo;
     phead->_size = this->_dataBodysize;
     phead->_type =magicnum::messagetype::DPSENDALARM;
     return phead;
}

char *sendAlarmMsg::packDataBody()
{
    this->_dataBodysize = 0;
    return NULL;
}


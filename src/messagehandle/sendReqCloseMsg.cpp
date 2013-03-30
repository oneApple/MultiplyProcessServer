/*
 * handleReqCloseMsg.cpp
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */
#include"messagehandle/sendReqCloseMsg.h"
#include"childProcess.h"
#include<unistd.h>

void sendReqCloseMsg::packDataHead()
{
	childProcess *_tempuser = (childProcess *)this->_uperuser;
	this->_sendSocketfd = _tempuser->GetSocketfd('p');
	close(_tempuser->GetSocketfd('c'));
	this->phead->_size = this->_dataBodysize;
	this->phead->_type = magicnum::messagetype::CPREQCLOSED;
}

char *sendReqCloseMsg::packDataBody()
{
	this->_dataBodysize = 0;
	return 0;
}

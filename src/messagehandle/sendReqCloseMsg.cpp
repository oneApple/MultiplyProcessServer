/*
 * handleReqCloseMsg.cpp
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */
#include"messagehandle/sendReqCloseMsg.h"
#include"childProcess.h"
#include<unistd.h>

commontype::headInfo *sendReqCloseMsg::packDataHead()
{
    childProcess *_tempuser = (childProcess *)this->_uperuser;
	this->_sendSocketfd = _tempuser->GetSocketfd('p');
	close(_tempuser->GetSocketfd('c'));

	 commontype::headInfo *phead = new commontype::headInfo;
     phead->_size = this->_dataBodysize;
     phead->_type = magicnum::messagetype::CPREQCLOSED;
     return phead;
}

char *sendReqCloseMsg::packDataBody()
{
    this->_dataBodysize = 0;
    return 0;
}

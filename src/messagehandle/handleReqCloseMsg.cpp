/*
 * handleReqCloseMsg.cpp
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */
#include"messagehandle/handleReqCloseMsg.h"
#include"childProcess.h"
#include<unistd.h>

commontype::headInfo *handleReqCloseMsg::packDataHead()
{
    childProcess *_tempuser = (childProcess *)this->_uperuser;
	this->_sendSocketfd = _tempuser->GetSocketfd('p');

	 commontype::headInfo *phead = new commontype::headInfo;
     phead->_size = this->_dataBodysize;
     phead->_type = magicnum::messagetype::CPREQCLOSED;
     return phead;
}

char *handleReqCloseMsg::packDataBody()
{
    this->_dataBodysize = 0;
    return 0;
}

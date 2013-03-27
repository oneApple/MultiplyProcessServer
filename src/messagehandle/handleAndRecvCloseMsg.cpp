/*
 * handleAndRecvCloseMsg.cpp
 *
 *  Created on: Mar 27, 2013
 *      Author: keym
 */

#include"messagehandle/handleAndRecvCloseMsg.h"
#include"parentProcess.h"
#include<unistd.h>

commontype::headInfo *handleAndRecvCloseMsg::packDataHead()
{
	parentProcess *_tempuser = (parentProcess *)this->_uperuser;
    _tempuser->relEpollSocket(this->_recvSocketfd,INIT);
    return NULL;
}

char *handleAndRecvCloseMsg::packDataBody()
{
    this->_dataBodysize = 0;
    return 0;
}

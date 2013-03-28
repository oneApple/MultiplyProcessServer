/*
 * recvAndHandleReleaseMsg.cpp
 *
 *  Created on: Mar 28, 2013
 *      Author: keym
 */

#include"messagehandle/recvAndHandleReleaseMsg.h"
#include"commonfunction/netSocketFun.h"
#include"parentProcess.h"

#include<unistd.h>
#include<iostream>
#include<assert.h>

commontype::headInfo *recvAndHandleReleaseMsg::packDataHead()
{
	((parentProcess *)this->_uperuser)->ReleaseSockfd(this->_recvSocketfd);
	return NULL;
}

char *recvAndHandleReleaseMsg::packDataBody()
{
	this->_dataBodysize = 0;
	return NULL;
}


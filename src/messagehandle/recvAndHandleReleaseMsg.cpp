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

void recvAndHandleReleaseMsg::packDataHead()
{
	((parentProcess *)this->_uperuser)->ReleaseSockfd(this->_recvSocketfd);
	this->phead->_type = magicnum::messagetype::NULLTYPENUM;
}

char *recvAndHandleReleaseMsg::packDataBody()
{
	this->_dataBodysize = 0;
	return NULL;
}


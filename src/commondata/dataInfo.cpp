/*
 * dataInfo.cpp
 *
 *  Created on: 2013-3-30
 *      Author: keym
 */
#include"commondata/dataInfo.h"

#include<string.h>

void dataInfo::PackMsg(size_t datasize,char *phead,char *pbody)
{
	this->_pdata = new char[sizeof(commontype::headInfo) + datasize];
	memcpy(this->_pdata,phead,sizeof(commontype::headInfo));
	memset(phead,0,sizeof(commontype::headInfo));
	if(datasize != 0)
	{
		memcpy(this->_pdata + sizeof(commontype::headInfo),pbody,datasize);
		delete []pbody;
	}
	this->_size = sizeof(commontype::headInfo) + datasize;
}

/*
 * messageHandleInterface.h
 *
 *  Created on: 2013-1-31
 *      Author: keym
 */

#ifndef MESSAGEHANDLEINTERFACE_H_
#define MESSAGEHANDLEINTERFACE_H_
#include"commondata/commontype.h"
#include"commondata/magicNum.h"
#include"commonfunction/netSocketFun.h"
#include"../handleEpollSocket.h"
#include<string.h>
//所有信息处理类的父类
class messageHandleInterface{
protected:
	unsigned _dataBodysize;
	unsigned _recvDatasize;
	unsigned _recvDatatype;
	void *_uperuser;
	int _recvSocketfd;
	int _sendSocketfd;
protected:
	messageHandleInterface(unsigned type):_recvDatatype(type),_uperuser(NULL){}
	virtual commontype::headInfo *packDataHead() = 0;
	virtual char *packDataBody() = 0;
	void *mergeDataHeadAndBody()
	{
		commontype::dataInfo *pdataInfo = new commontype::dataInfo;
		pdataInfo->_type = this->_recvDatatype;
		char *pbody = this->packDataBody();//顺序不能换
		commontype::headInfo *phead = this->packDataHead();

		pdataInfo->_pdata = new char[sizeof(commontype::headInfo) + this->_dataBodysize];
		memcpy(pdataInfo->_pdata,phead,sizeof(commontype::headInfo));
		delete phead;
		if(this->_dataBodysize != 0)
		{
			memcpy(pdataInfo->_pdata + sizeof(commontype::headInfo),pbody,this->_dataBodysize);
			delete []pbody;
		}
		pdataInfo->_size = sizeof(commontype::headInfo) + this->_dataBodysize;

		handleEpollSocket *_tempuser = (handleEpollSocket *)this->_uperuser;
		_tempuser->packData(pdataInfo);
		_tempuser->modEpollSocket(this->_sendSocketfd,true);
		return pdataInfo;
	}
public:
	void *HandleMsg(unsigned size,int recvfd,void *uperuser)
	{
		this->_recvDatasize = size;
		this->_recvSocketfd = recvfd;
		this->_uperuser = uperuser;
		return mergeDataHeadAndBody();
	}
};

#endif /* MESSAGEHANDLEINTERFACE_H_ */

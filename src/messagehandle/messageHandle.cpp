/*
 * messageHandle.cpp
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */
#include"messagehandle/messageHandle.h"
#include"commondata/magicNum.h"
#include"messagehandle/handleSendfdMsg.h"
#include"messagehandle/handleReqSendfdMsg.h"
#include"messagehandle/handleSendMsgMsg.h"
#include"messagehandle/handleReqCloseMsg.h"

#include<assert.h>
messageHandle* messageHandle::_singleInstance = NULL;

messageHandle::messageHandle()
{
	this->_mmsgHandle[magicnum::messagetype::NULLSENDFDT] = new handleSendfdMsg;
	this->_mmsgHandle[magicnum::messagetype::PCREQSENDFD] = new handleReqSendfdMsg;
	this->_mmsgHandle[magicnum::messagetype::CCMESSAGECC] = new handleSendMsgMsg;
	this->_mmsgHandle[magicnum::messagetype::CPREQCLOSED] = new handleReqCloseMsg;
}
void *messageHandle::msgHandle(void *recvbuf,int recvfd)
{
	commontype::headInfo *phead = (commontype::headInfo*)recvbuf;
	messageHandleInterface *_instance = this->getMsgHandleInstance(phead->_type);
	return _instance->HandleMsg(phead->_size,recvfd);
}

messageHandleInterface *messageHandle::getMsgHandleInstance(unsigned type)
{
	std::map<unsigned,messageHandleInterface*>::iterator _iter = this->_mmsgHandle.find(type);
	assert(_iter != this->_mmsgHandle.end());
	return _iter->second;
}

messageHandle *messageHandle::getInstance()
{
	if(messageHandle::_singleInstance == NULL)
	{
		messageHandle::_singleInstance = new messageHandle;
	}
	return messageHandle::_singleInstance;
}

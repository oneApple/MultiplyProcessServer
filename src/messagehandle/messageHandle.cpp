/*
 * messageHandle.cpp
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */
#include"messagehandle/messageHandle.h"
#include"commondata/magicNum.h"
#include"messagehandle/SendNewfdMsg.h"
#include"messagehandle/recvNewFdMsg.h"
#include"messagehandle/recvcAndSendcMsgMsg.h"
#include"messagehandle/sendReqCloseMsg.h"
#include"messagehandle/handleAndRecvCloseMsg.h"
#include"messagehandle/sendAlarmMsg.h"
#include"messagehandle/recvAlarmAndSendMsgMsg.h"
#include"messagehandle/recvpAndSendcMsgMsg.h"


#include<assert.h>
messageHandle* messageHandle::_singleInstance = NULL;

messageHandle::messageHandle()
{
	this->_mmsgHandle[magicnum::messagetype::NULLSENDFDT] = new SendNewfdMsg;
	this->_mmsgHandle[magicnum::messagetype::PCREQSENDFD] = new recvNewFdMsg;
	this->_mmsgHandle[magicnum::messagetype::CCMESSAGECC] = new recvcAndSendcMsgMsg;
	this->_mmsgHandle[magicnum::messagetype::CCREQCLOSED] = new sendReqCloseMsg;
	this->_mmsgHandle[magicnum::messagetype::CPREQCLOSED] = new handleAndRecvCloseMsg;
	this->_mmsgHandle[magicnum::messagetype::NULLSENDALA] = new sendAlarmMsg;
	this->_mmsgHandle[magicnum::messagetype::DPSENDALARM] = new recvAlarmAndSendMsgMsg;
	this->_mmsgHandle[magicnum::messagetype::PCMESSAGEPC] = new recvpAndSendcMsgMsg;


}

void messageHandle::msgHandle(void *recvbuf,int recvfd,void *uperuser)
{
	commontype::headInfo *phead = (commontype::headInfo*)recvbuf;
	messageHandleInterface *_instance = this->getMsgHandleInstance(phead->_type);
	_instance->HandleMsg(phead->_size,recvfd,uperuser);
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

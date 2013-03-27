/*
 * handleReqSendfdMsg.h
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */

#ifndef RECVFDANDSENDMSGMSG_H_
#define RECVFDANDSENDMSGMSG_H_
#include"messageHandleInterface.h"
class recvFdAndSendMsgMsg : public messageHandleInterface{
private:
	virtual commontype::headInfo *packDataHead();
	virtual char *packDataBody();
public:
	recvFdAndSendMsgMsg():messageHandleInterface(magicnum::messagetype::PCREQSENDFD){}
};

#endif /* HANDLEREQSENDFDMSG_H_ */

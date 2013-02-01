/*
 * handleSendMsgMsg.h
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */

#ifndef HANDLESENDMSGMSG_H_
#define HANDLESENDMSGMSG_H_
#include"messageHandleInterface.h"
class handleSendMsgMsg : public messageHandleInterface{
private:
	virtual void *packDataHead();
	virtual void *packDataBody();
public:
	handleSendMsgMsg():messageHandleInterface(magicnum::messagetype::CCMESSAGECC){}
};

#endif /* HANDLESENDMSGMSG_H_ */

/*
 * handleSendMsgMsg.h
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */

#ifndef RECVCANDSENDCMSGMSG_H_
#define RECVCANDSENDCMSGMSG_H_

#include"messageHandleInterface.h"
class recvcAndSendcMsgMsg : public messageHandleInterface{
private:
	virtual void packDataHead();
	virtual char *packDataBody();
public:
	recvcAndSendcMsgMsg():messageHandleInterface(){}
};

#endif /* RECVCANDSENDCMSGMSG_H_ */

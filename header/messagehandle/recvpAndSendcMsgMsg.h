/*
 * recvpAndSendcMsgMsg.h
 *
 *  Created on: Mar 28, 2013
 *      Author: keym
 */

#ifndef RECVPANDSENDCMSGMSG_H_
#define RECVPANDSENDCMSGMSG_H_

#include"messageHandleInterface.h"
class recvpAndSendcMsgMsg : public messageHandleInterface{
private:
	virtual commontype::headInfo *packDataHead();
	virtual char *packDataBody();
public:
	recvpAndSendcMsgMsg():messageHandleInterface(){}
};

#endif /* RECVPANDSENDCMSGMSG_H_ */

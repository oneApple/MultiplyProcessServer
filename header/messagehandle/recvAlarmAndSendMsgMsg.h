/*
 * recvAlarmAndSendMsgMsg.h
 *
 *  Created on: Mar 28, 2013
 *      Author: keym
 */

#ifndef RECVALARMANDSENDMSGMSG_H_
#define RECVALARMANDSENDMSGMSG_H_

#include"messageHandleInterface.h"
class recvAlarmAndSendMsgMsg : public messageHandleInterface{
private:
	virtual commontype::headInfo *packDataHead();
	virtual char *packDataBody();
public:
	recvAlarmAndSendMsgMsg():messageHandleInterface(){}
};

#endif /* RECVALARMANDSENDMSGMSG_H_ */

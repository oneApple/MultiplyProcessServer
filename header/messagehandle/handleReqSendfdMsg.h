/*
 * handleReqSendfdMsg.h
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */

#ifndef HANDLEREQSENDFDMSG_H_
#define HANDLEREQSENDFDMSG_H_
#include"messageHandleInterface.h"
class handleReqSendfdMsg : public messageHandleInterface{
private:
	virtual void *packDataHead();
	virtual void *packDataBody();
public:
	handleReqSendfdMsg():messageHandleInterface(magicnum::messagetype::PCREQSENDFD){}
};

#endif /* HANDLEREQSENDFDMSG_H_ */

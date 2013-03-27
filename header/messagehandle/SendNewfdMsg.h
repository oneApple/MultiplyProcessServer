/*
 * handleSendfdMsg.h
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */

#ifndef SENDNEWFDMSG_H_
#define SENDNEWFDMSG_H_
#include"messageHandleInterface.h"
class SendNewfdMsg : public messageHandleInterface{
private:
	virtual commontype::headInfo *packDataHead();
	virtual char *packDataBody();
public:
	SendNewfdMsg():messageHandleInterface(magicnum::messagetype::NULLSENDFDT){}
};

#endif /* HANDLESENDFDMSG_H_ */

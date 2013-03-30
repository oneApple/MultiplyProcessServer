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
	virtual void packDataHead();
	virtual char *packDataBody();
public:
	SendNewfdMsg():messageHandleInterface(){}
};

#endif /* HANDLESENDFDMSG_H_ */

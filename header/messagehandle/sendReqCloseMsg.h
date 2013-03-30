/*
 * handleReqCloseMsg.h
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */

#ifndef SENDREQCLOSEMSG_H_
#define SENDREQCLOSEMSG_H_
#include"messageHandleInterface.h"
class sendReqCloseMsg : public messageHandleInterface{
private:
	virtual void packDataHead();
	virtual char *packDataBody();
public:
	sendReqCloseMsg():messageHandleInterface(){}
};

#endif /* HANDLEREQCLOSEMSG_H_ */

/*
 * handleReqCloseMsg.h
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */

#ifndef HANDLEREQCLOSEMSG_H_
#define HANDLEREQCLOSEMSG_H_
#include"messageHandleInterface.h"
class handleReqCloseMsg : public messageHandleInterface{
private:
	virtual void *packDataHead();
	virtual void *packDataBody();
public:
	handleReqCloseMsg():messageHandleInterface(magicnum::messagetype::CPREQCLOSED){}
};

#endif /* HANDLEREQCLOSEMSG_H_ */

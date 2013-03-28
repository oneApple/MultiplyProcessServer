/*
 * handleAndRecvCloseMsg.h
 *
 *  Created on: Mar 27, 2013
 *      Author: keym
 */

#ifndef HANDLEANDRECVCLOSEMSG_H_
#define HANDLEANDRECVCLOSEMSG_H_

#include"messageHandleInterface.h"
class handleAndRecvCloseMsg : public messageHandleInterface{
private:
	virtual commontype::headInfo *packDataHead();
	virtual char *packDataBody();
public:
	handleAndRecvCloseMsg():messageHandleInterface(){}
};

#endif /* HANDLEANDRECVCLOSEMSG_H_ */

/*
 * recvAndSendReleaseMsg.h
 *
 *  Created on: Mar 28, 2013
 *      Author: keym
 */

#ifndef RECVANDSENDRELEASEMSG_H_
#define RECVANDSENDRELEASEMSG_H_

#include"messageHandleInterface.h"
class recvAndSendReleaseMsg : public messageHandleInterface{
private:
	virtual commontype::headInfo *packDataHead();
	virtual char *packDataBody();
public:
	recvAndSendReleaseMsg():messageHandleInterface(){}
};

#endif /* RECVANDSENDRELEASEMSG_H_ */

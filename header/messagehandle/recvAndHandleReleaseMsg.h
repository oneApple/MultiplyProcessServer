/*
 * recvAndHandleReleaseMsg.h
 *
 *  Created on: Mar 28, 2013
 *      Author: keym
 */

#ifndef RECVANDHANDLERELEASEMSG_H_
#define RECVANDHANDLERELEASEMSG_H_

#include"messageHandleInterface.h"
class recvAndHandleReleaseMsg : public messageHandleInterface{
private:
	virtual commontype::headInfo *packDataHead();
	virtual char *packDataBody();
public:
	recvAndHandleReleaseMsg():messageHandleInterface(){}
};

#endif /* RECVANDHANDLERELEASEMSG_H_ */

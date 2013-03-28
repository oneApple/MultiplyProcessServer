/*
 * sendAlarmMsg.h
 *
 *  Created on: Mar 28, 2013
 *      Author: keym
 */

#ifndef SENDALARMMSG_H_
#define SENDALARMMSG_H_

#include"messageHandleInterface.h"
class sendAlarmMsg : public messageHandleInterface{
private:
	virtual commontype::headInfo *packDataHead();
	virtual char *packDataBody();
public:
	sendAlarmMsg():messageHandleInterface(){}
};

#endif /* SENDALARMMSG_H_ */

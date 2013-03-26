/*
 * handleEpollSocket.h
 *
 *  Created on: 2013-1-30
 *      Author: keym
 */

#ifndef HANDLEEPOLLSOCKET_H_
#define HANDLEEPOLLSOCKET_H_

#include<i386-linux-gnu/sys/epoll.h>

#include"commonfunction/localSocketFun.h"
#include"commonfunction/netSocketFun.h"
#include"commondata/magicNum.h"
#include"commondata/commontype.h"
#include<unistd.h>
#include<errno.h>

#include<deque>

class handleEpollSocket{
protected:
	int _epfd;
	unsigned _maxNumOfEpollfd;
	std::deque<commontype::dataInfo*> _ddataToSend;
private:
	void getEpollFdlimit();
	void createEpollfd();
protected:
	handleEpollSocket():_maxNumOfEpollfd(magicnum::processmanage::MAXNUMPROCESS){}
	void initializeEpoll();
	void addEpollSocket(int fd);
	void delEpollSocket(int fd);
	void modEpollSocket(int fd,bool rOrw);
protected:
	void packData(void *pdata);
	unsigned sendData(int socket);
};

#endif /* HANDLEEPOLLSOCKET_H_ */

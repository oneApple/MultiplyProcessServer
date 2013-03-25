/*
 * handleEpollSocket.cpp
 *
 *  Created on: 2013-1-30
 *      Author: keym
 */
#include<sys/resource.h>
#include<sys/socket.h>
#include<unistd.h>
#include<exception>
#include<iostream>
#include<stdio.h>
#include"handleEpollSocket.h"
#include"commondata/commontype.h"

void handleEpollSocket::getEpollFdlimit()
{
	rlimit limit;
	getrlimit(RLIMIT_FSIZE,&limit);
	if(limit.rlim_cur > magicnum::processmanage::MAXNUMPROCESS)
	{
		this->_maxNumOfEpollfd = limit.rlim_cur;
	}
	this->_maxNumOfEpollfd = 2048;
	//描述符数目不能太大，有限制
}

void handleEpollSocket::createEpollfd()
{
	if((this->_epfd=epoll_create(this->_maxNumOfEpollfd))<0)
	{
		perror("epoll_create:");
		std::cerr<<"parentProcess::initializeListenfdAndEpollfd:epoll_create"<<this->_maxNumOfEpollfd<<std::endl;
		throw std::exception();
	}
}

void handleEpollSocket::initializeEpoll()
{
	getEpollFdlimit();
	createEpollfd();
}

void handleEpollSocket::addEpollSocket(int fd)
{
	if(SetSocketNonblocking(fd) == magicnum::FAILIED)
	{
		std::cerr<<"parentProcess::initializeListenfdAndEpollfd:SetSocketNonblocking"<<std::endl;
		throw std::exception();
	}
	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=EPOLLIN|EPOLLET;
	epoll_ctl(_epfd,EPOLL_CTL_ADD,fd,&ev);
}

void handleEpollSocket::delEpollSocket(int fd)
{
	close(fd);
	epoll_ctl(_epfd,EPOLL_CTL_DEL,fd,NULL);
}

void handleEpollSocket::modEpollSocket(int fd,bool rTow)
{
	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=EPOLLIN|EPOLLET;
	if(rTow)
	{
		ev.events=EPOLLOUT|EPOLLET;
	}
	epoll_ctl(_epfd,EPOLL_CTL_MOD,fd,&ev);
}

void handleEpollSocket::packData(void *pdata)
{
	this->_ddataToSend.push_back((commontype::dataInfo*)pdata);
}

unsigned handleEpollSocket::sendData(int sendfd)
{
	commontype::dataInfo *pdataInfo = this->_ddataToSend[0];
	this->_ddataToSend.pop_front();
	unsigned _type = magicnum::messagetype::NULLTYPENUM;
	if(RepeatSend(sendfd,(char*)pdataInfo->_pdata,pdataInfo->_size) != magicnum::FAILIED)
	{
		_type = pdataInfo->_type;
	}
	delete pdataInfo;
	return _type;
}

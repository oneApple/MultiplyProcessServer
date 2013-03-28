/*
 * deviceProcess.cpp
 *
 *  Created on: Mar 27, 2013
 *      Author: keym
 */

#include"deviceProcess.h"
#include"commondata/magicNum.h"
#include"messagehandle/messageHandle.h"


#include<exception>
#include<arpa/inet.h>
#include<string.h>
#include<exception>
#include<iostream>
#include<assert.h>
#include<stdio.h>

deviceProcess *deviceProcess::_singleInstance = NULL;
static void packSendAlarmMsg(void *buffer);

void deviceProcess::initializeListenfd()
{
	handleEpollSocket::initializeEpoll();

	if((this->_netListenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		std::cerr<<"parentProcess::initializeListenfdAndEpollfd:socket"<<std::endl;
		throw std::exception();
	}
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(magicnum::deviceprocess::LISTENPORT);
	addr.sin_addr.s_addr=INADDR_ANY;

	if(bind(this->_netListenfd,(struct sockaddr*)&addr,sizeof(addr))<0)
	{
		perror("bind:");
		std::cerr<<"parentProcess::initializeListenfdAndEpollfd:bind"<<std::endl;
		throw std::exception();
	}
	if(ListenAndSetBlockNum(this->_netListenfd,magicnum::parentprocess::LISTNEPORT) == magicnum::FAILIED)
	{
		std::cerr<<"parentProcess::initializeListenfdAndEpollfd:ListenAndSetBlockNum"<<std::endl;
		throw std::exception();
	}
	handleEpollSocket::addEpollSocket(this->_netListenfd);
}

int deviceProcess::GetSocketfdAndRun()
{
	pid_t pid;
	int sockfd[2];
	socketpair(AF_LOCAL,SOCK_STREAM,0,sockfd);
	if((pid = fork()) > 0)
	{
		close(sockfd[1]);
		return sockfd[0];
	}
	//client
	close(sockfd[0]);
	handleEpollSocket::addEpollSocket(sockfd[1]);
	this->_parentfd = sockfd[1];
	this->CommunicationHandle();
	assert(1 == 0);
	std::cerr<<"processManage::createSingleProcess:assert"<<std::endl;
	throw std::exception();
}

void deviceProcess::CommunicationHandle()
{

	struct epoll_event events[this->_maxNumOfEpollfd + 1];
	std::deque<pid_t*> _dPid;
	int connfd;
	std::deque<int> newcondeque;
	for(;;)
	{
		int nfds;
		if((nfds=epoll_wait(_epfd,events,this->_maxNumOfEpollfd,magicnum::parentprocess::EPOLLTIMEOUT)) <= 0)
		{
			if (errno != EINTR)
			{
				std::cerr<<"parentProcess::CommunicationHandle:epoll_wait"<<std::endl;
				throw std::exception();
			}
			continue;
		}
		int i;
		for(i=0;i<nfds;i++)
		{
			if(events[i].data.fd == this->_netListenfd)
			{
				struct sockaddr_in clientaddr;
				socklen_t clilen = sizeof(clientaddr);
				if((connfd=accept(this->_netListenfd,(struct sockaddr*)&clientaddr,&clilen))<0)
				{
					if(errno == EINTR){continue;}
					std::cerr<<"parentProcess::CommunicationHandle:accept"<<std::endl;
					throw std::exception();
				}
                char readbuf[magicnum::MSGHEADSIZE];
                packSendAlarmMsg(readbuf);
				messageHandle::getInstance()->msgHandle(readbuf,connfd,this);
			}
			else if(events[i].events&EPOLLOUT)
			{
				//通知的顺序与投递的顺序相同
				handleEpollSocket::sendData(events[i].data.fd);
				handleEpollSocket::modEpollSocket(events[i].data.fd,false);
			}
			else if((events[i].events&EPOLLHUP)||(events[i].events&EPOLLERR))
			{
				std::cerr<<"parentProcess::CommunicationHandle:accept"<<std::endl;
				throw std::exception();
			}
		}
	}
}

static void packSendAlarmMsg(void *buffer)
{
	commontype::headInfo* _head = (commontype::headInfo *)buffer;
	_head->_type = magicnum::messagetype::NULLSENDALA;
	_head->_size = 0;
}

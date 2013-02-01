/*
 * childProcess.cpp
 *
 *  Created on: 2013-1-30
 *      Author: keym
 */
#include"childProcess.h"
#include"commondata/commontype.h"
#include"messagehandle/messageHandle.h"

#include<iostream>
#include<exception>
#include<stdio.h>
#include<string.h>
#include<deque>

#define MAXLINE 20

void childProcess::acceptClientSocket()
{
	if((this->_clientSocket = recv_fd(this->_parentSocket,write)) == magicnum::FAILIED)
	{
		std::cerr<<"childProcess::acceptClientSocket:recv_fd"<<std::endl;
		throw std::exception();
	}
}

void childProcess::InitializeProcess()
{
	handleEpollSocket::initializeEpoll();
	handleEpollSocket::addEpollSocket(this->_parentSocket);
}

void childProcess::CommunicateHandle()
{
	struct epoll_event events[this->_maxNumOfEpollfd + 1];
	std::deque<pid_t*> _dPid;
	int readbytes;
	char readbuf[MAXLINE];
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
			if(events[i].events&EPOLLIN)
			{
				memset(readbuf,0,MAXLINE);
				int _childSocketfd = events[i].data.fd;
				if((readbytes=RepeatRecv(_childSocketfd,readbuf,sizeof(commontype::headInfo))) < 0)
				{
					//这里可能是客户端关闭或出现错误
					if(readbytes == magicnum::CLOSEED)
					{
						std::cerr<<"magicnum::CLOSEED"<<std::endl;
						commontype::headInfo _head;
						_head._type = magicnum::messagetype::CPREQCLOSED;
						_head._size = 0;
						handleEpollSocket::packData(messageHandle::getInstance()->msgHandle(&_head,_childSocketfd));
						handleEpollSocket::modEpollSocket(this->_parentSocket,true);
					}
					continue;
				}
				//处理子进程指令
				void * pdata = messageHandle::getInstance()->msgHandle(readbuf,_childSocketfd);
				if(pdata == 0)
				{
					continue;
				}
				handleEpollSocket::packData(pdata);
				commontype::dataInfo *pInfo = (commontype::dataInfo *)pdata;
				if(pInfo->_type == magicnum::messagetype::PCREQSENDFD)
				{
					this->acceptClientSocket();
					handleEpollSocket::addEpollSocket(this->_clientSocket);
					handleEpollSocket::modEpollSocket(this->_clientSocket,true);
					continue;
				}
				handleEpollSocket::modEpollSocket(_childSocketfd,true);
			}
			else if(events[i].events&EPOLLOUT)
			{
				//通知的顺序与投递的顺序相同
				this->sendData(events[i].data.fd);
				handleEpollSocket::modEpollSocket(events[i].data.fd,false);
			}
			else if((events[i].events&EPOLLHUP)||(events[i].events&EPOLLERR))
			{
				throw std::exception();
			}
		}
	}
}

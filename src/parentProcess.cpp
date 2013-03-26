/*
 * parentProcess.cpp
 *
 *  Created on: 2013-1-25
 *      Author: keym
 */
#include<arpa/inet.h>
#include<string.h>

#include<exception>
#include<vector>
#include<deque>

#include<iostream>
#include<assert.h>

#include"parentProcess.h"
#include"processManage.h"

#include"messagehandle/messageHandle.h"

#define MAXLINE 10

void parentProcess::initializeListenfd()
{
	if((this->_netListenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		std::cerr<<"parentProcess::initializeListenfdAndEpollfd:socket"<<std::endl;
		throw std::exception();
	}
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(magicnum::parentprocess::LISTNEPORT);
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

void parentProcess::initializeChildProcessfd(int num)
{
	processManage::GetInstance()->CreateAllProcess(num,this);
}

void parentProcess::InitializeManage(int num) throw(std::exception)
{
	handleEpollSocket::initializeEpoll();
	this->initializeListenfd();
	this->initializeChildProcessfd(num);
}

void parentProcess::acceptNewConnection(int newfd)
{
	int _allocatefd = processManage::GetInstance()->OccupyProcessToClient(this);
	if(_allocatefd == magicnum::FAILIED){return;}
	this->_dnewConnectSocket.push_back(newfd);
	commontype::headInfo _head;
	_head._type = magicnum::messagetype::NULLSENDFDT;
	_head._size = 0;
	handleEpollSocket::packData(messageHandle::getInstance()->msgHandle(&_head,_allocatefd));
	handleEpollSocket::modEpollSocket(_allocatefd,true);
}

void parentProcess::sendNewConnection(int sendfd)
{
	assert(this->_dnewConnectSocket.size() != 0);
	int newfd = this->_dnewConnectSocket[0];
	this->_dnewConnectSocket.pop_front();
	if(send_fd(sendfd,newfd) == magicnum::SUCCESS)
	{
		this->_mSocketAndAlloc[sendfd] = true;
	}
	close(newfd);
}

void parentProcess::AddSocketToEpoll(int socket)
{
	handleEpollSocket::addEpollSocket(socket);
}

void parentProcess::relEpollSocket(int socket,PROCESSSTATE type)
{
	int result = processManage::GetInstance()->ReleaseProcess(socket,type);
	if(type == ERR && result == magicnum::SUCCESS)
	{
		printf("relEpollSocket error\n");
		delEpollSocket(socket);
	}
}

void parentProcess::CommunicationHandle()
{
	struct epoll_event events[this->_maxNumOfEpollfd + 1];
	std::deque<pid_t*> _dPid;
	int connfd;
	int readbytes;
	char readbuf[MAXLINE];
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
				this->acceptNewConnection(connfd);
				continue;
			}
			else if(events[i].events&EPOLLIN)
			{
				memset(readbuf,0,MAXLINE);
				int _childSocketfd = events[i].data.fd;
				if((readbytes=RepeatRecv(_childSocketfd,readbuf,sizeof(commontype::headInfo))) == magicnum::FAILIED)
				{
					this->relEpollSocket(_childSocketfd,ERR);
					continue;
				}
				commontype::headInfo *pHead = (commontype::headInfo*)readbuf;
				if(pHead->_type == magicnum::messagetype::CPREQCLOSED)
				{
					std::cerr<<"relepollsocket"<<std::endl;
					this->relEpollSocket(_childSocketfd,INIT);
				}
			}
			else if(events[i].events&EPOLLOUT)
			{
				//通知的顺序与投递的顺序相同
				handleEpollSocket::sendData(events[i].data.fd);
				this->sendNewConnection(events[i].data.fd);
				handleEpollSocket::modEpollSocket(events[i].data.fd,false);
			}
			else if((events[i].events&EPOLLHUP)||(events[i].events&EPOLLERR))
			{
				this->relEpollSocket(events[i].data.fd,ERR);
			}
		}
	}

}

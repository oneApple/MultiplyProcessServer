/*
 * netSocketFun.cpp
 *
 *  Created on: 2013-1-25
 *      Author: keym
 */
#include<stdlib.h>
#include<i386-linux-gnu/sys/socket.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>

#include"commondata/magicNum.h"
#include"commonfunction/signalHandleFun.h"

#include<stdio.h>
#include<exception>

int ListenAndSetBlockNum(int fd, int backlog)
{
	char *ptr;
	if ((ptr = getenv("LISTENQ")) != NULL)
	{
		backlog = atoi(ptr);
	}
	if (listen(fd, backlog) < 0)
	{
		//perror("listen error:");
		return magicnum::FAILIED;
	}
	return magicnum::SUCCESS;
}

int SetSocketNonblocking(int sock)    //将文件描述符设置为非阻塞模式
{
	int opts;
	if((opts=fcntl(sock,F_GETFL)<0)){
		//perror("fcntl get");
		return magicnum::FAILIED;
	}
	opts=opts|O_NONBLOCK;
	if(fcntl(sock,F_SETFL,opts)<0){
		//perror("fcntl set");
		return magicnum::FAILIED;
	}
	return magicnum::SUCCESS;
}

//当socket为阻塞形式时，采用alarm进行超时功能，如果为非阻塞形式不要采用，容易引起错误
ssize_t RepeatRecv(int fd,char *buf,ssize_t bufsize)
{
	ssize_t readbytes = 0;
	ssize_t remnantbytes = bufsize;
	char *pbuf = buf;
	while(remnantbytes > 0)
	{
		readbytes = recv(fd,pbuf,remnantbytes,0);
		if(readbytes <= 0)//0:对方关闭;<0:发生错误
		{
			if(readbytes == 0)
			{
				return magicnum::CLOSEED;
			}
			if(errno == EAGAIN || errno == EINTR)//EAGAIN：缓存无数据;EINTR：系统中断
			{
				//printf("buffer no data\n");//缓存区已无数据可读
				readbytes = 0;
				continue;
			}
			//perror("recv");
			return magicnum::FAILIED;
		}
		remnantbytes -= readbytes;//发送部分数据
		pbuf += readbytes;
	}
	return remnantbytes;
}

ssize_t RepeatSend(int fd,const char *buf,ssize_t bufsize)
{
	ssize_t sendbytes = 0;
	ssize_t remnantbytes = bufsize;
	const char *pbuf = buf;
	while(remnantbytes > 0)
	{
		sendbytes = send(fd,pbuf,remnantbytes,0);
		if(sendbytes <= 0)
		{
			if(errno==EINTR || errno==EAGAIN)
			{
				printf("block later..\n");//缓存区暂时已满，所以等待一会再次读取
				sendbytes = 0;
				continue;
			}
			return magicnum::FAILIED;
		}
		remnantbytes -= sendbytes;//发送部分数据
		pbuf += sendbytes;
	}
	return remnantbytes;
}

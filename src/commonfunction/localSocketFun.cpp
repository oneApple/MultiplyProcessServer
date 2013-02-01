/*
 * localSocketFun.cpp
 *
 *  Created on: 2013-1-25
 *      Author: keym
 */
#include"commonfunction/localSocketFun.h"
#include<i386-linux-gnu/sys/socket.h>
#include<unistd.h>
#include<assert.h>
#include<errno.h>

#include<stdlib.h>
#include<string.h>

#include"commondata/magicNum.h"

#include<stdio.h>

static struct cmsghdr *cmptr = NULL;

int send_fd(int fd,int fd_to_send)
{
	struct iovec iov[1];
	struct msghdr msg;
	char buf[magicnum::localsocketfun::BUFFERSIZE];
	iov[0].iov_base=buf;
	iov[0].iov_len=2;
	msg.msg_iov=iov;
	msg.msg_iovlen=1;
	msg.msg_name=NULL;
	msg.msg_namelen=0;
	if(fd_to_send<0){
		msg.msg_control=NULL;
		msg.msg_controllen=0;
		buf[1]=-fd_to_send;
		if(buf[1]==0)
			buf[1]=1;
	}else{
		if(cmptr == NULL && ((cmptr = (cmsghdr*)malloc(CONTROLLEN)) == NULL))
			return magicnum::FAILIED;
		cmptr->cmsg_level=SOL_SOCKET;
		cmptr->cmsg_type=SCM_RIGHTS;
		cmptr->cmsg_len=CONTROLLEN;
		msg.msg_control=cmptr;
		msg.msg_controllen=CONTROLLEN;
		*(int*)CMSG_DATA(cmptr)=fd_to_send;
		buf[1]=0;
	}
	buf[0]=0;
	if(sendmsg(fd,&msg,0)!=2)
		return magicnum::FAILIED;
	return magicnum::SUCCESS;
}

int send_err(int fd,int errcode,const char *msg)
{
	int n;
	if((n=strlen(msg))>0)
		if(write(fd,msg,n)!=n)
			return magicnum::FAILIED;
	if(errcode>=0)
		errcode=-1;
	if(send_fd(fd,errcode)<0)
		return magicnum::FAILIED;
	return magicnum::SUCCESS;
}

int recv_fd(int fd,ssize_t (*userfunc)(int,const void *,size_t))
{
	int newfd,nr,status;
	char *ptr;
	char buf[magicnum::localsocketfun::BUFFERSIZE];
	struct iovec iov[1];
	struct msghdr msg;
	status=-1;
	for(;;)
	{
		iov[0].iov_base=buf;
		iov[0].iov_len=sizeof(buf);
		msg.msg_iov=iov;
		msg.msg_iovlen=1;
		msg.msg_name=NULL;
		msg.msg_namelen=0;
		if(cmptr==NULL&&(cmptr=(cmsghdr*)malloc(CONTROLLEN))==NULL)
			return magicnum::FAILIED;
		msg.msg_control=cmptr;
		msg.msg_controllen=CONTROLLEN;
		if((nr=recvmsg(fd,&msg,0))<0){
			if(errno == EAGAIN || errno == EINTR)//EAGAIN：缓存无数据;EINTR：系统中断
			{
				//printf("buffer no data\n");//缓存区已无数据可读
				//readbytes = 0;
				continue;
			}
			perror("recvmsg");
			//perror("recv");
			return magicnum::FAILIED;
		}else if(nr==0){
			printf("connection closed by server\n");
			return magicnum::FAILIED;
		}
		for(ptr=buf;ptr<&buf[nr];)
		{
			if(*ptr++==0){
				assert(ptr == &buf[nr-1]);
				status=*ptr&0xFF;
				if(status==0){
					if(msg.msg_controllen!=CONTROLLEN){
						printf("status=0,but no fd\n");
						return magicnum::FAILIED;
					}
					newfd=*(int*)CMSG_DATA(cmptr);
				}else{
					newfd=-status;
				}
				nr=-2;
			}
		}
		if(nr > 0 && (*userfunc)(STDERR_FILENO,buf,nr)!=nr)
			return magicnum::FAILIED;
		if(status>=0)
			return(newfd);
	}
}

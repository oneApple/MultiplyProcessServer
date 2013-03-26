/*
 * localSocketFun.h
 *
 *  Created on: 2013-1-25
 *      Author: keym
 */

#ifndef LOCALSOCKETFUN_H_
#define LOCALSOCKETFUN_H_

#define CONTROLLEN CMSG_LEN(sizeof(int))
#define CONTROLLEN CMSG_LEN(sizeof(int))

#include<i386-linux-gnu/sys/types.h>

//发送文件描述符
int send_fd(int fd,int fd_to_send);
int send_err(int fd,int errcode,const char *msg);
//接收文件描述符
int recv_fd(int fd,ssize_t (*userfunc)(int,const void *,size_t));

#endif /* LOCALSOCKETFUN_H_ */

/*
 * netSocketFun.h
 *
 *  Created on: 2013-1-25
 *      Author: keym
 */

#ifndef NETSOCKETFUN_H_
#define NETSOCKETFUN_H_
#include<i386-linux-gnu/sys/types.h>

int ListenAndSetBlockNum(int fd, int backlog) ;
int SetSocketNonblocking(int sock) ;   //将文件描述符设置为非阻塞模式
ssize_t RepeatRecv(int fd,char *buf,ssize_t bufsize);
ssize_t RepeatSend(int fd,const char *buf,ssize_t bufsize);

#endif /* NETSOCKETFUN_H_ */

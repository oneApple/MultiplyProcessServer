/*
 * signalHandleFun.h
 *
 *  Created on: 2013-1-25
 *      Author: keym
 */

#ifndef SIGNALHANDLEFUN_H_
#define SIGNALHANDLEFUN_H_
#include<setjmp.h>

typedef void Sigfunc(int);
//添加信号处理函数
Sigfunc *Signal(int signo, Sigfunc *func);
void sig_cld(int signo);
#endif /* SIGNALHANDLEFUN_H_ */

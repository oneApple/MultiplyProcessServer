/*
 * signalHandleFun.cpp
 *
 *  Created on: 2013-1-25
 *      Author: keym
 */
#include<signal.h>
#include<wait.h>
#include<errno.h>

#include"commonfunction/signalHandleFun.h"

#include<iostream>
#include<stdio.h>

//添加信号处理函数
Sigfunc* Signal(int signo, Sigfunc* func)
{
	struct sigaction act, oact;
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (signo == SIGALRM) {
#ifdef SA_INTERRUPT
		act.sa_flags|=SA_INTERRUPT;//在处理指定信号时，屏蔽该信号
#endif
	} else {
#ifdef SA_RESTART
		act.sa_flags|=SA_RESTART;
#endif
	}
	if (sigaction(signo, &act, &oact) < 0)
		return (SIG_ERR);
	return (oact.sa_handler);
}

//处理关闭子进程
void sig_cld(int signo)
{
	pid_t pid;
	while(1)
	{
		if((pid = waitpid(-1,NULL,WNOHANG)) <= 0)
		{
			break;
		}
		else
		{
			std::cout<<"sig_cld:"<<pid<<std::endl;
		}
	}
	if(errno != ECHILD)
	{
		return;
	}
}



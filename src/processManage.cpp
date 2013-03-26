/*
 * processManage.cpp
 *
 *  Created on: 2013-1-24
 *      Author: keym
 */

#include<i386-linux-gnu/sys/resource.h>
#include<i386-linux-gnu/sys/socket.h>
#include<assert.h>
#include<exception>
#include<string.h>
#include"processManage.h"
#include"commonfunction/localSocketFun.h"
#include"commonfunction/netSocketFun.h"

#include"childProcess.h"
#include"parentProcess.h"
#include<iostream>

processManage* processManage::_singleInstance = NULL;

void processManage::getSystemLimit()
{
	rlimit limit;
	getrlimit(RLIMIT_NPROC,&limit);
	if(limit.rlim_cur > magicnum::processmanage::MAXNUMPROCESS)
	{
		this->_uMaxNumOfProcess = limit.rlim_cur;
	}
}

void processManage::releaseAllData()
{
	vectorIterType iter = this->_vProcessInfo.begin();
	while(iter != this->_vProcessInfo.end())
	{
		if((*iter) != NULL)
		{
			delete (*iter);
		}
		++ iter;
	}
	this->_vProcessInfo.clear();
	this->_mProcessSocketAndIndex.clear();
}

void processManage::createSingleProcess()
{
	pid_t pid;
	int sockfd[2];
	socketpair(AF_LOCAL,SOCK_STREAM,0,sockfd);
	if((pid = fork()) > 0)
	{
		childProcessInfo *c = new childProcessInfo(sockfd[0],INIT,pid);
		std::cout<<"new pid:"<<pid<<","<<this->_uTotalNumOfProcess<<std::endl;
		close(sockfd[1]);
		this->_vProcessInfo.push_back(c);
		return;
	}
	//client
	close(sockfd[0]);
	childProcess p(sockfd[1]);
	p.InitializeProcess();
	p.CommunicateHandle();
	assert(1 == 0);
	std::cerr<<"processManage::createSingleProcess:assert"<<std::endl;
	throw std::exception();
}

void processManage::CreateAllProcess(unsigned num,parentProcess *pobject)
throw(std::exception)
{
	if(num < this->_uMinNumOfProcess || num > this->_uMaxNumOfProcess){throw std::exception();}

	unsigned i;
	this->_uTotalNumOfProcess += num;

	unsigned _totalnum = this->_vProcessInfo.size();
	for(i = 0;i < num;++ i)
	{
		this->createSingleProcess();
		unsigned index = _totalnum + i;
		int socket = this->_vProcessInfo[index]->GetProcessSocket();
		pobject->AddSocketToEpoll(socket);
		this->_mProcessSocketAndIndex[socket] = index;
	}
}

int processManage::OccupyProcessToClient(parentProcess *pobject)
{
	if(this->_uNumOfRunningProcess == this->_uMaxNumOfProcess)
	{
		return magicnum::FAILIED;
	}

	if(this->_uNumOfRunningProcess == this->_uTotalNumOfProcess)
	{
		this->CreateAllProcess(this->_uTotalNumOfProcess,pobject);
	}

	vectorIterType viter = this->_vProcessInfo.begin();
	while(viter != this->_vProcessInfo.end())
	{
		if((*viter)->GetProcessState() == INIT)
		{
			break;
		}
		++ viter;
	}

	assert(viter != this->_vProcessInfo.end());

	(*viter)->SetProcessState(BUSY);
	++ this->_uNumOfRunningProcess;
	std::cout<<"occupy:"<<(*viter)->GetProcessPid()<<std::endl;
	return (*viter)->GetProcessSocket();
}

void processManage::moveErrorProcessToTail()
{
	vectorIterType reverseOrderIter = this->_vProcessInfo.end();
	vectorIterType forwardOrderIter = this->_vProcessInfo.begin();

	while(forwardOrderIter < reverseOrderIter)
	{
		if((*forwardOrderIter)->GetProcessState() == ERR)
		{
			-- reverseOrderIter;
			while((*reverseOrderIter)->GetProcessState() == ERR)
			{
				-- reverseOrderIter;
			}
			childProcessInfo *temp = (*reverseOrderIter);
			(*reverseOrderIter) = (*forwardOrderIter);
			(*forwardOrderIter) = temp;
		}
		++ forwardOrderIter;
	}
}

int processManage::ReleaseProcess(int socket,PROCESSSTATE type)
{
	std::map<int,int>::iterator iter = this->_mProcessSocketAndIndex.find(socket);

	if(iter == this->_mProcessSocketAndIndex.end())
	{
		return magicnum::FAILIED;
	}

	this->_vProcessInfo[iter->second]->SetProcessState(type);
	-- this->_uNumOfRunningProcess;
	std::cout<<"release:"<<this->_vProcessInfo[iter->second]->GetProcessPid()<<","<<type<<std::endl;
	if(this->_uNumOfRunningProcess == this->_uTotalNumOfProcess / magicnum::processmanage::DIVISOR)
	{
		if(this->_uTotalNumOfProcess == this->_uMinNumOfProcess)
		{
			return magicnum::SUCCESS;
		}
		this->moveErrorProcessToTail();

		vectorIterType forwardOrderIter = this->_vProcessInfo.begin();
		vectorIterType reverseOrderIter = this->_vProcessInfo.begin() + this->_vProcessInfo.size() / 2;

		this->_mProcessSocketAndIndex.clear();

		while(reverseOrderIter != this->_vProcessInfo.end())
		{
			if((*reverseOrderIter)->GetProcessState() == BUSY)
			{
				while((*forwardOrderIter)->GetProcessState() == BUSY)
				{
					++ forwardOrderIter;
				}
				childProcessInfo *temp = (*reverseOrderIter);
				(*reverseOrderIter) = (*forwardOrderIter);
				(*forwardOrderIter) = temp;
			}
			if((*reverseOrderIter)->GetProcessState() == INIT)
			{
				close((*reverseOrderIter)->GetProcessSocket());
				std::cerr<<"child-init:"<<(*reverseOrderIter)->GetProcessPid()<<std::endl;
				kill((*reverseOrderIter)->GetProcessPid(),SIGTERM);
			}
			else
			{
				std::cerr<<"child-error:"<<(*reverseOrderIter)->GetProcessPid()<<std::endl;
			}
			delete (*reverseOrderIter);
			++ reverseOrderIter;
		}

		this->_vProcessInfo.erase(this->_vProcessInfo.begin() + this->_vProcessInfo.size() / 2,this->_vProcessInfo.end());
		unsigned i;
		for(i = 0;i < this->_vProcessInfo.size();++ i)
		{
			this->_mProcessSocketAndIndex[this->_vProcessInfo[i]->GetProcessSocket()] = i;
		}
		this->_uTotalNumOfProcess /= 2;
	}
	std::cout<<"total,runing:"<<this->_uTotalNumOfProcess<<","<<this->_uNumOfRunningProcess<<std::endl;
	return magicnum::SUCCESS;
}

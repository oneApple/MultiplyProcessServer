/*
 * processManage.h
 *
 *  Created on: 2013-1-24
 *      Author: keym
 */

#ifndef PROCESSMANAGE_H_
#define PROCESSMANAGE_H_

#include<unistd.h>
#include<vector>
#include<map>
#include"childProcessInfo.h"
#include"commonfunction/signalHandleFun.h"
#include"commondata/magicNum.h"

#include<stdio.h>
typedef std::vector<childProcessInfo *>::iterator vectorIterType;
class parentProcess;

class processManage{
private:
	std::vector<childProcessInfo *> _vProcessInfo;//子进程数据
	std::map<int,int> _mProcessSocketAndIndex;//socket与数据直接联系
	unsigned _uTotalNumOfProcess;//子进程总数
	unsigned _uNumOfRunningProcess;//接受客户端链接的子进程总数
	unsigned _uMaxNumOfProcess;//可以创建的最大子进程总数
	unsigned _uMinNumOfProcess;//可以创建的最小的子进程总数
	static processManage *_singleInstance;
	class Garbo{//用于删除实例句柄
	public:
		~Garbo()
		{
			if(processManage::_singleInstance != NULL)
			{
				delete processManage::_singleInstance;
			}
		}
	};
	static Garbo release;
public:
	static processManage *GetInstance()
	{
		if(processManage::_singleInstance == NULL)
		{
			processManage::_singleInstance = new processManage;
			processManage::_singleInstance->InitializeManage();
		}
		return processManage::_singleInstance;
	}
private:
	explicit processManage():_uTotalNumOfProcess(0),
	_uNumOfRunningProcess(0),_uMaxNumOfProcess(magicnum::processmanage::MAXNUMPROCESS),
	_uMinNumOfProcess(magicnum::processmanage::MINNUMPROCESS){}
	processManage(const processManage&);
	processManage& operator=(const processManage&);//不去定义
	~processManage()
	{
		this->releaseAllData();
	}
private:
	void getSystemLimit();//获取系统的最大进程数
	void InitializeManage()//初始化操作：获取系统最大进程数，注册信号
	{
		getSystemLimit();
		if(Signal(SIGCHLD,sig_cld)==SIG_ERR)
		{
			throw std::exception();
		}
	}
	void releaseAllData();//释放所有数据
	void createSingleProcess();//创建一个子进程
	void moveErrorProcessToTail();//将_vProcessInfo前面的err类型的数据移动到后面
public:
	void CreateAllProcess(unsigned num,parentProcess *pobject) throw(std::exception);//创建指定数目的进程
	int OccupyProcessToClient(parentProcess *pobject);//将一个进程分配给一个客户
	int ReleaseProcess(int socket,PROCESSSTATE type);//释放一个进程
};

#endif /* PROCESSMANAGE_H_ */

/*
 * deviceProcess.h
 *
 *  Created on: Mar 27, 2013
 *      Author: keym
 */

#ifndef DEVICEPROCESS_H_
#define DEVICEPROCESS_H_

#include"handleEpollSocket.h"

class deviceProcess : protected handleEpollSocket{
private:
	int _netListenfd;
	int _parentfd;
private:
	void initializeListenfd();
	static deviceProcess *_singleInstance;
	class Garbo{//用于删除实例句柄
	public:
		~Garbo()
		{
			if(deviceProcess::_singleInstance != NULL)
			{
				delete deviceProcess::_singleInstance;
			}
		}
	};
	static Garbo release;
public:
	static deviceProcess *GetInstance()
	{
		if(deviceProcess::_singleInstance == NULL)
		{
			deviceProcess::_singleInstance = new deviceProcess;
			deviceProcess::_singleInstance->initializeListenfd();
		}
		return deviceProcess::_singleInstance;
	}
public:
	const int GetParentSocketfd()
	{
		return this->_parentfd;
	}
	int GetSocketfdAndRun();
	void CommunicationHandle();

};

#endif /* DEVICEPROCESS_H_ */

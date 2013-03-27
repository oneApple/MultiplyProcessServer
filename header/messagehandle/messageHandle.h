/*
 * messagehandle.h
 *
 *  Created on: 2013-1-31
 *      Author: keym
 */

#ifndef MESSAGEHANDLE_H_
#define MESSAGEHANDLE_H_
#include<messagehandle/messageHandleInterface.h>
#include<map>
//用来实现工厂模式
class messageHandle{
private:
	std::map<unsigned,messageHandleInterface*> _mmsgHandle;
private:
	messageHandleInterface *getMsgHandleInstance(unsigned type);
public:
	static messageHandle* _singleInstance;
	static messageHandle *getInstance();
	class Garbo{
	public:
		~Garbo()
		{
			if(messageHandle::_singleInstance != NULL)
			{
				delete messageHandle::_singleInstance;
			}
		}
	};
	static Garbo release;
public:
	messageHandle();
	void *msgHandle(void *recvbuf,int recvfd,void *uperuser);
};
#endif /* MESSAGEHANDLE_H_ */

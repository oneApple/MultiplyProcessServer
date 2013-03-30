/*
 * dataInfo.h
 *
 *  Created on: 2013-3-30
 *      Author: keym
 */

#ifndef DATAINFO_H_
#define DATAINFO_H_
#include"commondata/commontype.h"

class dataInfo{
private:
	char *_pdata;//要发送的数据（头+数据）
	size_t _size;//头+数据的大小
public:
	dataInfo():_pdata(0),_size(0){}
	virtual ~dataInfo()
	{
		if(this->_pdata != 0)
		{
			delete []this->_pdata;
		}
	}
public:
	char *GetData(){return this->_pdata;}
	size_t GetSize(){return this->_size;}
	void PackMsg(size_t datasize,char *phead,char *pbody);
};

#endif /* DATAINFO_H_ */

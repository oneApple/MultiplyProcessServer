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
public:
	char *_pdata;//要发送的数据（头+数据）
	size_t _size;//头+数据的大小
};

#endif /* DATAINFO_H_ */

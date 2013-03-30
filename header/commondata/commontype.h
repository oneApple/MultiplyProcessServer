/*
 * commontype.h
 *
 *  Created on: 2013-1-31
 *      Author: keym
 */

#ifndef COMMONTYPE_H_
#define COMMONTYPE_H_
#include<sys/types.h>

namespace commontype{
//发送消息的头
struct _messagehead{
	size_t _type;
	size_t _size;
};
typedef struct _messagehead headInfo;
};


#endif /* COMMONTYPE_H_ */

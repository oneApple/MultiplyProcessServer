/*
 * magicNum.h
 *
 *  Created on: 2013-1-25
 *      Author: keym
 */

#ifndef MAGICNUM_H_
#define MAGICNUM_H_
#include<sys/types.h>
//魔法数一定不要直接使用
namespace magicnum{

const ssize_t SUCCESS = 0;
const ssize_t FAILIED = -1;
const ssize_t CLOSEED = -2;
const size_t UNFIXMEMPOOLSIZE = 10000;
const size_t MSGHEADSIZE = sizeof(size_t) * 2;

namespace processmanage{
const size_t DIVISOR = 2;
const size_t MAXNUMPROCESS = 4;
const size_t MINNUMPROCESS = 2;
};

namespace localsocketfun{
const size_t BUFFERSIZE = 2;
};

namespace deviceprocess{
const size_t LISTENPORT = 5678;
};

namespace parentprocess{
const size_t LISTNEPORT = 1234;
const size_t LISTENBLOCKNUM = 10;
const ssize_t EPOLLTIMEOUT = -1;
};

namespace messagetype{
const size_t NULLTYPENUM = 1000;
const size_t PCREQSENDFD = 1001;//发送描述符
const size_t CPREQCLOSED = 2002;
const size_t NULLSENDFDT = 3003;
const size_t CCMESSAGECC = 4004;//客户间传递的消息
const size_t CCREQCLOSED = 5005;
const size_t NULLSENDALA = 6006;
const size_t DPSENDALARM = 7007;
const size_t PCMESSAGEPC = 8008;
const size_t CCRELEASECC = 9009;
const size_t CPRELEASECP = 0110;
};

};

#endif /* MAGICNUM_H_ */

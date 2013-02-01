/*
 * magicNum.h
 *
 *  Created on: 2013-1-25
 *      Author: keym
 */

#ifndef MAGICNUM_H_
#define MAGICNUM_H_
//魔法数一定不要直接使用
namespace magicnum{

const int SUCCESS = 0;
const int FAILIED = -1;
const int CLOSEED = -2;

namespace processmanage{
const unsigned DIVISOR = 2;
const unsigned MAXNUMPROCESS = 4;
const unsigned MINNUMPROCESS = 2;
};

namespace localsocketfun{
const unsigned BUFFERSIZE = 2;
};

namespace parentprocess{
const unsigned LISTNEPORT = 8080;
const unsigned LISTENBLOCKNUM = 10;
const unsigned EPOLLTIMEOUT = -1;
};

namespace messagetype{
const unsigned NULLTYPENUM = 1000;
const unsigned PCREQSENDFD = 1001;//发送描述符
const unsigned CPREQCLOSED = 2002;
const unsigned NULLSENDFDT = 3003;
const unsigned CCMESSAGECC = 4004;//客户间传递的消息
};

};

#endif /* MAGICNUM_H_ */
